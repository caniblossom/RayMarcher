/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_SCENE_HPP
#define RAYMARCHER_SCENE_HPP

#include <memory>
#include <vector>

#include "../general/types.hpp"
#include "sceneitem.hpp"

namespace raymarcher {
    class Scene {
        public:
            void addItem(const Object* object, const Material* material);
            const std::vector<SceneItem>& getGlobalItemList() const;

        private:
            std::vector<SceneItem> _itemList;
    };

    inline void Scene::addItem(const Object* object, const Material* material) {
        _itemList.push_back(SceneItem(object, material));
    }

    inline const std::vector<SceneItem>& Scene::getGlobalItemList() const {
        return _itemList;
    }
};

#endif /* RAYMARCHER_SCENE_HPP */

