/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_INTEGER3_HPP
#define FLOWERPOT_INTEGER3_HPP

namespace flowerpot {
    template <typename T>
    class Integer3 {
        public:
            T x, y, z;

            Integer3() {}
            Integer3(const T x, const T y, const T z);

            bool operator ==(const Integer3& v) const;
            bool operator !=(const Integer3& v) const;

            Integer3 operator -() const;

            Integer3 operator +(const Integer3& v) const;
            Integer3 operator -(const Integer3& v) const;
            Integer3 operator *(const Integer3& v) const;

            Integer3& operator +=(const Integer3& v);
            Integer3& operator -=(const Integer3& v);
            Integer3& operator *=(const Integer3& v);

            T dot(const Integer3& v) const;
    };
    
    template <typename T> 
    Integer3<T> operator *(const T& t, const Integer3<T>& v);

    template <typename T> Integer3<T> min(const Integer3<T>& a, const Integer3<T>& b);
    template <typename T> Integer3<T> max(const Integer3<T>& a, const Integer3<T>& b);

    template <typename T>
    Integer3<T>::Integer3(const T x, const T y, const T z) : x(x), y(y), z(z) {}

    template <typename T> bool Integer3<T>::operator ==(const Integer3& v) const { 
        return x == v.x && y == v.y && z == v.z; 
    }
    
    template <typename T> bool Integer3<T>::operator !=(const Integer3& v) const { 
        return x != v.x || y != v.y || z != v.z; 
    }

    template <typename T>
    Integer3<T> Integer3<T>::operator -() const {
        return Integer3(-x, -y, -z);
    }

    template <typename T> Integer3<T> Integer3<T>::operator +(const Integer3& v) const { 
        return Integer3(x + v.x, y + v.y, z + v.z); 
    }
    
    template <typename T> Integer3<T> Integer3<T>::operator -(const Integer3& v) const { 
        return Integer3(x - v.x, y - v.y, z - v.z); 
    }
    
    template <typename T> Integer3<T> Integer3<T>::operator *(const Integer3& v) const { 
        return Integer3(x * v.x, y * v.y, z * v.z); 
    }

    template <typename T> Integer3<T>& Integer3<T>::operator +=(const Integer3& v) { 
        *this = *this + v; return *this; 
    }
    
    template <typename T> Integer3<T>& Integer3<T>::operator -=(const Integer3& v) { 
        *this = *this - v; return *this; 
    }
    
    template <typename T> Integer3<T>& Integer3<T>::operator *=(const Integer3& v) { 
        *this = *this * v; return *this; 
    }

    template <typename T>
    T Integer3<T>::dot(const Integer3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    template <typename T>
    Integer3<T> operator *(const T& t, const Integer3<T>& v) {
        return Integer3<T>(t * v.x, t * v.y, t * v.z);
    }
    
    template <typename T>
    Integer3<T> min(const Integer3<T>& a, const Integer3<T>& b) {
        return Integer3<T>(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
    }
    
    template <typename T>
    Integer3<T> max(const Integer3<T>& a, const Integer3<T>& b) {
        return Integer3<T>(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
    }
};

#endif /* FLOWERPOT_INTEGER3_HPP */

