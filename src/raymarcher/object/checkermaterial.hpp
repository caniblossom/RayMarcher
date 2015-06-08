/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_CHECKERMATERIAL_HPP
#define RAYMARCHER_CHECKERMATERIAL_HPP

#include "material.hpp"

namespace raymarcher {
    class CheckeredMaterial : public Material {
        public:
            CheckeredMaterial(
                const bool isEmissive,
                const RVec3& color1,
                const RVec3& color2,
                const Real specularity1,
                const Real specularity2,
                const RVec2 scale
            );

            RVec3 getMappedColor       (const RVec2 uv) const;
            Real  getMappedSpecularity (const RVec2 uv) const;

        private:
            RVec3 _color1, _color2;
            Real  _specularity1, _specularity2;

            RVec2 _scale;

            Real getPhase(const RVec2 uv) const;
    };

    inline CheckeredMaterial::CheckeredMaterial(
        const bool isEmissive,
        const RVec3& color1,
        const RVec3& color2,
        const Real specularity1,
        const Real specularity2,
        const RVec2 scale
    ) :
        Material(Material::Type::Mapped, isEmissive),
        _color1(color1),
        _color2(color2),
        _specularity1(specularity1),
        _specularity2(specularity2),
        _scale(scale)
    {}

    inline RVec3 CheckeredMaterial::getMappedColor(const RVec2 uv) const {
        return getPhase(uv) > static_cast<Real>(0.0) ? _color1 : _color2;
    }

    inline Real CheckeredMaterial::getMappedSpecularity(const RVec2 uv) const {
        return getPhase(uv) > static_cast<Real>(0.0) ? _specularity1 : _specularity2;
    }

    inline Real CheckeredMaterial::getPhase(const RVec2 uv) const {
        const RVec2 scaled = _scale * uv;

        RVec2 phase(fmod(scaled.x, static_cast<Real>(1.0)), fmod(scaled.y, static_cast<Real>(1.0)));
        phase.x = phase.x < 0 ? static_cast<Real>(1.0) + phase.x : phase.x;
        phase.y = phase.y < 0 ? static_cast<Real>(1.0) + phase.y : phase.y;

        return (phase.x - static_cast<Real>(0.5)) * (phase.y - static_cast<Real>(0.5));
    }
};
#endif /* RAYMARCHER_CHECKERMATERIAL_HPP */

