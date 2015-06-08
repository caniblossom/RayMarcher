/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#include <algorithm>
#include <cassert>
#include <thread>

#include "tracer.hpp"

using namespace std;

namespace raymarcher {
    class DistanceResult {
        public:
            Real distance;
            SceneItem item;

            DistanceResult() {}
            DistanceResult(const Real distance, const SceneItem& item);
    };

    DistanceResult::DistanceResult(const Real distance, const SceneItem& item) : distance(distance), item(item) {}

    DistanceResult getDistance(const vector<SceneItem>& itemList, const RVec3& position) {
        if (itemList.size() <= 0) return DistanceResult(numeric_limits<Real>::max(), SceneItem());

        Real curDistance = itemList[0].getObject()->distance(position);
        unsigned curIndex = 0;

        for (unsigned i = 1; i < itemList.size(); i++) {
            const Object* current = itemList[i].getObject();
            const Real newDistance = current->distance(position);

            if (newDistance <= curDistance) {
                curDistance = newDistance;
                curIndex = i;
            }
        }

        return DistanceResult(curDistance, SceneItem(itemList[curIndex]));
    }

    RVec3 getNormal(const vector<SceneItem>& itemList, const RVec3& position, const Real epsilon) {
        const Real center = getDistance(itemList, RVec3(position)).distance;
        const Real z = static_cast<Real>(0.0);

        RVec3 delta(
            getDistance(itemList, RVec3(position) + RVec3(epsilon, z, z)).distance - center,
            getDistance(itemList, RVec3(position) + RVec3(z, epsilon, z)).distance - center,
            getDistance(itemList, RVec3(position) + RVec3(z, z, epsilon)).distance - center
        );

        return delta.normal();
    }

    Tracer::Tracer() : _scene(nullptr), _image(nullptr), _settings(TracerSettings()) {}

    void Tracer::reset(const TracerSettings& settings)  {
        _settings = settings;

        _xBlock = 0, _yBlock = 0;
        _xBlockCount = _image->getWidth()  / _settings.blockWidth  + (_image->getWidth()  % _settings.blockWidth  == 0 ? 0 : 1);
        _yBlockCount = _image->getHeight() / _settings.blockHeight + (_image->getHeight() % _settings.blockHeight == 0 ? 0 : 1);

        _rStep = static_cast<Real>(1.0) / static_cast<Real>(_settings.lambertianRadSamples);
        _aStep = static_cast<Real>(1.0) / static_cast<Real>(_settings.lambertianAngSamples);
        _lWeight = static_cast<Real>(1.0) / static_cast<Real>(_settings.lambertianRadSamples * _settings.lambertianAngSamples);
    }

    void Tracer::setScene(const Scene* scene) {
        assert(scene);
        _scene = scene;

        reset(_settings);
    }

    void Tracer::setImage(Image* image) {
        assert(image);
        _image = image;

        if (_image->isNull()) {
            _xBlockCount = 0;
            _yBlockCount = 0;
            return;
        }

        reset(_settings);
    }

    void Tracer::setCamera(Camera& camera) {
        _camera = camera;
    }

    bool Tracer::isFinished() {
        lock_guard<mutex> lock(_blockCounterLock);
        return _yBlock >= _yBlockCount;
    }

    void Tracer::renderNextBlock(RGen& gen) {
        assert(_scene && _image);
        if (isFinished()) return;

        int xBegin = 0;
        int yBegin = 0;

        {
            lock_guard<mutex> lock(_blockCounterLock);
            xBegin = _xBlock * _settings.blockWidth;
            yBegin = _yBlock * _settings.blockHeight;

            _xBlock++;
            if (_xBlock >= _xBlockCount) {
                _xBlock = 0;
                _yBlock++;
            }
        }

        const int xEnd = min(_image->getWidth(),  xBegin + _settings.blockWidth);
        const int yEnd = min(_image->getHeight(), yBegin + _settings.blockHeight);

        for (int y = yBegin; y < yEnd; y++) {
            for (int x = xBegin; x < xEnd; x++) {
                const RVec2 element(static_cast<Real>(x), static_cast<Real>(y));

                for (unsigned sample = 0; sample < _settings.sampleCount; sample++) {
                    const RVec3 color = recurseTrace(_camera.genRay(element, gen, _settings.rayInitialLife), gen);
                    _image->accumulate(x, y, Sample(color, static_cast<Real>(1.0)));
                }
            }
        }
    }

    RVec3 Tracer::recurseTrace(Ray ray, RGen& gen) const {
        const unsigned MAX_STEPS = 512;

        const Real MARCH_EPSILON  = static_cast<Real>(1.0 / 1024.0);
        const Real NORMAL_EPSILON = MARCH_EPSILON / static_cast<Real>(64.0);
        const Real SCENE_RADIUS_SQR = static_cast<Real>(256.0 * 256.0);

        const RVec3 BLACK(static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(0.0));
        const RVec3 PINK(static_cast<Real>(1024.0), static_cast<Real>(0.0), static_cast<Real>(1024.0));

        unsigned stepCount = 0;
        while (true) {
            DistanceResult result = getDistance(_scene->getGlobalItemList(), ray.position);
            if (!result.item.isGood()) return PINK;

            if (result.distance < MARCH_EPSILON) {
                const RVec3 normal = getNormal(_scene->getGlobalItemList(), ray.position, NORMAL_EPSILON);

                const Material* material = result.item.getMaterial();

                RVec3 color = PINK;
                Real  specularity = 1.0;

                switch (material->getType()) {
                    case Material::Type::Simple: {
                        color       = material->getBaseColor();
                        specularity = material->getBaseSpecularity();
                        break;
                    }
                    case Material::Type::Mapped: {
                        const RVec2 uv = result.item.getObject()->mapToUV(ray.position, ray.normal);
                        color          = material->getMappedColor(uv);
                        specularity    = material->getMappedSpecularity(uv);
                        break;
                    }
                }

                if (material->isEmissive()) {
                    return ray.color * color;
                }
                else {
                    ray.march(-MARCH_EPSILON);
                    ray.color *= color;

                    RVec3 specularColor(BLACK);
                    RVec3 diffuseColor(BLACK);

                    if (specularity < static_cast<Real>(1.0)) {
                        Ray baseRay = ray;
                        baseRay.payLife(static_cast<Real>(1.0));

                        if (baseRay.isAlive()) {
                            Real curRad = static_cast<Real>(0.0);
                            Real curAng = static_cast<Real>(0.0);

                            RVec3 color(static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(0.0));

                            for (unsigned a = 0; a < _settings.lambertianAngSamples; a++) {
                                for (unsigned r = 0; r < _settings.lambertianRadSamples; r++) {
                                    Ray newRay = baseRay;

                                    newRay.normal = gen.genOnSemiSphereCosWeighted(normal, curRad, curRad + _rStep, curAng, curAng + _aStep);
                                    color += recurseTrace(newRay, gen);

                                    curRad += _rStep;
                                }

                                curRad = static_cast<Real>(0.0);
                                curAng += _aStep;
                            }

                            diffuseColor = _lWeight * color;
                        }
                    }

                    if (specularity > static_cast<Real>(0.0)) {
                        Ray baseRay = ray;
                        baseRay.payLife(static_cast<Real>(0.1));

                        if (baseRay.isAlive()) {
                            Ray newRay = baseRay;
                            newRay.normal = util::getMirrored(normal, -ray.normal);
                            specularColor = recurseTrace(newRay, gen);
                        }
                    }

                    return specularity * specularColor + static_cast<Real>(1.0 - specularity) * diffuseColor;
                }

                assert(false);
            }

            ray.march(result.distance);

            const Real rayDistanceSqr = ray.position.dot(ray.position);
            if (rayDistanceSqr > SCENE_RADIUS_SQR) {
                return BLACK;
            }

            stepCount++;
            if (stepCount > MAX_STEPS) break;
        }

        return BLACK;
    }
};

