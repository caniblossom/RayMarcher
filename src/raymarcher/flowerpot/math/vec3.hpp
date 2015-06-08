/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_VEC3_HPP
#define FLOWERPOT_VEC3_HPP

#include <algorithm>
#include <cmath>

#include "../config/packing.hpp"

#pragma pack(push, FLOWERPOT_FLOATING_POINT_TYPE_PACKING)

namespace flowerpot {
    template <typename T>
    struct Vec3 {
        public:
            T x, y, z;

            Vec3() {}
            Vec3(const T x, const T y, const T z);

            bool operator ==(const Vec3& v) const;
            bool operator !=(const Vec3& v) const;

            Vec3 operator -() const;

            Vec3 operator +(const Vec3& v) const;
            Vec3 operator -(const Vec3& v) const;
            Vec3 operator *(const Vec3& v) const;

            Vec3& operator +=(const Vec3& v);
            Vec3& operator -=(const Vec3& v);
            Vec3& operator *=(const Vec3& v);

            T    dot  (const Vec3& v) const;
            Vec3 cross(const Vec3& v) const;

            T    length() const;
            Vec3 normal() const;

            bool isNumeric() const;
    };

    template <typename T> 
    Vec3<T> operator *(const T& t, const Vec3<T>& v);

    template <typename T> Vec3<T> min(const Vec3<T>& a, const Vec3<T>& b);
    template <typename T> Vec3<T> max(const Vec3<T>& a, const Vec3<T>& b);

    template <typename T>
    Vec3<T>::Vec3(const T x, const T y, const T z) : x(x), y(y), z(z) {}

    template <typename T> 
    bool Vec3<T>::operator ==(const Vec3& v) const { 
        return x == v.x && y == v.y && z == v.z; 
    }
    
    template <typename T> 
    bool Vec3<T>::operator !=(const Vec3& v) const { 
        return x != v.x || y != v.y || z != v.z; 
    }

    template <typename T> 
    Vec3<T> Vec3<T>::operator -() const { 
        return Vec3(-x, -y, -z); 
    }

    template <typename T>
    Vec3<T> Vec3<T>::operator +(const Vec3& v) const { 
        return Vec3(x + v.x, y + v.y, z + v.z); 
    }
    
    template <typename T> 
    Vec3<T> Vec3<T>::operator -(const Vec3& v) const { 
        return Vec3(x - v.x, y - v.y, z - v.z); 
    }
    
    template <typename T> 
    Vec3<T> Vec3<T>::operator *(const Vec3& v) const { 
        return Vec3(x * v.x, y * v.y, z * v.z); 
    }

    template <typename T> 
    Vec3<T>& Vec3<T>::operator +=(const Vec3& v) { 
        *this = *this + v; 
        return *this; 
    }
    
    template <typename T> 
    Vec3<T>& Vec3<T>::operator -=(const Vec3& v) { 
        *this = *this - v; 
        return *this; 
    }
    
    template <typename T> 
    Vec3<T>& Vec3<T>::operator *=(const Vec3& v) { 
        *this = *this * v; 
        return *this; 
    }

    template <typename T>
    T Vec3<T>::dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    template <typename T>
    Vec3<T> Vec3<T>::cross(const Vec3& v) const {
        return Vec3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    template <typename T>
    T Vec3<T>::length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    template <typename T>
    Vec3<T> Vec3<T>::normal() const {
        return (static_cast<T>(1.0) / length()) * *this;
    }

    template <typename T>
    bool Vec3<T>::isNumeric() const {
        return x == x && y == y && z == z;
    }

    template <typename T>
    Vec3<T> operator *(const T& t, const Vec3<T>& v) {
        return Vec3<T>(t * v.x, t * v.y, t * v.z);
    }

    template <typename T>
    Vec3<T> min(const Vec3<T>& a, const Vec3<T>& b) {
        return Vec3<T>(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
    }
    
    template <typename T>
    Vec3<T> max(const Vec3<T>& a, const Vec3<T>& b) {
        return Vec3<T>(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
    }
};

#pragma pack(pop)

#endif /* FLOWERPOT_VEC3_HPP */

