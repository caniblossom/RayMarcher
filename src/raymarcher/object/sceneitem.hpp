/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_SCENEITEM_HPP
#define RAYMARCHER_SCENEITEM_HPP

#include "object.hpp"
#include "material.hpp"

namespace raymarcher {
    class SceneItem {
        public:
            SceneItem(const Object* object = nullptr, const Material* material = nullptr);

            bool isGood() const;

            const Object*   getObject()  const;
            const Material* getMaterial() const;

        private:
            const Object*   _object;
            const Material* _material;

    };

    inline SceneItem::SceneItem(const Object* object, const Material* material) :
        _object(object), _material(material) {}

    inline bool SceneItem::isGood() const {
        return _object && _material;
    }

    inline const Object*   SceneItem::getObject()  const { return _object;  }
    inline const Material* SceneItem::getMaterial() const { return _material; }
};

#endif /* SCENEITEM_HPP */

