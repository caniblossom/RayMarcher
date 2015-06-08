/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_RGBA32_HPP
#define FLOWERPOT_RGBA32_HPP

#include <cstdint>

#pragma pack(push, 4)

namespace flowerpot {
    struct RGBA32 {
        public:
            std::uint8_t r, g, b, a;

            RGBA32() {}
            RGBA32(
                const std::uint8_t r,
                const std::uint8_t g,
                const std::uint8_t b,
                const std::uint8_t a
            );

            bool operator ==(const RGBA32& c) const;
            bool operator !=(const RGBA32& c) const;
    };

    inline RGBA32::RGBA32(
        const std::uint8_t r,
        const std::uint8_t g,
        const std::uint8_t b,
        const std::uint8_t a
    ) : r(r), g(g), b(b), a(a) {}

    inline bool RGBA32::operator ==(const RGBA32& c) const { 
        return r == c.r && g == c.g && b == c.b && a == c.a; 
    }
    
    inline bool RGBA32::operator !=(const RGBA32& c) const { 
        return r != c.r || g != c.g || b != c.b || a != c.a; 
    }
};

#pragma pack(pop)

#endif /* FLOWERPOT_RGBA32_HPP */

