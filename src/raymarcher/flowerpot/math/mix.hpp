/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_MIX_HPP
#define FLOWERPOT_MIX_HPP

namespace flowerpot {
    namespace math {
        template <typename T, typename U>
        T mix(const T a, const T b, const U w);

        template <typename T, typename U>
        T mix(const T a, const T b, const U w) {
            return (static_cast<U>(1.0) - w) * a + w * b;
        }
    };
};

#endif /* FLOWERPOT_MIX_HPP */

