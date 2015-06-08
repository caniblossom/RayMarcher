/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_SURFACE_HPP
#define FLOWERPOT_SURFACE_HPP

#include <string>

#include "../array/array2.hpp"
#include "rgba32.hpp"

namespace flowerpot {
    class Surface : public Array2<RGBA32> {
        public:
            Surface() {}
            Surface(const unsigned width, const unsigned height);

            void readPNG(const std::string& filename);
            void writePNG(const std::string& filename) const;
    };

    inline Surface::Surface(const unsigned width, const unsigned height) : Array2(width, height) {}
};

#endif /* FLOWERPOT_SURFACE_HPP */

