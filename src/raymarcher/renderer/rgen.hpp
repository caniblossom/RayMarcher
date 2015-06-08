/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_RGEN_HPP
#define RAYMARCHER_RGEN_HPP

#include <cmath>
#include <cstdint>
#include <mutex>

#include "flowerpot/math/constants.hpp"
#include "flowerpot/rng/rng.hpp"

#include "../general/types.hpp"
#include "util.hpp"

namespace raymarcher {
    class RGen {
        public:
            RGen();

            Real genRealP();
            Real genRealNP();

            RVec2 genOnUnitCircle();
			RVec3 genOnSemiSphereCosWeighted(const RVec3& normal, const Real rMin, const Real rMax, const Real aMin, const Real aMax);

        private:
            static bool _seedGenInit;
            static flowerpot::RNG _seedRNG;
            static std::mutex _seedGenLock;

            flowerpot::RNG _rng;
            static std::uint32_t genSeed();
    };

    inline RGen::RGen() : _rng(genSeed()) {}

    inline Real RGen::genRealP() {
        return static_cast<Real>(_rng.genUInt()) / static_cast<Real>(4294967295.0);
    }

    inline Real RGen::genRealNP() {
        return static_cast<Real>(2.0) * (genRealP() - static_cast<Real>(0.5));
    }

    inline RVec2 RGen::genOnUnitCircle() {
        const int MAX_ATTEMPTS = 1024;
        for (int i = 0; i < MAX_ATTEMPTS; i++) {
            const RVec2 p(genRealNP(), genRealNP());
            if (p.dot(p) <= static_cast<Real>(1.0)) return p;
        }

        return RVec2(static_cast<Real>(0.0), static_cast<Real>(1.0));
    }

    inline RVec3 RGen::genOnSemiSphereCosWeighted(const RVec3& normal, const Real rMin, const Real rMax, const Real aMin, const Real aMax) {
        const Real r =  rMin + (rMax - rMin) * genRealP();
        const Real t = (aMin + (aMax - aMin) * genRealP()) * static_cast<Real>(2.0) * flowerpot::math::pi();

        const RVec2 xy = r * RVec2(std::cos(t), std::sin(t));
        const Real z = std::sqrt(std::max(static_cast<Real>(0.0), static_cast<Real>(1.0) - xy.dot(xy)));

        // TODO See if the normalization is necessary.
        const RVec3 uAxis = util::genPerpendicular(normal);
        const RVec3 vAxis = normal.cross(uAxis).normal();

        return xy.x * uAxis + xy.y * vAxis + z * normal;
    }
};

#endif /* RAYMARCHER_RGEN_HPP */

