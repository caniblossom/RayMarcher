/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include "systemlog.hpp"

namespace flowerpot {
    namespace system {
        Log& log() { 
            static Log systemLog("system.log");
            return systemLog; 
        }
    }
};

