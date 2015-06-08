/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_BASICSPHERE_HPP
#define RAYMARCHER_BASICSPHERE_HPP

#include "../general/types.hpp"

namespace raymarcher {
    class BasicSphere {
        public:
            BasicSphere(
                const RVec3& center,
                const Real radius
            );

            Real  getDistance(const RVec3& position) const;
            RVec2 getUVFromPosition(const RVec3& position) const;

        public:
            RVec3 _center;
            Real  _radius;
    };

    inline BasicSphere::BasicSphere(const RVec3& center, const Real radius) : _center(center), _radius(radius) {}

    inline Real BasicSphere::getDistance(const RVec3& position) const {
        const RVec3 local = position - _center;
        return local.length() - _radius;
    }

    // TODO Implement this.
    inline RVec2 BasicSphere::getUVFromPosition(const RVec3& position) const {
        return RVec2(static_cast<Real>(0.0), static_cast<Real>(0.0));
    }
};

#endif /* RAYMARCHER_BASICSPHERE_HPP */

