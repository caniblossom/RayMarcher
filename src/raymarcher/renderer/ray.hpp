/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_RAY_HPP
#define RAYMARCHER_RAY_HPP

#include "../general/types.hpp"

namespace raymarcher {
    class Ray {
        public:
            RVec3 position;
            RVec3 normal;
            RVec3 color;

            Ray() {}
            Ray(const RVec3& position, const RVec3& normal, const RVec3 color, const Real life);

            void march(const Real& distance);

            bool isAlive() const;
            void payLife(const Real cost);

        private:
            Real _life;
    };

    inline Ray::Ray(const RVec3& position, const RVec3& normal, const RVec3 color, const Real life) :
        position(position), normal(normal), color(color), _life(life)
    {}

    inline bool Ray::isAlive() const {
        return _life > static_cast<Real>(0.0);
    }

    inline void Ray::payLife(const Real cost) {
        _life -= cost;
    }

    inline void Ray::march(const Real& distance) {
        position += distance * normal;
    }
};

#endif /* RAYMARCHER_RAY_HPP */

