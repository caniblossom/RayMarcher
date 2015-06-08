/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#include <fstream>
#include <thread>

#include "image.hpp"

using namespace std;
using namespace flowerpot;

namespace raymarcher {
    Image::Image(const unsigned width, const unsigned height) : _data(width, height) {
        _data.fill(Sample(RVec3(static_cast<Real>(0.0), static_cast<Real>(0.0), static_cast<Real>(0.0)), static_cast<Real>(1.0 / 256.0)));
    }

    int sampleComponentToPixelComponent(const Real component, const Real exposure) {
        return static_cast<int>(std::max(static_cast<Real>(0.0), std::min(255.0, component * exposure)));
    }

    void Image::toSurface(flowerpot::Surface& surface, const Real exposure) {
        lock_guard<mutex> lock(_dataLock);

        if (surface.getWidth() != getWidth() || surface.getHeight() != surface.getHeight()) {
            surface = Surface(getWidth(), getHeight());
        }

        surface.loop([&](RGBA32& pixel, const int x, const int y) {
            pixel = RGBA32(
                sampleComponentToPixelComponent(at(x, y).color.x, exposure),
                sampleComponentToPixelComponent(at(x, y).color.y, exposure),
                sampleComponentToPixelComponent(at(x, y).color.z, exposure),
                255
            );
        });
    }

    void Image::exportToRaw(const char* file) {
        fstream output(file, ios::binary | ios::out);
        _data.loop([&](const Sample& sample, const int x, const int y) {
            const float data[3] = {
                static_cast<float>(sample.color.x),
                static_cast<float>(sample.color.y),
                static_cast<float>(sample.color.z)
            };

            output.write(reinterpret_cast<const char*>(data), sizeof(float) * 3);
        });
    }
};

