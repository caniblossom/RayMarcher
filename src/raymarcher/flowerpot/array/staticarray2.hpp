/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

/*
 * A template for a static two dimensional array.
 */

#ifndef FLOWERPOT_STATICARRAY2_HPP
#define FLOWERPOT_STATICARRAY2_HPP

#include <array>
#include <cassert>
#include <functional>

#include "array2metrics.hpp"

namespace flowerpot {
    template <typename T, unsigned WIDTH, unsigned HEIGHT>
    class StaticArray2 {
        public:
            unsigned getWidth() const;
            unsigned getHeight() const;

            const std::array<T, WIDTH * HEIGHT>& data() const;
                  std::array<T, WIDTH * HEIGHT>& data();

            static bool isInside(const int x, const int y);
            static int  index   (const int x, const int y);

            const T& at(const int x, const int y) const;
                  T& at(const int x, const int y);

            const T& operator [](const std::size_t index) const;
                  T& operator [](const std::size_t index);

            void fill(const T& t);
            void fill(const T& t, const int boxX, const int boxY, const unsigned width, const unsigned height);

            void loop(std::function<void (const T& value, const int x, const int y)> func) const;
            void loop(std::function<void       (T& value, const int x, const int y)> func);

        private:
            std::array<T, WIDTH * HEIGHT> _data;
    };

    template <typename T, unsigned WIDTH, unsigned HEIGHT> 
    unsigned StaticArray2<T, WIDTH, HEIGHT>::getWidth() const { 
        return WIDTH; 
    }
    
    template <typename T, unsigned WIDTH, unsigned HEIGHT> 
    unsigned StaticArray2<T, WIDTH, HEIGHT>::getHeight() const { 
        return HEIGHT; 
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT> 
    const std::array<T, WIDTH * HEIGHT>& StaticArray2<T, WIDTH, HEIGHT>::data() const { 
        return _data; 
    }
    
    template <typename T, unsigned WIDTH, unsigned HEIGHT> 
    std::array<T, WIDTH * HEIGHT>& StaticArray2<T, WIDTH, HEIGHT>::data() { 
        return _data; 
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT>
    bool StaticArray2<T, WIDTH, HEIGHT>::isInside(const int x, const int y) {
        return x >= 0 && x < static_cast<int>(WIDTH) && y >= 0 && y < static_cast<int>(HEIGHT);
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT>
    int StaticArray2<T, WIDTH, HEIGHT>::index(const int x, const int y) {
        return x + y * WIDTH;
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT> 
    const T& StaticArray2<T, WIDTH, HEIGHT>::at(const int x, const int y) const { 
        assert(isInside(x, y)); 
        return _data[index(x, y)]; 
    }
    
    template <typename T, unsigned WIDTH, unsigned HEIGHT> 
    T& StaticArray2<T, WIDTH, HEIGHT>::at(const int x, const int y) { 
        assert(isInside(x, y)); 
        return _data[index(x, y)]; 
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT> 
    const T& StaticArray2<T, WIDTH, HEIGHT>::operator [](const std::size_t index) const { 
        return _data[index]; 
    }
    
    template <typename T, unsigned WIDTH, unsigned HEIGHT> 
    T& StaticArray2<T, WIDTH, HEIGHT>::operator [](const std::size_t index) { 
        return _data[index]; 
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT>
    void StaticArray2<T, WIDTH, HEIGHT>::fill(const T& t) {
        for (T& value : _data) value = t;
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT>
    void StaticArray2<T, WIDTH, HEIGHT>::fill(const T& t, const int boxX, const int boxY, const unsigned width, const unsigned height) {
        array::loopPositions2(WIDTH, HEIGHT, boxX, boxY, width, height, [&](const int x, const int y) {
            at(x, y) = t;
        });
    }
    
    template <typename T, unsigned WIDTH, unsigned HEIGHT>
    void StaticArray2<T, WIDTH, HEIGHT>::loop(std::function<void (const T& value, const int x, const int y)> func) const {
        array::loopPositions2(WIDTH, HEIGHT, [&](const int x, const int y) {
            func(at(x, y), x, y);
        });
    }

    template <typename T, unsigned WIDTH, unsigned HEIGHT>
    void StaticArray2<T, WIDTH, HEIGHT>::loop(std::function<void (T& value, const int x, const int y)> func) {
        array::loopPositions2(WIDTH, HEIGHT, [&](const int x, const int y) {
            func(at(x, y), x, y);
        });
    }
};

#endif /* FLOWERPOT_STATICARRAY2_HPP */

