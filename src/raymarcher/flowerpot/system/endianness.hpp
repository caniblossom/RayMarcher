/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_ENDIANNESS_HPP
#define FLOWERPOT_ENDIANNESS_HPP

#include <cstdint>
#include "SDL2/SDL_endian.h"

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
namespace flowerpot {
    namespace system {
        void flipIfLEnd(std::uint32_t& x);
        void flipIfBEnd(std::uint32_t& x);

        inline void flipIfLEnd(std::uint32_t& x) { 
            SDL_Swap32(x); 
        }
        
        inline void flipIfBEnd(std::uint32_t& x) {}
    };

#else /* SDL_BYTEORDER == SDL_LIL_ENDIAN */
    namespace system {
        void flipIfLEnd(std::uint32_t& x);
        void flipIfBEnd(std::uint32_t& x);

        inline void flipIfLEnd(std::uint32_t& x) {}
        
        inline void flipIfBEnd(std::uint32_t& x) { 
            SDL_Swap32(x); 
        }
    };
#endif /* SDL_BYTEORDER == SDL_LIL_ENDIAN */
};

#endif /* FLOWERPOT_ENDIANNESS_HPP */

