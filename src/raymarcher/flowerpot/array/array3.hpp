/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_ARRAY3_HPP
#define FLOWERPOT_ARRAY3_HPP

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

#include "array3metrics.hpp"

namespace flowerpot {
    template <typename T>
    class Array3 {
        public:
            Array3();
            Array3(const unsigned width, const unsigned height, const unsigned depth);
            virtual ~Array3() {}

            void release();
            void resize(const unsigned width, const unsigned height, const unsigned depth);

            bool isNull() const;

            unsigned getWidth() const;
            unsigned getHeight() const;
            unsigned getDepth() const;

            const std::vector<T>& data() const;
                  std::vector<T>& data();

            bool isInside(const int x, const int y, const int z) const;
            int  index   (const int x, const int y, const int z) const;

            const T& at(const int x, const int y, const int z) const;
                  T& at(const int x, const int y, const int z);

            const T& operator [](const std::size_t index) const;
                  T& operator [](const std::size_t index);

            void fill(const T& t);
            void fill(const T& t, const int dstX, const int dstY, const int dstZ, const unsigned width, const unsigned height, const unsigned depth);

            void copyTo(Array3& target, const int dstX, const int dstY, const int dstZ, const int srcX, const int srcY, const int srcZ, const unsigned width, const unsigned height, const unsigned depth) const;

            void loop(std::function<void (const T& value, const int x, const int y, const int z)> func) const;
            void loop(std::function<void       (T& value, const int x, const int y, const int z)> func);

        private:
            unsigned _width;
            unsigned _height;
            unsigned _depth;

            std::vector<T> _data;
    };

    template <typename T>
    Array3<T>::Array3() : _width(0), _height(0), _depth(0) {}

    template <typename T>
    Array3<T>::Array3(const unsigned width, const unsigned height, const unsigned depth) : _width(width), _height(height), _depth(depth) {
        try { _data.resize(_width * _height * _depth); }
        catch (std::exception& e) {
            release();
            throw;
        }
    }

    template <typename T>
    void Array3<T>::release() {
        _width = 0;
        _height = 0;
        _depth = 0;
        _data.clear();
    }

    template <typename T>
    void Array3<T>::resize(const unsigned width, const unsigned height, const unsigned depth) {
        _width  = width;
        _height = height;
        _depth  = depth;

        try { _data.resize(_width * _height * _depth); }
        catch (std::exception e) {
            release();
            throw;
        }
    }

    template <typename T>
    bool Array3<T>::isNull() const {
        return (_data.size() == 0);
    }

    template <typename T> 
    unsigned Array3<T>::getWidth() const { 
        return _width; 
    }
    
    template <typename T> unsigned Array3<T>::getHeight() const { 
        return _height; 
    }
    
    template <typename T> unsigned Array3<T>::getDepth() const { 
        return _depth; 
    }

    template <typename T> const std::vector<T>& Array3<T>::data() const {
        return _data; 
    }
    
    template <typename T> std::vector<T>& Array3<T>::data() { 
        return _data; 
    }

    template <typename T>
    bool Array3<T>::isInside(const int x, const int y, const int z) const {
        return x >= 0 && x < static_cast<int>(_width) && y >= 0 && y < static_cast<int>(_height) && z >= 0 && z < static_cast<int>(_depth);
    }

    template <typename T>
    int Array3<T>::index(const int x, const int y, const int z) const {
        return x + y * _width + z * _width * _height;
    }

    template <typename T> const T& Array3<T>::at(const int x, const int y, const int z) const { 
        assert(isInside(x, y, z)); 
        return _data[index(x, y, z)]; 
    }
    
    template <typename T> T& Array3<T>::at(const int x, const int y, const int z) { 
        assert(isInside(x, y, z)); 
        return _data[index(x, y, z)]; 
    }

    template <typename T> 
    const T& Array3<T>::operator [](const std::size_t index) const { 
        return _data[index]; 
    }
    
    template <typename T> 
    T& Array3<T>::operator [](const std::size_t index) { 
        return _data[index]; 
    }

    template <typename T>
    void Array3<T>::fill(const T& t) {
        for (T& value : _data) value = t;
    }

    template <typename T>
    void Array3<T>::fill(const T& t, const int dstX, const int dstY, const int dstZ, const unsigned width, const unsigned height, const unsigned depth) {
        if (isNull()) return;
        array::loopPositions3(_width, _height, _depth, dstX, dstY, dstZ, width, height, depth, [&](const int x, const int y, const int z) {
            at(x, y, z) = t;
        });
    }
        
    template <typename T>
    void Array3<T>::copyTo(Array3& target, const int dstX, const int dstY, const int dstZ, const int srcX, const int srcY, const int srcZ, const unsigned width, const unsigned height, const unsigned depth) const {
        if (isNull() || target.isNull() || width == 0 || height == 0 || depth == 0) return;

        const int srcX0 = std::max(0, srcX), srcX1 = std::min(static_cast<int>(_width)         - 1, srcX + static_cast<int>(width)  - 1);
        const int srcY0 = std::max(0, srcY), srcY1 = std::min(static_cast<int>(_height)        - 1, srcY + static_cast<int>(height) - 1);
        const int srcZ0 = std::max(0, srcZ), srcZ1 = std::min(static_cast<int>(_depth)         - 1, srcZ + static_cast<int>(depth)  - 1);
        const int dstX0 = std::max(0, dstX), dstX1 = std::min(static_cast<int>(target._width)  - 1, dstX + static_cast<int>(width)  - 1);
        const int dstY0 = std::max(0, dstY), dstY1 = std::min(static_cast<int>(target._height) - 1, dstY + static_cast<int>(height) - 1);
        const int dstZ0 = std::max(0, dstZ), dstZ1 = std::min(static_cast<int>(target._depth)  - 1, dstZ + static_cast<int>(depth)  - 1);

        const int w = std::min(srcX1 - srcX0, dstX1 - dstX0) + 1;
        const int h = std::min(srcY1 - srcY0, dstY1 - dstY0) + 1;
        const int d = std::min(srcZ1 - srcZ0, dstZ1 - dstZ0) + 1;

        for (int z = 0; z < d; z++) {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    target.at(dstX0 + x, dstY0 + y, dstZ0 + z) = at(srcX0 + x, srcY0 + y, srcZ0 + z);
                }
            }
        }
    }

    template <typename T>
    void Array3<T>::loop(std::function<void (const T& value, const int x, const int y, const int z)> func) const {
        array::loopPositions3(_width, _height, _depth, [&](const int x, const int y, const int z) {
            func(at(x, y, z), x, y, z);
        });
    }

    template <typename T>
    void Array3<T>::loop(std::function<void (T& value, const int x, const int y, const int z)> func) {
        array::loopPositions3(_width, _height, _depth, [&](const int x, const int y, const int z) {
            func(at(x, y, z), x, y, z);
        });
    }
};

#endif /* FLOWERPOT_ARRAY3_HPP */

