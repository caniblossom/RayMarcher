/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_CYLINDER_HPP
#define RAYMARCHER_CYLINDER_HPP

#include "basiccylinder.hpp"
#include "object.hpp"

namespace raymarcher {
    class Cylinder : public Object, private BasicCylinder {
        public:
            Cylinder(
                const RVec3& center,
                const RVec3& normal,
                const Real radius,
                const Real length
            );

            Real distance (const RVec3& position) const;
            RVec2 mapToUV (const RVec3& position, const RVec3& normal) const;

    };

    inline Cylinder::Cylinder(
        const RVec3& center,
        const RVec3& normal,
        const Real radius,
        const Real length
    ) : BasicCylinder(center, normal, radius, length) {}

    inline Real  Cylinder::distance (const RVec3& position)                      const { return getDistance(position); }
    inline RVec2 Cylinder::mapToUV  (const RVec3& position, const RVec3& normal) const { return getUVFromPosition(position); }
};

#endif /* RAYMARCHER_CYLINDER_HPP */

