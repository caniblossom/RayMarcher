/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef KUKKAGEN_SIMPLEMATERIAL_HPP
#define KUKKAGEN_SIMPLEMATERIAL_HPP

#include "material.hpp"

namespace raymarcher {
    class SimpleMaterial : public Material {
        public:
            SimpleMaterial(const bool isEmissive, const RVec3& color, const Real specularity);

            RVec3 getBaseColor()       const;
            Real  getBaseSpecularity() const;

        private:
            RVec3 _color;
            Real  _specularity;
    };

    inline SimpleMaterial::SimpleMaterial(const bool isEmissive, const RVec3& color, const Real specularity) :
        Material(Material::Type::Simple, isEmissive), _color(color), _specularity(specularity) {}

    inline RVec3 SimpleMaterial::getBaseColor()       const { return _color; }
    inline Real  SimpleMaterial::getBaseSpecularity() const { return _specularity; }
};

#endif /* KUKKAGEN_SIMPLEMATERIAL_HPP */

