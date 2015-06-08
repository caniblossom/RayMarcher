/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_RENDERWORKER_HPP
#define RAYMARCHER_RENDERWORKER_HPP

#include <atomic>
#include <chrono>
#include <thread>

#include "tracer.hpp"

namespace raymarcher {
    class RenderWorker {
        public:
            RenderWorker(Tracer* _tracer);

            RenderWorker(const RenderWorker& worker)             = delete;
            RenderWorker& operator =(const RenderWorker& worker) = delete;

            void start();
            void stop();

        private:
            RGen    _gen;
            Tracer* _tracer;

            std::thread       _thread;
            std::atomic<bool> _runFlag;

            void run();
    };

    inline RenderWorker::RenderWorker(Tracer* tracer) : _tracer(tracer) {
        assert(tracer);
    }

    inline void RenderWorker::start() {
        _runFlag.store(true);
        _thread = std::thread(run, this);
    }

    inline void RenderWorker::stop() {
        _runFlag.store(false);
        _thread.join();
    }

    inline void RenderWorker::run() {
        while (!_tracer->isFinished() && _runFlag.load()) {
            _tracer->renderNextBlock(_gen);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
};

#endif /* RAYMARCHER_RENDERWORKER_HPP */

