/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_MAINWINDOW_HPP
#define RAYMARCHER_MAINWINDOW_HPP

#include <memory>
#include <vector>

#include "flowerpot/surface/surface.hpp"
#include "flowerpot/window/window.hpp"
#include "flowerpot/window/windowmanager.hpp"

#include "../object/checkermaterial.hpp"
#include "../object/simplematerial.hpp"
#include "../object/material.hpp"
#include "../object/cylinder.hpp"
#include "../object/sphere.hpp"
#include "../object/scene.hpp"
#include "../renderer/camera.hpp"
#include "../renderer/image.hpp"
#include "../renderer/tracer.hpp"
#include "../renderer/renderworker.hpp"

#include "surfacerenderer.hpp"

namespace raymarcher {
    class MainWindow : public flowerpot::Window {
        public:
            MainWindow();
            ~MainWindow();

            void onUpdate();

        private:
            static const unsigned WIDTH  = 1920;
            static const unsigned HEIGHT = 1080;

            static const unsigned THREAD_COUNT = 4;

            std::unique_ptr<SurfaceRenderer> _surfaceRenderer;
            flowerpot::Surface             _softSurface;

            std::vector<std::unique_ptr<Object>>   _objectList;
            std::vector<std::unique_ptr<Material>> _materialList;

            Scene _scene;
            Image _image;

            Tracer _tracer;
            std::vector<std::unique_ptr<RenderWorker>> _renderWorkerList;

            void setupRenderTest();
            void renderTest();

            // TODO Remove.
            std::uint32_t _time;
    };
};

#endif /* RAYMARCHER_MAINWINDOW_HPP */

