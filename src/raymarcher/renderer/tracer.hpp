/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_TRACER_HPP
#define RAYMARCHER_TRACER_HPP

#include <mutex>

#include "../general/types.hpp"
#include "../object/scene.hpp"

#include "camera.hpp"
#include "image.hpp"
#include "tracersettings.hpp"

namespace raymarcher {
    class Tracer {
        public:
            Tracer();

            void reset(const TracerSettings& settings);

            void setImage(Image* image);
            void setScene(const Scene* scene);
            void setCamera(Camera& camera);

            bool isFinished();
            void renderNextBlock(RGen& gen);

        private:
            const Scene* _scene;
            Image*       _image;
            Camera       _camera;

            TracerSettings _settings;

            unsigned int _xBlockCount, _yBlockCount;
            unsigned int _xBlock,      _yBlock;
            std::mutex _blockCounterLock;

            Real _rStep, _aStep, _lWeight;

            RVec3 recurseTrace(Ray ray, RGen& gen) const;
    };
};

#endif /* RAYMARCHER_TRACER_HPP */

