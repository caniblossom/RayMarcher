/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#include <chrono>
#include <thread>

#include "rgen.hpp"

using namespace std;
using namespace flowerpot;

namespace raymarcher {
    bool  RGen::_seedGenInit = false;
    RNG   RGen::_seedRNG;
    mutex RGen::_seedGenLock;

    uint32_t RGen::genSeed() {
        lock_guard<mutex> lock(_seedGenLock);

        if (!_seedGenInit) {
            _seedGenInit = true;

            chrono::system_clock::time_point now = chrono::system_clock::now();
            _seedRNG = RNG(static_cast<uint32_t>(chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count()));
        }

        return _seedRNG.genUInt();
    }
};

