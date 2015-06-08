/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_SPHERE_HPP
#define RAYMARCHER_SPHERE_HPP

#include "basicsphere.hpp"
#include "object.hpp"

namespace raymarcher {
    class Sphere : public Object, private BasicSphere {
        public:
            Sphere(const RVec3& center, const Real radius);

            Real distance (const RVec3& position) const;
            RVec2 mapToUV (const RVec3& position, const RVec3& normal) const;
    };

    inline Sphere::Sphere(const RVec3& center, const Real radius) : BasicSphere(center, radius) {}

    inline Real  Sphere::distance (const RVec3& position)                      const { return getDistance(position); }
    inline RVec2 Sphere::mapToUV  (const RVec3& position, const RVec3& normal) const { return getUVFromPosition(position); }
};

#endif /* RAYMARCHER_SPHERE_HPP */

