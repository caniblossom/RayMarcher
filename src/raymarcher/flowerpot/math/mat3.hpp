/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_MAT3_HPP
#define FLOWERPOT_MAT3_HPP

#include <array>
#include <cmath>

#include "../config/packing.hpp"
#include "vec2.hpp"

#pragma pack(push, FLOWERPOT_FLOATING_POINT_TYPE_PACKING)

namespace flowerpot {
    template <typename T>
    class Mat3 {
        public:
            static const int X0 = 0, X1 = 3, X2 = 6;
            static const int Y0 = 1, Y1 = 4, Y2 = 7;
            static const int Z0 = 2, Z1 = 5, Z2 = 8;

            static Mat3 identity();

            static Mat3 translation(const T x, const T y);
            static Mat3 scaling    (const T x, const T y);
            static Mat3 rotation   (const T r);

            Mat3() {}

            template <typename... E>
            Mat3(E... e);

            const T* data() const;
                  T* data();

            const T& operator [](const int i) const;
                  T& operator [](const int i);

            bool operator ==(const Mat3& m) const;
            bool operator !=(const Mat3& m) const;

            Mat3 operator +(const Mat3& m) const;
            Mat3 operator -(const Mat3& m) const;
            Mat3 operator *(const Mat3& m) const;

            Mat3& operator +=(const Mat3& m);
            Mat3& operator -=(const Mat3& m);
            Mat3& operator *=(const Mat3& m);

            T    determinant() const;
            Mat3 transpose() const;
            Mat3 inverse() const;

            void translate(const T x, const T y);
            void scale    (const T x, const T y);
            void rotate   (const T r);

            Vec2<T> transform(const Vec2<T> v) const;

            bool isNumeric() const;

        private:
            std::array<T, 9> _e;
    };

    template <typename T>
    Mat3<T> Mat3<T>::identity() {
        const T n = static_cast<T>(0.0);
        const T u = static_cast<T>(1.0);

        return Mat3(
            u, n, n,
            n, u, n,
            n, n, u
        );
    }

    template <typename T>
    Mat3<T> Mat3<T>::translation(const T x, const T y) {
        const T n = static_cast<T>(0.0);
        const T u = static_cast<T>(1.0);

        return Mat3(
            u, n, n,
            n, u, n,
            x, y, u
        );
    }

    template <typename T>
    Mat3<T> Mat3<T>::scaling(const T x, const T y) {
        const T n = static_cast<T>(0.0);
        const T u = static_cast<T>(1.0);

        return Mat3(
            x, n, n,
            n, y, n,
            n, n, u
        );
    }

    template <typename T>
    Mat3<T> Mat3<T>::rotation(const T r) {
        const T n = static_cast<T>(0.0);
        const T u = static_cast<T>(1.0);
        const T c = std::cos(r);
        const T s = std::sin(r);

        return Mat3(
             c, s, n,
            -s, c, n,
             n, n, u
        );
    }

    template <typename T>
    template <typename... E>
    Mat3<T>::Mat3(E... e) : _e{{e...}} {}

    template <typename T> 
    const T* Mat3<T>::data() const { 
        return _e.data(); 
    }
    
    template <typename T> 
    T* Mat3<T>::data() { 
        return _e.data(); 
    }

    template <typename T> 
    const T& Mat3<T>::operator [](const int i) const { 
        return _e[i]; 
    }
    
    template <typename T> 
    T& Mat3<T>::operator [](const int i) { 
        return _e[i]; 
    }
    
    template <typename T>
    bool Mat3<T>::operator ==(const Mat3& m) const {
        return (
            _e[X0] == m._e[X0] && _e[Y0] == m._e[Y0] && _e[Z0] == m._e[Z0] &&
            _e[X1] == m._e[X1] && _e[Y1] == m._e[Y1] && _e[Z1] == m._e[Z1] &&
            _e[X2] == m._e[X2] && _e[Y2] == m._e[Y2] && _e[Z2] == m._e[Z2]
         );
    }

    template <typename T>
    bool Mat3<T>::operator !=(const Mat3& m) const {
        return (
            _e[X0] != m._e[X0] || _e[Y0] != m._e[Y0] || _e[Z0] != m._e[Z0] ||
            _e[X1] != m._e[X1] || _e[Y1] != m._e[Y1] || _e[Z1] != m._e[Z1] ||
            _e[X2] != m._e[X2] || _e[Y2] != m._e[Y2] || _e[Z2] != m._e[Z2]
        );
    }

    template <typename T>
    Mat3<T> operator *(const T t, const Mat3<T>& m) {
         return Mat3<T>(
            t * m[Mat3<T>::X0], t * m[Mat3<T>::Y0] * t, t * m[Mat3<T>::Z0],
            t * m[Mat3<T>::X1], t * m[Mat3<T>::Y1] * t, t * m[Mat3<T>::Z1],
            t * m[Mat3<T>::X2], t * m[Mat3<T>::Y2] * t, t * m[Mat3<T>::Z2]
        );
    }

    template <typename T>
    Mat3<T> Mat3<T>::operator +(const Mat3& m) const {
        return Mat3(
            _e[X0] + m._e[X0], _e[Y0] + m._e[Y0], _e[Z0] + m._e[Z0],
            _e[X1] + m._e[X1], _e[Y1] + m._e[Y1], _e[Z1] + m._e[Z1],
            _e[X2] + m._e[X2], _e[Y2] + m._e[Y2], _e[Z2] + m._e[Z2]
        );
    }

    template <typename T>
    Mat3<T> Mat3<T>::operator -(const Mat3& m) const {
         return Mat3(
            _e[X0] - m._e[X0], _e[Y0] - m._e[Y0], _e[Z0] - m._e[Z0],
            _e[X1] - m._e[X1], _e[Y1] - m._e[Y1], _e[Z1] - m._e[Z1],
            _e[X2] - m._e[X2], _e[Y2] - m._e[Y2], _e[Z2] - m._e[Z2]
        );
    }

    template <typename T>
    Mat3<T> Mat3<T>::operator *(const Mat3& m) const {
        return Mat3(
            _e[X0] * m._e[X0] + _e[X1] * m._e[Y0] + _e[X2] * m._e[Z0],
            _e[Y0] * m._e[X0] + _e[Y1] * m._e[Y0] + _e[Y2] * m._e[Z0],
            _e[Z0] * m._e[X0] + _e[Z1] * m._e[Y0] + _e[Z2] * m._e[Z0],
            _e[X0] * m._e[X1] + _e[X1] * m._e[Y1] + _e[X2] * m._e[Z1],
            _e[Y0] * m._e[X1] + _e[Y1] * m._e[Y1] + _e[Y2] * m._e[Z1],
            _e[Z0] * m._e[X1] + _e[Z1] * m._e[Y1] + _e[Z2] * m._e[Z1],
            _e[X0] * m._e[X2] + _e[X1] * m._e[Y2] + _e[X2] * m._e[Z2],
            _e[Y0] * m._e[X2] + _e[Y1] * m._e[Y2] + _e[Y2] * m._e[Z2],
            _e[Z0] * m._e[X2] + _e[Z1] * m._e[Y2] + _e[Z2] * m._e[Z2]
        );
    }

    template <typename T> 
    Mat3<T>& Mat3<T>::operator +=(const Mat3& m) { 
        *this = *this + m; 
        return *this; 
    }
    
    template <typename T> 
    Mat3<T>& Mat3<T>::operator -=(const Mat3& m) { 
        *this = *this - m; 
        return *this; 
    }
    
    template <typename T> 
    Mat3<T>& Mat3<T>::operator *=(const Mat3& m) { 
        *this = *this * m; 
        return *this; 
    }

    template <typename T>
    T Mat3<T>::determinant() const {
        return (
            _e[X0] * _e[Y1] * _e[Z2] +
            _e[Y0] * _e[Z1] * _e[X2] +
            _e[Z0] * _e[X1] * _e[Y2] -
            _e[X0] * _e[Z1] * _e[Y2] -
            _e[Z0] * _e[Y1] * _e[X2] -
            _e[Y0] * _e[X1] * _e[Z2]
        );
    }

    template <typename T>
    Mat3<T> Mat3<T>::transpose() const {
        return Mat3(
            _e[X0], _e[X1], _e[X2],
            _e[Y0], _e[Y1], _e[Y2],
            _e[Z0], _e[Z1], _e[Z2]
        );
    }

    template <typename T>
    Mat3<T> Mat3<T>::inverse() const {
        const T invDet = static_cast<T>(1.0) / determinant();

        return invDet * Mat3(
            _e[Y1] * _e[Z2] - _e[Y2] * _e[Z1],
            _e[Y2] * _e[Z0] - _e[Y0] * _e[Z2],
            _e[Y0] * _e[Z1] - _e[Y1] * _e[Z0],
            _e[X2] * _e[Z1] - _e[X1] * _e[Z2],
            _e[X0] * _e[Z2] - _e[X2] * _e[Z0],
            _e[X1] * _e[Z0] - _e[X0] * _e[Z1],
            _e[X1] * _e[Y2] - _e[X2] * _e[Y1],
            _e[X2] * _e[Y0] - _e[X0] * _e[Y2],
            _e[X0] * _e[Y1] - _e[X1] * _e[Y0]
        );
    }

    template <typename T>
    void Mat3<T>::translate(const T x, const T y) {
        *this = translation(x, y) * *this;
    }

    template <typename T>
    void Mat3<T>::scale(const T x, const T y) {
        *this = scaling(x, y) * *this;
    }

    template <typename T>
    void Mat3<T>::rotate(const T r) {
        *this = rotation(r) * *this;
    }

    template <typename T>
    Vec2<T> Mat3<T>::transform(const Vec2<T> v) const {
        return Vec2<T>(
            _e[X0] * v.x + _e[X1] * v.y + _e[X2],
            _e[Y0] * v.x + _e[Y1] * v.y + _e[Y2]
        );
    }

    template <typename T>
    bool Mat3<T>::isNumeric() const {
        return (
            _e[X0] == _e[X0] && _e[Y0] == _e[Y0] && _e[Z0] == _e[Z0] &&
            _e[X1] == _e[X1] && _e[Y1] == _e[Y1] && _e[Z1] == _e[Z1] &&
            _e[X2] == _e[X2] && _e[Y2] == _e[Y2] && _e[Z2] == _e[Z2]
        );
    }
};

#pragma pack(pop)

#endif /* FLOWERPOT_MAT3_HPP */

