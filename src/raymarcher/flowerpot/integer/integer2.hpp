/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2014. All rights reserved unless otherwise stated.
 */

#ifndef FLOWERPOT_INTEGER2_HPP
#define FLOWERPOT_INTEGER2_HPP

#include <algorithm>

namespace flowerpot {
    template <typename T>
    class Integer2 {
        public:
            T x, y;

            Integer2() {}
            Integer2(const T x, const T y);

            bool operator ==(const Integer2& v) const;
            bool operator !=(const Integer2& v) const;

            Integer2 operator -() const;

            Integer2 operator +(const Integer2& v) const;
            Integer2 operator -(const Integer2& v) const;
            Integer2 operator *(const Integer2& v) const;

            Integer2& operator +=(const Integer2& v);
            Integer2& operator -=(const Integer2& v);
            Integer2& operator *=(const Integer2& v);

            T dot(const Integer2& v) const;
    };
    
    template <typename T> 
    Integer2<T> operator *(const T& t, const Integer2<T>& v);

    template <typename T> Integer2<T> min(const Integer2<T>& a, const Integer2<T>& b);
    template <typename T> Integer2<T> max(const Integer2<T>& a, const Integer2<T>& b);

    template <typename T>
    Integer2<T>::Integer2(const T x, const T y) : x(x), y(y) {}

    template <typename T> 
    bool Integer2<T>::operator ==(const Integer2& v) const { 
        return x == v.x && y == v.y; 
    }
    
    template <typename T> 
    bool Integer2<T>::operator !=(const Integer2& v) const { 
        return x != v.x || y != v.y; 
    }

    template <typename T>
    Integer2<T> Integer2<T>::operator -() const {
        return Integer2(-x, -y);
    }

    template <typename T> Integer2<T> 
    Integer2<T>::operator +(const Integer2& v) const { 
        return Integer2(x + v.x, y + v.y); 
    }
    
    template <typename T> Integer2<T> 
    Integer2<T>::operator -(const Integer2& v) const { 
        return Integer2(x - v.x, y - v.y); 
    }
    
    template <typename T> Integer2<T> 
    Integer2<T>::operator *(const Integer2& v) const { 
        return Integer2(x * v.x, y * v.y); 
    }
    
    template <typename T> Integer2<T>& 
    Integer2<T>::operator +=(const Integer2& v) { 
        *this = *this + v; return *this; 
    }
    
    template <typename T> Integer2<T>& 
    Integer2<T>::operator -=(const Integer2& v) { 
        *this = *this - v; return *this; 
    }
    
    template <typename T> Integer2<T>& 
    Integer2<T>::operator *=(const Integer2& v) { 
        *this = *this * v; return *this; 
    }
    
    template <typename T>
    T Integer2<T>::dot(const Integer2& v) const {
        return x * v.x + y * v.y;
    }

    template <typename T>
    Integer2<T> operator *(const T& t, const Integer2<T>& v) {
        return Integer2<T>(t * v.x, t * v.y);
    }
    
    template <typename T>
    Integer2<T> min(const Integer2<T>& a, const Integer2<T>& b) {
        return Integer2<T>(std::min(a.x, b.x), std::min(a.y, b.y));
    }
    
    template <typename T>
    Integer2<T> max(const Integer2<T>& a, const Integer2<T>& b) {
        return Integer2<T>(std::max(a.x, b.x), std::max(a.y, b.y));
    }
};

#endif /* FLOWERPOT_INTEGER2_HPP */

