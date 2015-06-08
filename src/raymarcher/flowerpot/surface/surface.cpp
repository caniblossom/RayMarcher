/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <stdexcept>

#include "lodepng/lodepng.h"
#include "surface.hpp"

using namespace std;

namespace flowerpot {
    void Surface::readPNG(const std::string& filename) {
        try {
            vector<unsigned char> image;
            unsigned width = 0, height = 0;

            unsigned error = lodepng::decode(image, width, height, filename.c_str());
            if (error) throw runtime_error(lodepng_error_text(error));

            *this = Surface(width, height);
            if (image.size() != 4 * data().size()) throw runtime_error("Surface size mismatch.");

            unsigned ptr = 0;
            loop([&](RGBA32& pixel, const int x, const int y) {
               pixel.r = image[ptr++];
               pixel.g = image[ptr++];
               pixel.b = image[ptr++];
               pixel.a = image[ptr++];
            });
        }
        catch (exception& e) {
            throw runtime_error(string("Couldn't read PNG file: ") + string(filename) + string(", ") + e.what());
        }
    }

    void Surface::writePNG(const std::string& filename) const {
        try {
            vector<unsigned char> image;
            loop([&](const RGBA32& pixel, const int x, const int y) {
               image.push_back(pixel.r);
               image.push_back(pixel.g);
               image.push_back(pixel.b);
               image.push_back(pixel.a);
            });

            unsigned error = lodepng::encode(filename.c_str(), image, getWidth(), getHeight());
            if (error) throw runtime_error(lodepng_error_text(error));
        }
        catch (exception& e) {
            throw runtime_error(string("Couldn't write PNG file: ") + string(filename) + string(", ") + e.what());
        }
    }
};

