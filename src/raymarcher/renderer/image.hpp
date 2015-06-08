/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_IMAGE_HPP
#define RAYMARCHER_IMAGE_HPP

#include <mutex>

#include "flowerpot/array/array2.hpp"
#include "flowerpot/surface/surface.hpp"

#include "../general/types.hpp"
#include "sample.hpp"

namespace raymarcher {
    class Image {
        public:
            Image() {}
            Image(const unsigned width, const unsigned height);

            bool isNull() const;

            unsigned getWidth() const;
            unsigned getHeight() const;

            void resize(const unsigned width, const unsigned height);

            bool isInside(const int x, const int y) const;

            const Sample& at(const int x, const int y) const;
                  Sample& at(const int x, const int y);

            void accumulate(const int x, const int y, const Sample& sample);

            void toSurface(flowerpot::Surface& surface, const Real exposure);

            void exportToRaw(const char* file);

        private:
            flowerpot::Array2<Sample> _data;
            std::mutex _dataLock;
    };

    inline bool Image::isNull() const {
        return _data.isNull();
    }

    inline unsigned Image::getWidth()  const { return _data.getWidth();  }
    inline unsigned Image::getHeight() const { return _data.getHeight(); }

    inline void Image::resize(const unsigned width, const unsigned height) {
        _data = flowerpot::Array2<Sample>(width, height);
    }

    inline bool Image::isInside(const int x, const int y) const {
        return _data.isInside(x, y);
    }

    inline const Sample& Image::at(const int x, const int y) const { return _data.at(x, y); }
    inline       Sample& Image::at(const int x, const int y)       { return _data.at(x, y); }

    inline void Image::accumulate(const int x, const int y, const Sample& sample) {
        at(x, y) += sample;
    };
};

#endif /* RAYMARCHER_IMAGE_HPP */

