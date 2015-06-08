/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_OBJECT_HPP
#define RAYMARCHER_OBJECT_HPP

#include "../general/types.hpp"
#include "material.hpp"

namespace raymarcher {
    class Object {
        public:
            virtual Real  distance (const RVec3& position)                      const = 0;
            virtual RVec2 mapToUV  (const RVec3& position, const RVec3& normal) const = 0;

    };
};

#endif /* RAYMARCHER_OBJECT_HPP */

