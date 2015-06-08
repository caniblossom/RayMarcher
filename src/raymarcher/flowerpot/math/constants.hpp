/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2014. All rights reserved unless otherwise stated.
 */

#ifndef FLOWERPOT_CONSTANTS_HPP
#define FLOWERPOT_CONSTANTS_HPP

namespace flowerpot {
    namespace math {
        constexpr double pi();
        constexpr double e();

        inline constexpr double pi() { 
            return 3.1415926535897932; 
        }
        
        inline constexpr double e() { 
            return 2.7182818284590452; 
        }
    };
};

#endif /* FLOWERPOT_CONSTANTS_HPP */

