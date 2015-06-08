/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_MAT4_HPP
#define FLOWERPOT_MAT4_HPP

#include <array>
#include <cmath>

#include "../config/packing.hpp"
#include "vec3.hpp"

#pragma pack(push, FLOWERPOT_FLOATING_POINT_TYPE_PACKING)

namespace flowerpot {
    template <typename T>
    class Mat4 {
        public:
            static const int X0 = 0, X1 = 4, X2 = 8,  X3 = 12;
            static const int Y0 = 1, Y1 = 5, Y2 = 9,  Y3 = 13;
            static const int Z0 = 2, Z1 = 6, Z2 = 10, Z3 = 14;
            static const int W0 = 3, W1 = 7, W2 = 11, W3 = 15;

            static Mat4 identity();

            static Mat4 translation(const T x, const T y, const T z);
            static Mat4 scaling    (const T x, const T y, const T z);
            static Mat4 rotation   (const T r, const T x, const T y, const T z);

            static Mat4 projection(const T fovY, const T aspectRatio, const T near, const T far);
            static Mat4 orthoProjection(const T left, const T right, const T bottom, const T top, const T near, const T far);

            Mat4() {}

            template <typename... E>
            Mat4(E... e);

            const T* data() const;
                  T* data();

            const T& operator [](const int i) const;
                  T& operator [](const int i);

            bool operator ==(const Mat4& m) const;
            bool operator !=(const Mat4& m) const;

            Mat4 operator +(const Mat4& m) const;
            Mat4 operator -(const Mat4& m) const;
            Mat4 operator *(const Mat4& m) const;

            Mat4& operator +=(const Mat4& m);
            Mat4& operator -=(const Mat4& m);
            Mat4& operator *=(const Mat4& m);

            T    determinant() const;
            Mat4 transpose() const;
            Mat4 inverse() const;

            void translate(const T x, const T y, const T z);
            void scale    (const T x, const T y, const T z);
            void rotate   (const T r, const T x, const T y, const T z);

            Vec3<T> transform(const Vec3 <T> v) const;

            bool isNumeric() const;

        private:
            std::array<T, 16> _e;
    };

    template <typename T>
    Mat4<T> Mat4<T>::identity() {
        const T n = static_cast<T>(0.0);
        const T u = static_cast<T>(1.0);

        return Mat4(
            u, n, n, n,
            n, u, n, n,
            n, n, u, n,
            n, n, n, u
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::translation(const T x, const T y, const T z) {
        const T n = static_cast<T>(0.0);
        const T u = static_cast<T>(1.0);

        return Mat4(
                u, n, n, n,
                n, u, n, n,
                n, n, u, n,
                x, y, z, u
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::scaling(const T x, const T y, const T z) {
        const T n = static_cast<T>(0.0);
        const T u = static_cast<T>(1.0);

        return Mat4(
                x, n, n, n,
                n, y, n, n,
                n, n, z, n,
                n, n, n, u
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::rotation(const T r, const T x, const T y, const T z) {
        const T n = static_cast<T>(0.0);
        const T u = static_cast<T>(1.0);

        const T c = std::cos(r);
        const T s = std::sin(r);
        const T t = static_cast<T>(1.0) - c;

        return Mat4(
            t * x * x + c,     t * x * y + s * z, t * x * z - s * y, n,
            t * x * y - s * z, t * y * y + c,     t * y * z + s * x, n,
            t * x * z + s * y, t * y * z - s * x, t * z * z + c,     n,
            n,                 n,                 n,                 u
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::projection(const T fov, const T aspectRatio, const T near, const T far) {
        const T n = static_cast<T>(0.0);
        const T u = static_cast<T>(1.0);

        const T r = static_cast<T>(0.5) * fov;
        const T yScale = static_cast<T>(1.0) / std::tan(r);
        const T xScale = yScale / aspectRatio;
        const T length = far - near;

        return Mat4(
                xScale, n,       n,                                          n,
                n,      yScale,  n,                                          n,
                n,      n,      -(far + near) / length,                     -u,
                n,      n,      -static_cast<T>(2.0) * near * far / length,  n
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::orthoProjection(const T left, const T right, const T bottom, const T top, const T near, const T far) {
        const T n = static_cast<T>(0.0);
        const T u = static_cast<T>(1.0);

        const T rl =  static_cast<T>(2.0) / (right - left);
        const T tb =  static_cast<T>(2.0) / (top   - bottom);
        const T fn = -static_cast<T>(2.0) / (far   - near);

        const T tx = -(right + left) / (right - left);
        const T ty = -(top + bottom) / (top - bottom);
        const T tz = -(far + near)   / (far - near);

        return Mat4(
            rl,  n,  n, n,
            n,  tb,  n, n,
            n,   n, fn, n,
            tx, ty, tz, u
        );
    }

    template <typename T>
    template <typename... E>
    Mat4<T>::Mat4(E... e) : _e{{e...}} {}

    template <typename T> 
    const T* Mat4<T>::data() const { 
        return _e.data(); 
    }
    
    template <typename T> 
    T* Mat4<T>::data() { 
        return _e.data(); 
    }

    template <typename T> 
    const T& Mat4<T>::operator [](const int i) const { 
        return _e[i]; 
    }
    
    template <typename T> 
    T& Mat4<T>::operator [](const int i) { 
        return _e[i]; 
    }

    template <typename T>
    bool Mat4<T>::operator ==(const Mat4& m) const {
        return (
            _e[X0] == m._e[X0] && _e[Y0] == m._e[Y0] && _e[Z0] == m._e[Z0] && _e[W0] == m._e[W0] &&
            _e[X1] == m._e[X1] && _e[Y1] == m._e[Y1] && _e[Z1] == m._e[Z1] && _e[W1] == m._e[W1] &&
            _e[X2] == m._e[X2] && _e[Y2] == m._e[Y2] && _e[Z2] == m._e[Z2] && _e[W2] == m._e[W2] &&
            _e[X3] == m._e[X3] && _e[Y3] == m._e[Y3] && _e[Z3] == m._e[Z3] && _e[W3] == m._e[W3]
        );
    }

    template <typename T>
    bool Mat4<T>::operator !=(const Mat4& m) const {
        return (
            _e[X0] != m._e[X0] || _e[Y0] != m._e[Y0] || _e[Z0] != m._e[Z0] || _e[W0] != m._e[W0] ||
            _e[X1] != m._e[X1] || _e[Y1] != m._e[Y1] || _e[Z1] != m._e[Z1] || _e[W1] != m._e[W1] ||
            _e[X2] != m._e[X2] || _e[Y2] != m._e[Y2] || _e[Z2] != m._e[Z2] || _e[W2] != m._e[W2] ||
            _e[X3] != m._e[X3] || _e[Y3] != m._e[Y3] || _e[Z3] != m._e[Z3] || _e[W3] != m._e[W3]
        );
    }

    template <typename T>
    Mat4<T> operator *(const T t, const Mat4<T>& m) {
        return Mat4<T>(
            t * m[Mat4<T>::X0], t * m[Mat4<T>::Y0], t * m[Mat4<T>::Z0], t * m[Mat4<T>::W0],
            t * m[Mat4<T>::X1], t * m[Mat4<T>::Y1], t * m[Mat4<T>::Z1], t * m[Mat4<T>::W1],
            t * m[Mat4<T>::X2], t * m[Mat4<T>::Y2], t * m[Mat4<T>::Z2], t * m[Mat4<T>::W2],
            t * m[Mat4<T>::X3], t * m[Mat4<T>::Y3], t * m[Mat4<T>::Z3], t * m[Mat4<T>::W3]
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::operator +(const Mat4& m) const {
        return Mat4(
            _e[X0] + m._e[X0], _e[Y0] + m._e[Y0], _e[Z0] + m._e[Z0], _e[W0] + m._e[W0],
            _e[X1] + m._e[X1], _e[Y1] + m._e[Y1], _e[Z1] + m._e[Z1], _e[W1] + m._e[W1],
            _e[X2] + m._e[X2], _e[Y2] + m._e[Y2], _e[Z2] + m._e[Z2], _e[W2] + m._e[W2],
            _e[X3] + m._e[X3], _e[Y3] + m._e[Y3], _e[Z3] + m._e[Z3], _e[W3] + m._e[W3]
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::operator -(const Mat4& m) const {
         return Mat4(
            _e[X0] - m._e[X0], _e[Y0] - m._e[Y0], _e[Z0] - m._e[Z0], _e[W0] - m._e[W0],
            _e[X1] - m._e[X1], _e[Y1] - m._e[Y1], _e[Z1] - m._e[Z1], _e[W1] - m._e[W1],
            _e[X2] - m._e[X2], _e[Y2] - m._e[Y2], _e[Z2] - m._e[Z2], _e[W2] - m._e[W2],
            _e[X3] - m._e[X3], _e[Y3] - m._e[Y3], _e[Z3] - m._e[Z3], _e[W3] - m._e[W3]
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::operator *(const Mat4& m) const {
        return Mat4(
            _e[X0] * m._e[X0] + _e[X1] * m._e[Y0] + _e[X2] * m._e[Z0] + _e[X3] * m._e[W0],
            _e[Y0] * m._e[X0] + _e[Y1] * m._e[Y0] + _e[Y2] * m._e[Z0] + _e[Y3] * m._e[W0],
            _e[Z0] * m._e[X0] + _e[Z1] * m._e[Y0] + _e[Z2] * m._e[Z0] + _e[Z3] * m._e[W0],
            _e[W0] * m._e[X0] + _e[W1] * m._e[Y0] + _e[W2] * m._e[Z0] + _e[W3] * m._e[W0],
            _e[X0] * m._e[X1] + _e[X1] * m._e[Y1] + _e[X2] * m._e[Z1] + _e[X3] * m._e[W1],
            _e[Y0] * m._e[X1] + _e[Y1] * m._e[Y1] + _e[Y2] * m._e[Z1] + _e[Y3] * m._e[W1],
            _e[Z0] * m._e[X1] + _e[Z1] * m._e[Y1] + _e[Z2] * m._e[Z1] + _e[Z3] * m._e[W1],
            _e[W0] * m._e[X1] + _e[W1] * m._e[Y1] + _e[W2] * m._e[Z1] + _e[W3] * m._e[W1],
            _e[X0] * m._e[X2] + _e[X1] * m._e[Y2] + _e[X2] * m._e[Z2] + _e[X3] * m._e[W2],
            _e[Y0] * m._e[X2] + _e[Y1] * m._e[Y2] + _e[Y2] * m._e[Z2] + _e[Y3] * m._e[W2],
            _e[Z0] * m._e[X2] + _e[Z1] * m._e[Y2] + _e[Z2] * m._e[Z2] + _e[Z3] * m._e[W2],
            _e[W0] * m._e[X2] + _e[W1] * m._e[Y2] + _e[W2] * m._e[Z2] + _e[W3] * m._e[W2],
            _e[X0] * m._e[X3] + _e[X1] * m._e[Y3] + _e[X2] * m._e[Z3] + _e[X3] * m._e[W3],
            _e[Y0] * m._e[X3] + _e[Y1] * m._e[Y3] + _e[Y2] * m._e[Z3] + _e[Y3] * m._e[W3],
            _e[Z0] * m._e[X3] + _e[Z1] * m._e[Y3] + _e[Z2] * m._e[Z3] + _e[Z3] * m._e[W3],
            _e[W0] * m._e[X3] + _e[W1] * m._e[Y3] + _e[W2] * m._e[Z3] + _e[W3] * m._e[W3]
        );
    }

    template <typename T> 
    Mat4<T>& Mat4<T>::operator +=(const Mat4& m) { 
        *this = *this + m; 
        return *this; 
    }
    
    template <typename T>
    Mat4<T>& Mat4<T>::operator -=(const Mat4& m) { 
        *this = *this - m; 
        return *this; 
    }
    
    template <typename T> 
    Mat4<T>& Mat4<T>::operator *=(const Mat4& m) { 
        *this = *this * m; 
        return *this; 
    }

    template <typename T>
    T Mat4<T>::determinant() const {
        return (
            _e[X0] * _e[Y1] * _e[Z2] * _e[W3] + _e[X0] * _e[Y2] * _e[Z3] * _e[W1] +  _e[X0] * _e[Y3] * _e[Z1] * _e[W2] +
            _e[X1] * _e[Y0] * _e[Z3] * _e[W2] + _e[X1] * _e[Y2] * _e[Z0] * _e[W3] +  _e[X1] * _e[Y3] * _e[Z2] * _e[W0] +
            _e[X2] * _e[Y0] * _e[Z1] * _e[W3] + _e[X2] * _e[Y1] * _e[Z3] * _e[W0] +  _e[X2] * _e[Y3] * _e[Z0] * _e[W1] +
            _e[X3] * _e[Y0] * _e[Z2] * _e[W1] + _e[X3] * _e[Y1] * _e[Z0] * _e[W2] +  _e[X3] * _e[Y2] * _e[Z1] * _e[W0] -
            _e[X0] * _e[Y1] * _e[Z3] * _e[W2] - _e[X0] * _e[Y2] * _e[Z1] * _e[W3] -  _e[X0] * _e[Y3] * _e[Z2] * _e[W1] -
            _e[X1] * _e[Y0] * _e[Z2] * _e[W3] - _e[X1] * _e[Y2] * _e[Z3] * _e[W0] -  _e[X1] * _e[Y3] * _e[Z0] * _e[W2] -
            _e[X2] * _e[Y0] * _e[Z3] * _e[W1] - _e[X2] * _e[Y1] * _e[Z0] * _e[W3] -  _e[X2] * _e[Y3] * _e[Z1] * _e[W0] -
            _e[X3] * _e[Y0] * _e[Z1] * _e[W2] - _e[X3] * _e[Y1] * _e[Z2] * _e[W0] -  _e[X3] * _e[Y2] * _e[Z0] * _e[W1]
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::transpose() const {
        return Mat4(
            _e[X0], _e[X1], _e[X2], _e[X3],
            _e[Y0], _e[Y1], _e[Y2], _e[Y3],
            _e[Z0], _e[Z1], _e[Z2], _e[Z3],
            _e[W0], _e[W1], _e[W2], _e[W3]
        );
    }

    template <typename T>
    Mat4<T> Mat4<T>::inverse() const {
        const T invDet = static_cast<T>(1.0) / determinant();

        return invDet * Mat4(
            _e[Y1] * _e[Z2] * _e[W3] + _e[Y2] * _e[Z3] * _e[W1] + _e[Y3] * _e[Z1] * _e[W2] - _e[Y1] * _e[Z3] * _e[W2] - _e[Y2] * _e[Z1] * _e[W3] - _e[Y3] * _e[Z2] * _e[W1],
            _e[Y0] * _e[Z3] * _e[W2] + _e[Y2] * _e[Z0] * _e[W3] + _e[Y3] * _e[Z2] * _e[W0] - _e[Y0] * _e[Z2] * _e[W3] - _e[Y2] * _e[Z3] * _e[W0] - _e[Y3] * _e[Z0] * _e[W2],
            _e[Y0] * _e[Z1] * _e[W3] + _e[Y1] * _e[Z3] * _e[W0] + _e[Y3] * _e[Z0] * _e[W1] - _e[Y0] * _e[Z3] * _e[W1] - _e[Y1] * _e[Z0] * _e[W3] - _e[Y3] * _e[Z1] * _e[W0],
            _e[Y0] * _e[Z2] * _e[W1] + _e[Y1] * _e[Z0] * _e[W2] + _e[Y2] * _e[Z1] * _e[W0] - _e[Y0] * _e[Z1] * _e[W2] - _e[Y1] * _e[Z2] * _e[W0] - _e[Y2] * _e[Z0] * _e[W1],
            _e[X1] * _e[Z3] * _e[W2] + _e[X2] * _e[Z1] * _e[W3] + _e[X3] * _e[Z2] * _e[W1] - _e[X1] * _e[Z2] * _e[W3] - _e[X2] * _e[Z3] * _e[W1] - _e[X3] * _e[Z1] * _e[W2],
            _e[X0] * _e[Z2] * _e[W3] + _e[X2] * _e[Z3] * _e[W0] + _e[X3] * _e[Z0] * _e[W2] - _e[X0] * _e[Z3] * _e[W2] - _e[X2] * _e[Z0] * _e[W3] - _e[X3] * _e[Z2] * _e[W0],
            _e[X0] * _e[Z3] * _e[W1] + _e[X1] * _e[Z0] * _e[W3] + _e[X3] * _e[Z1] * _e[W0] - _e[X0] * _e[Z1] * _e[W3] - _e[X1] * _e[Z3] * _e[W0] - _e[X3] * _e[Z0] * _e[W1],
            _e[X0] * _e[Z1] * _e[W2] + _e[X1] * _e[Z2] * _e[W0] + _e[X2] * _e[Z0] * _e[W1] - _e[X0] * _e[Z2] * _e[W1] - _e[X1] * _e[Z0] * _e[W2] - _e[X2] * _e[Z1] * _e[W0],
            _e[X1] * _e[Y2] * _e[W3] + _e[X2] * _e[Y3] * _e[W1] + _e[X3] * _e[Y1] * _e[W2] - _e[X1] * _e[Y3] * _e[W2] - _e[X2] * _e[Y1] * _e[W3] - _e[X3] * _e[Y2] * _e[W1],
            _e[X0] * _e[Y3] * _e[W2] + _e[X2] * _e[Y0] * _e[W3] + _e[X3] * _e[Y2] * _e[W0] - _e[X0] * _e[Y2] * _e[W3] - _e[X2] * _e[Y3] * _e[W0] - _e[X3] * _e[Y0] * _e[W2],
            _e[X0] * _e[Y1] * _e[W3] + _e[X1] * _e[Y3] * _e[W0] + _e[X3] * _e[Y0] * _e[W1] - _e[X0] * _e[Y3] * _e[W1] - _e[X1] * _e[Y0] * _e[W3] - _e[X3] * _e[Y1] * _e[W0],
            _e[X0] * _e[Y2] * _e[W1] + _e[X1] * _e[Y0] * _e[W2] + _e[X2] * _e[Y1] * _e[W0] - _e[X0] * _e[Y1] * _e[W2] - _e[X1] * _e[Y2] * _e[W0] - _e[X2] * _e[Y0] * _e[W1],
            _e[X1] * _e[Y3] * _e[Z2] + _e[X2] * _e[Y1] * _e[Z3] + _e[X3] * _e[Y2] * _e[Z1] - _e[X1] * _e[Y2] * _e[Z3] - _e[X2] * _e[Y3] * _e[Z1] - _e[X3] * _e[Y1] * _e[Z2],
            _e[X0] * _e[Y2] * _e[Z3] + _e[X2] * _e[Y3] * _e[Z0] + _e[X3] * _e[Y0] * _e[Z2] - _e[X0] * _e[Y3] * _e[Z2] - _e[X2] * _e[Y0] * _e[Z3] - _e[X3] * _e[Y2] * _e[Z0],
            _e[X0] * _e[Y3] * _e[Z1] + _e[X1] * _e[Y0] * _e[Z3] + _e[X3] * _e[Y1] * _e[Z0] - _e[X0] * _e[Y1] * _e[Z3] - _e[X1] * _e[Y3] * _e[Z0] - _e[X3] * _e[Y0] * _e[Z1],
            _e[X0] * _e[Y1] * _e[Z2] + _e[X1] * _e[Y2] * _e[Z0] + _e[X2] * _e[Y0] * _e[Z1] - _e[X0] * _e[Y2] * _e[Z1] - _e[X1] * _e[Y0] * _e[Z2] - _e[X2] * _e[Y1] * _e[Z0]
        );
    }

    template <typename T>
    void Mat4<T>::translate(const T x, const T y, const T z) {
        *this = translation(x, y, z) * *this;
    }

    template <typename T>
    void Mat4<T>::scale(const T x, const T y, const T z) {
        *this = scaling(x, y, z) * *this;
    }

    template <typename T>
    void Mat4<T>::rotate(const T r, const T x, const T y, const T z) {
        *this = rotation(r, x, y, z) * *this;
    }

    template <typename T>
    Vec3<T> Mat4<T>::transform(const Vec3<T> v) const {
        return Vec3<T>(
            _e[X0] * v.x + _e[X1] * v.y + _e[X2] * v.z + _e[X3],
            _e[Y0] * v.x + _e[Y1] * v.y + _e[Y2] * v.z + _e[Y3],
            _e[Z0] * v.x + _e[Z1] * v.y + _e[Z2] * v.z + _e[Z3]
        );
    }

    template <typename T>
    bool Mat4<T>::isNumeric() const {
        return (
            _e[X0] == _e[X0] && _e[Y0] == _e[Y0] && _e[Z0] == _e[Z0] && _e[W0] == _e[W0] &&
            _e[X1] == _e[X1] && _e[Y1] == _e[Y1] && _e[Z1] == _e[Z1] && _e[W1] == _e[W1] &&
            _e[X2] == _e[X2] && _e[Y2] == _e[Y2] && _e[Z2] == _e[Z2] && _e[W2] == _e[W2] &&
            _e[X3] == _e[X3] && _e[Y3] == _e[Y3] && _e[Z3] == _e[Z3] && _e[W3] == _e[W3]
        );
    }
};

#pragma pack(pop)

#endif /* FLOWERPOT_MAT4_HPP */

