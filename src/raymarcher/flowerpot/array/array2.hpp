/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_ARRAY2_HPP
#define FLOWERPOT_ARRAY2_HPP

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

#include "array2metrics.hpp"

namespace flowerpot {
    template <typename T>
    class Array2 {
        public:
            Array2();
            Array2(const unsigned width, const unsigned height);
            virtual ~Array2() {}

            void release();
            void resize(const unsigned width, const unsigned height);

            bool isNull() const;

            unsigned getWidth() const;
            unsigned getHeight() const;

            const std::vector<T>& data() const;
                  std::vector<T>& data();

            bool isInside(const int x, const int y) const;
            int  index   (const int x, const int y) const;

            const T& at(const int x, const int y) const;
                  T& at(const int x, const int y);

            const T& operator [](const std::size_t index) const;
                  T& operator [](const std::size_t index);

            void fill(const T& t);
            void fill(const T& t, const int boxX, const int boxY, const unsigned width, const unsigned height);
            
            void copyTo(Array2& target, const int dstX, const int dstY, const int srcX, const int srcY, const unsigned width, const unsigned height) const;

            void loop(std::function<void (const T& value, const int x, const int y)> func) const;
            void loop(std::function<void       (T& value, const int x, const int y)> func);

        private:
            unsigned _width;
            unsigned _height;

            std::vector<T> _data;
    };

    template <typename T>
    Array2<T>::Array2() : _width(0), _height(0) {}

    template <typename T>
    Array2<T>::Array2(const unsigned width, const unsigned height) : _width(width), _height(height) {
        try { _data.resize(_width * _height); }
        catch (std::exception& e) {
            release();
            throw;
        }
    }

    template <typename T>
    void Array2<T>::release() {
        _width = 0;
        _height = 0;
        _data.clear();
    }

    template <typename T>
    void Array2<T>::resize(const unsigned width, const unsigned height) {
        _width  = width;
        _height = height;

        try { _data.resize(_width * _height); }
        catch (std::exception e) {
            release();
            throw;
        }
    }

    template <typename T>
    bool Array2<T>::isNull() const {
        return (_data.size() == 0);
    }

    template <typename T> 
    unsigned Array2<T>::getWidth() const { 
        return _width; 
    }
    
    template <typename T> 
    unsigned Array2<T>::getHeight() const { 
        return _height; 
    }

    template <typename T> 
    const std::vector<T>& Array2<T>::data() const { 
        return _data; 
    }
    
    template <typename T> 
    std::vector<T>& Array2<T>::data() { 
        return _data; 
    }

    template <typename T>
    bool Array2<T>::isInside(const int x, const int y) const {
        return x >= 0 && x < static_cast<int>(_width) && y >= 0 && y < static_cast<int>(_height);
    }

    template <typename T>
    int Array2<T>::index(const int x, const int y) const {
        return x + y * _width;
    }

    template <typename T> 
    const T& Array2<T>::at(const int x, const int y) const { 
        assert(isInside(x, y));
        return _data[index(x, y)]; 
    }
    
    template <typename T>       
    T& Array2<T>::at(const int x, const int y) { 
        assert(isInside(x, y)); 
        return _data[index(x, y)]; 
    }

    template <typename T> 
    const T& Array2<T>::operator [](const std::size_t index) const { 
        return _data[index]; 
    }
    
    template <typename T> 
    T& Array2<T>::operator [](const std::size_t index) { 
        return _data[index]; 
    }

    template <typename T>
    void Array2<T>::fill(const T& t) {
        for (T& value : _data) value = t;
    }
    
    template <typename T>
    void Array2<T>::fill(const T& t, const int boxX, const int boxY, const unsigned width, const unsigned height) {
        if (isNull()) return;
        array::loopPositions2(_width, _height, boxX, boxY, width, height, [&](const int x, const int y) {
            at(x, y) = t;
        });   
    }

    template <typename T>
    void Array2<T>::copyTo(Array2& target, const int dstX, const int dstY, const int srcX, const int srcY, const unsigned width, const unsigned height) const {
        if (isNull() || target.isNull() || width == 0 || height == 0) return;

        const int srcX0 = std::max(0, srcX), srcX1 = std::min(static_cast<int>(_width)         - 1, srcX + static_cast<int>(width)  - 1);
        const int srcY0 = std::max(0, srcY), srcY1 = std::min(static_cast<int>(_height)        - 1, srcY + static_cast<int>(height) - 1);
        const int dstX0 = std::max(0, dstX), dstX1 = std::min(static_cast<int>(target._width)  - 1, dstX + static_cast<int>(width)  - 1);
        const int dstY0 = std::max(0, dstY), dstY1 = std::min(static_cast<int>(target._height) - 1, dstY + static_cast<int>(height) - 1);

        const int w = std::min(srcX1 - srcX0, dstX1 - dstX0) + 1;
        const int h = std::min(srcY1 - srcY0, dstY1 - dstY0) + 1;

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                target.at(dstX0 + x, dstY0 + y) = at(srcX0 + x, srcY0 + y);
            }
        }
    }

    template <typename T>
    void Array2<T>::loop(std::function<void (const T& value, const int x, const int y)> func) const {
        array::loopPositions2(_width, _height, [&](const int x, const int y) {
            func(at(x, y), x, y);
        });
    }

    template <typename T>
    void Array2<T>::loop(std::function<void (T& value, const int x, const int y)> func) {
        array::loopPositions2(_width, _height, [&](const int x, const int y) {
            func(at(x, y), x, y);
        });
    }
};

#endif /* FLOWERPOT_ARRAY2_HPP */

