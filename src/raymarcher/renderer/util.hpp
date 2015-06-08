/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_UTIL_HPP
#define RAYMARCHER_UTIL_HPP

#include <cmath>
#include "../general/types.hpp"

namespace raymarcher {
    namespace util {
        inline RVec3 genPerpendicular(const RVec3& normal) {
            RVec3 tilted;

            // TODO Make a version with less branching.
            if (fabs(normal.x) < fabs(normal.y)) {
                if (fabs(normal.x) < fabs(normal.z)) tilted = RVec3( normal.x, -normal.z,  normal.y);
                else                                 tilted = RVec3(-normal.y,  normal.y,  normal.z);
            }
            else {
                if (fabs(normal.y < normal.z)) tilted = RVec3( normal.z,  normal.y, -normal.x);
                else                           tilted = RVec3(-normal.y,  normal.x,  normal.z);
            }

            return (tilted - (normal.dot(tilted) * normal)).normal();
        }

        inline RVec3 getMirrored(const RVec3& normal, const RVec3& vector) {
            return static_cast<Real>(2.0) * normal.dot(vector) * normal - vector;
        }
    }
};

#endif /* RAYMARCHER_UTIL_HPP */

