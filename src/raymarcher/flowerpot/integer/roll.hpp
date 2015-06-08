/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_ROLL_HPP
#define FLOWERPOT_ROLL_HPP

#include <cstdint>

namespace flowerpot {
    namespace integer {
        std::uint8_t  rol8 (std::uint8_t  i, std::uint8_t shift);
        std::uint8_t  ror8 (std::uint8_t  i, std::uint8_t shift);
        std::uint16_t rol16(std::uint16_t i, std::uint8_t shift);
        std::uint16_t ror16(std::uint16_t i, std::uint8_t shift);
        std::uint32_t rol32(std::uint32_t i, std::uint8_t shift);
        std::uint32_t ror32(std::uint32_t i, std::uint8_t shift);

        inline std::uint8_t rol8(std::uint8_t  i, std::uint8_t shift) { 
            return (i << shift) | (i >> (8 - shift)); 
        }
        
        inline std::uint8_t ror8(std::uint8_t  i, std::uint8_t shift) { 
            return (i >> shift) | (i << (8 - shift)); 
        }
        
        inline std::uint16_t rol16(std::uint16_t i, std::uint8_t shift) { 
            return (i << shift) | (i >> (16 - shift)); 
        }
        
        inline std::uint16_t ror16(std::uint16_t i, std::uint8_t shift) { 
            return (i >> shift) | (i << (16 - shift)); 
        }
        
        inline std::uint32_t rol32(std::uint32_t i, std::uint8_t shift) { 
            return (i << shift) | (i >> (32 - shift)); 
        }
        
        inline std::uint32_t ror32(std::uint32_t i, std::uint8_t shift) { 
            return (i >> shift) | (i << (32 - shift)); 
        }
    };
};

#endif /* FLOWERPOT_ROLL_HPP */

