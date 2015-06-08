/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_VEC2_HPP
#define FLOWERPOT_VEC2_HPP

#include <algorithm>
#include <cmath>

#include "../config/packing.hpp"

#pragma pack(push, FLOWERPOT_FLOATING_POINT_TYPE_PACKING)

namespace flowerpot {
    template <typename T>
    struct Vec2 {
        public:
            T x, y;

            Vec2() {}
            Vec2(const T x, const T y);

            bool operator ==(const Vec2& v) const;
            bool operator !=(const Vec2& v) const;

            Vec2 operator -() const;

            Vec2 operator +(const Vec2& v) const;
            Vec2 operator -(const Vec2& v) const;
            Vec2 operator *(const Vec2& v) const;

            Vec2& operator +=(const Vec2& v);
            Vec2& operator -=(const Vec2& v);
            Vec2& operator *=(const Vec2& v);

            T dot  (const Vec2& v) const;
            T cross(const Vec2& v) const;

            T    length() const;
            Vec2 normal() const;

            bool isNumeric() const;
    };

    template <typename T> 
    Vec2<T> operator *(const T& t, const Vec2<T>& v);

    template <typename T> Vec2<T> min(const Vec2<T>& a, const Vec2<T>& b);
    template <typename T> Vec2<T> max(const Vec2<T>& a, const Vec2<T>& b);

    template <typename T>
    Vec2<T>::Vec2(const T x, const T y) : x(x), y(y) {}

    template <typename T> 
    bool Vec2<T>::operator ==(const Vec2& v) const { 
        return x == v.x && y == v.y; 
    }
    
    template <typename T> 
    bool Vec2<T>::operator !=(const Vec2& v) const { 
        return x != v.x || y != v.y; 
    }

    template <typename T> 
    Vec2<T> Vec2<T>::operator -() const { 
        return Vec2(-x, -y); 
    }

    template <typename T> 
    Vec2<T> Vec2<T>::operator +(const Vec2& v) const { 
        return Vec2(x + v.x, y + v.y); 
    }
    
    template <typename T> 
    Vec2<T> Vec2<T>::operator -(const Vec2& v) const { 
        return Vec2(x - v.x, y - v.y); 
    }
    
    template <typename T> 
    Vec2<T> Vec2<T>::operator *(const Vec2& v) const { 
        return Vec2(x * v.x, y * v.y); 
    }

    template <typename T> 
    Vec2<T>& Vec2<T>::operator +=(const Vec2& v) { 
        *this = *this + v; return *this; 
    }
    
    template <typename T> 
    Vec2<T>& Vec2<T>::operator -=(const Vec2& v) { 
        *this = *this - v; return *this; 
    }
    
    template <typename T> 
    Vec2<T>& Vec2<T>::operator *=(const Vec2& v) { 
        *this = *this * v; return *this; 
    }

    template <typename T>
    T Vec2<T>::dot(const Vec2& v) const {
        return x * v.x + y * v.y;
    }

    template <typename T>
    T Vec2<T>::cross(const Vec2& v) const {
        return x * v.y - y * v.x;
    }

    template <typename T>
    T Vec2<T>::length() const {
        return std::sqrt(x * x + y * y);
    }

    template <typename T>
    Vec2<T> Vec2<T>::normal() const {
        return (static_cast<T>(1.0) / length()) * *this;
    }

    template <typename T>
    bool Vec2<T>::isNumeric() const {
        return x == x && y == y;
    }

    template <typename T>
    Vec2<T> operator *(const T& t, const Vec2<T>& v) {
        return Vec2<T>(t * v.x, t * v.y);
    }

    template <typename T>
    Vec2<T> min(const Vec2<T>& a, const Vec2<T>& b) {
        return Vec2<T>(std::min(a.x, b.x), std::min(a.y, b.y));
    }
    
    template <typename T>
    Vec2<T> max(const Vec2<T>& a, const Vec2<T>& b) {
        return Vec2<T>(std::max(a.x, b.x), std::max(a.y, b.y));
    }
};

#pragma pack(pop)

#endif /* FLOWERPOT_VEC2_HPP */

