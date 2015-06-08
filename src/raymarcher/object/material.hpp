/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef KUKKAGEN_MATERIAL_HPP
#define KUKKAGEN_MATERIAL_HPP

#include "../general/types.hpp"

namespace raymarcher {
    class Material {
        public:
            // TODO Source should be a property, not type.
            enum class Type {
                Simple,
                Mapped
            };

            Material(const Type type, const bool isEmissive);

            Type getType() const;
            bool isEmissive() const;

            virtual RVec3 getBaseColor()       const;
            virtual Real  getBaseSpecularity() const;

            virtual RVec3 getMappedColor       (const RVec2 uv) const;
            virtual Real  getMappedSpecularity (const RVec2 uv) const;

        private:
            Type _type;
            bool _isEmissive;
    };

    inline Material::Material(const Type type, const bool isEmissive) : _type(type), _isEmissive(isEmissive) {}

    inline Material::Type Material::getType() const {
        return _type;
    }

    inline bool Material::isEmissive() const {
        return _isEmissive;
    }

    inline RVec3 Material::getBaseColor()       const { return RVec3(static_cast<Real>(1024.0), static_cast<Real>(0.0), static_cast<Real>(1024.0)); }
    inline Real  Material::getBaseSpecularity() const { return 1.0; }

    inline RVec3 Material::getMappedColor       (const RVec2 uv) const { return getBaseColor(); }
    inline Real  Material::getMappedSpecularity (const RVec2 uv) const { return getBaseSpecularity(); }

};

#endif /* KUKKAGEN_MATERIAL_HPP */

