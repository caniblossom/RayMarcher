/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_BASICCYLINDER_HPP
#define RAYMARCHER_BASICCYLINDER_HPP

#include <algorithm>
#include "../general/types.hpp"

namespace raymarcher {
    class BasicCylinder {
        public:
            BasicCylinder(
                const RVec3& center,
                const RVec3& normal,
                const Real radius,
                const Real length
            );

            Real  getDistance(const RVec3& position) const;
            RVec2 getUVFromPosition(const RVec3& position) const;

        public:
            RVec3 _center;
            RVec3 _normal;
            Real  _radius;
            Real  _halfLength;
    };

    inline BasicCylinder::BasicCylinder(const RVec3& center, const RVec3& normal, const Real radius, const Real length) :
        _center(center), _normal(normal), _radius(radius), _halfLength(static_cast<Real>(0.5) * length) {}

    inline Real BasicCylinder::getDistance(const RVec3& position) const {
        const RVec3 local = position - _center;
        const Real projection = _normal.dot(local);

        const Real uDist = std::fabs(projection) - _halfLength;
        const Real vDist = (local - (projection * _normal)).length() - _radius;

        return (
            std::min(std::max(uDist, vDist), static_cast<Real>(0.0)) +
            RVec2(std::max(uDist, static_cast<Real>(0.0)), std::max(vDist, static_cast<Real>(0.0))).length()
        );
    }

    inline RVec2 BasicCylinder::getUVFromPosition(const RVec3& position) const {
        const RVec3 local = position - _center;
        const Real projection = _normal.dot(local);

        return RVec2(projection - _halfLength, (local - (projection * _normal)).length() - _radius);
    }
};

#endif /* RAYMARCHER_BASICCYLINDER_HPP */

