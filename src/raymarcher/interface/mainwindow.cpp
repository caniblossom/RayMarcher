/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#include <string>
#include "mainwindow.hpp"

using namespace std;
using namespace flowerpot;

namespace raymarcher {
    MainWindow::MainWindow() :
        Window(
            false, false, WIDTH / 4, HEIGHT / 4, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            GLAttributes(8, 8, 8, 8, 16, 0, 3, 3)
        )
    {
        setTitle(string("Raymarcher"));

        Surface icon;
        icon.readPNG(string("icon.png"));
        setIcon(icon);

        _surfaceRenderer = unique_ptr<SurfaceRenderer>(new SurfaceRenderer());
        _softSurface = Surface(WIDTH, HEIGHT);

        glClearDepth(1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        setupRenderTest();
        renderTest();
    }

    MainWindow::~MainWindow() {
        for (unique_ptr<RenderWorker>& worker : _renderWorkerList) {
            worker->stop();
        }
    }

    void MainWindow::onUpdate() {
        static int lazyUpdateCounter = 0;
        static int lazyCounter = 0;

        if (lazyUpdateCounter > 100) {
            lazyUpdateCounter = 0;
            _image.toSurface(_softSurface, 2.0 * 256.0);
            _surfaceRenderer->upload(_softSurface);

            if (_tracer.isFinished()) {
                string filename = string("output") + to_string(lazyCounter) + string("_") + to_string(_time);
                lazyCounter++;
                _image.exportToRaw(filename.c_str());

                for (unique_ptr<RenderWorker>& worker : _renderWorkerList) {
                    worker->stop();
                }
                renderTest();
            }
        }

        lazyUpdateCounter++;

        _surfaceRenderer->render();
        flipDisplayBuffer();
        SDL_Delay(10);
    }

    void MainWindow::setupRenderTest() {
        _image.resize(_softSurface.getWidth(), _softSurface.getHeight());

        _objectList.push_back(unique_ptr<Object>(new Cylinder(RVec3( 0.0, -0.50,  0.00), RVec3( 0.0, 1.0,  0.0),        100.00,   1.00)));
        _objectList.push_back(unique_ptr<Object>(new Cylinder(RVec3( 2.0,  0.50,  0.00), RVec3( 0.0, 1.0,  0.0).normal(), 0.50,   1.00)));
        _objectList.push_back(unique_ptr<Object>(new Sphere(RVec3(-0.8,  0.50,  0.80), 0.50)));
        _objectList.push_back(unique_ptr<Object>(new Cylinder(RVec3(-1.0,  4.0,  -0.50), RVec3( 0.0, 1.0,  0.0).normal(), 2.00,   0.25)));
        _objectList.push_back(unique_ptr<Object>(new Cylinder(RVec3( 2.0,  0.50,  0.00), RVec3( 1.0, 0.0,  1.0).normal(), 0.25,   1.50)));
        _objectList.push_back(unique_ptr<Object>(new Cylinder(RVec3( 2.0,  0.50,  0.00), RVec3( 1.0, 0.0, -1.0).normal(), 0.25,   1.50)));
        _objectList.push_back(unique_ptr<Object>(new Sphere(RVec3(-0.0,  0.50, -0.20), 0.50)));
        _objectList.push_back(unique_ptr<Object>(new Sphere(RVec3(-1.4,  0.50, -0.50), 0.50)));

        _materialList.push_back(unique_ptr<Material>(new CheckeredMaterial(false, RVec3(0.8, 0.8, 0.8), RVec3(0.4, 0.4, 0.4), 0.00, 1.00, RVec2(1.0, 1.0))));
        _materialList.push_back(unique_ptr<Material>(new SimpleMaterial(false, RVec3(0.9, 0.8, 0.8), 0.05)));
        _materialList.push_back(unique_ptr<Material>(new SimpleMaterial(false, RVec3(0.8, 0.8, 1.0), 0.95)));
        _materialList.push_back(unique_ptr<Material>(new SimpleMaterial(true, RVec3(1.5, 1.75, 2.0), 0.95)));
        _materialList.push_back(unique_ptr<Material>(new SimpleMaterial(true, RVec3(8.0, 4.00, 2.0), 0.95)));

        _scene.addItem(_objectList[0].get(), _materialList[0].get());
        _scene.addItem(_objectList[1].get(), _materialList[1].get());
        _scene.addItem(_objectList[2].get(), _materialList[2].get());
        _scene.addItem(_objectList[3].get(), _materialList[3].get());
        _scene.addItem(_objectList[4].get(), _materialList[4].get());
        _scene.addItem(_objectList[5].get(), _materialList[4].get());
        _scene.addItem(_objectList[6].get(), _materialList[2].get());
        _scene.addItem(_objectList[7].get(), _materialList[2].get());

        Camera camera(
            RVec3( 0.50, 3.0, 2.5),
            RVec3( 0.00, 1.0, 0.0),
            RVec3( 0.45, 0.1, 0.0),
            RVec2(static_cast<Real>(WIDTH), static_cast<Real>(HEIGHT)),
            50.0,
            0.05,
            1.00
        );

        _tracer.setImage(&_image);
        _tracer.setScene(&_scene);
        _tracer.setCamera(camera);

        for (unsigned i = 0; i < THREAD_COUNT; i++) {
            _renderWorkerList.push_back(unique_ptr<RenderWorker>(new RenderWorker(&_tracer)));
        }

        chrono::system_clock::time_point now = chrono::system_clock::now();
        _time = static_cast<uint32_t>(chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count());
    }

    void MainWindow::renderTest() {
        _tracer.reset(TracerSettings(32, 32, 1, 3, 3, 3.0));
        for (unique_ptr<RenderWorker>& worker : _renderWorkerList) {
            worker->start();
        }
    }
};

