/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_STATICARRAY3_HPP
#define FLOWERPOT_STATICARRAY3_HPP

#include <array>
#include <cassert>
#include <functional>

#include "array3metrics.hpp"

namespace flowerpot {
    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH>
    class StaticArray3 {
        public:
            unsigned getWidth() const;
            unsigned getHeight() const;
            unsigned getDepth() const;

            const std::array<T, WIDTH * HEIGHT * DEPTH>& data() const;
                  std::array<T, WIDTH * HEIGHT * DEPTH>& data();

            static bool isInside(const int x, const int y, const int z);
            static int  index   (const int x, const int y, const int z);

            const T& at(const int x, const int y, const int z) const;
                  T& at(const int x, const int y, const int z);

            const T& operator [](const std::size_t index) const;
                  T& operator [](const std::size_t index);

            void fill(const T& t);
            void fill(const T& t, const int boxX, const int boxY, const int boxZ, const unsigned width, const unsigned height, const unsigned depth);

            void loop(std::function<void (const T& value, const int x, const int y, const int z)> func) const;
            void loop(std::function<void       (T& value, const int x, const int y, const int z)> func);

        private:
            std::array<T, WIDTH * HEIGHT * DEPTH> _data;
    };

    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH> 
    unsigned StaticArray3<T, WIDTH, HEIGHT, DEPTH>::getWidth() const { 
        return WIDTH; 
    }
    
    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH> 
    unsigned StaticArray3<T, WIDTH, HEIGHT, DEPTH>::getHeight() const { 
        return HEIGHT; 
    }
    
    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH> 
    unsigned StaticArray3<T, WIDTH, HEIGHT, DEPTH>::getDepth() const { 
        return DEPTH; 
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH> 
    const std::array<T, WIDTH * HEIGHT * DEPTH>& StaticArray3<T, WIDTH, HEIGHT, DEPTH>::data() const { 
        return _data; 
    }
    
    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH> 
    std::array<T, WIDTH * HEIGHT * DEPTH>& StaticArray3<T, WIDTH, HEIGHT, DEPTH>::data() { 
        return _data; 
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH>
    bool StaticArray3<T, WIDTH, HEIGHT, DEPTH>::isInside(const int x, const int y, const int z) {
        return x >= 0 && x < static_cast<int>(WIDTH) && y >= 0 && y < static_cast<int>(HEIGHT) && z >= 0 && z < static_cast<int>(DEPTH);
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH>
    int StaticArray3<T, WIDTH, HEIGHT, DEPTH>::index(const int x, const int y, const int z) {
        return x + y * WIDTH + z * WIDTH * HEIGHT;
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH> 
    const T& StaticArray3<T, WIDTH, HEIGHT, DEPTH>::at(const int x, const int y, const int z) const { 
        assert(isInside(x, y, z)); 
        return _data[index(x, y, z)]; 
    }
    
    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH> 
    T& StaticArray3<T, WIDTH, HEIGHT, DEPTH>::at(const int x, const int y, const int z) { 
        assert(isInside(x, y, z)); 
        return _data[index(x, y, z)]; 
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH> 
    const T& StaticArray3<T, WIDTH, HEIGHT, DEPTH>::operator [](const std::size_t index) const {
        return _data[index]; 
    }
    
    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH> 
    T& StaticArray3<T, WIDTH, HEIGHT, DEPTH>::operator [](const std::size_t index) { 
        return _data[index]; 
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH>
    void StaticArray3<T, WIDTH, HEIGHT, DEPTH>::fill(const T& t) {
        for (T& value : _data) value = t;
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH>
    void StaticArray3<T, WIDTH, HEIGHT, DEPTH>::fill(const T& t, const int boxX, const int boxY, const int boxZ, const unsigned width, const unsigned height, const unsigned depth) {
        array::loopPositions3(WIDTH, HEIGHT, DEPTH, boxX, boxY, boxZ, width, height, depth, [&](const int x, const int y, const int z) {
            at(x, y, z) = t;
        });
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH>
    void StaticArray3<T, WIDTH, HEIGHT, DEPTH>::loop(std::function<void (const T& value, const int x, const int y, const int z)> func) const {
        array::loopPositions3(WIDTH, HEIGHT, DEPTH, [&](const int x, const int y, const int z) {
            func(at(x, y, z), x, y, z);
        });
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT, unsigned DEPTH>
    void StaticArray3<T, WIDTH, HEIGHT, DEPTH>::loop(std::function<void (T& value, const int x, const int y, const int z)> func) {
        array::loopPositions3(WIDTH, HEIGHT, DEPTH, [&](const int x, const int y, const int z) {
            func(at(x, y, z), x, y, z);
        });
    }
};

#endif /* FLOWERPOT_STATICARRAY3_HPP */

