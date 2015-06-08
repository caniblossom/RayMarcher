/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_DISPLAYMODE_HPP
#define FLOWERPOT_DISPLAYMODE_HPP

#include <cstdint>
#include <SDL2/SDL.h>

namespace flowerpot {
    class DisplayMode {
        public:
            DisplayMode(
                const int width            = 0,
                const int height           = 0,
                const int refreshRate      = 0,
                const std::uint32_t format = SDL_PIXELFORMAT_UNKNOWN
            );

            int getWidth() const;
            int getHeight() const;
            int getRefreshRate() const;

            std::uint32_t getFormat() const;

        private:
            int _width;
            int _height;
            int _refreshRate;

            std::uint32_t _format;
    };

    inline DisplayMode::DisplayMode(
        const int width,
        const int height,
        const int refreshRate,
        const std::uint32_t format
    ) :
        _width(width),
        _height(height),
        _refreshRate(refreshRate),
        _format(format)
    {}

    inline int DisplayMode::getWidth() const { 
        return _width; 
    }
    
    inline int DisplayMode::getHeight() const { 
        return _height; 
    }
    
    inline int DisplayMode::getRefreshRate() const { 
        return _refreshRate; 
    }

    inline std::uint32_t DisplayMode::getFormat() const { 
        return _format; 
    }
};

#endif /* FLOWERPOT_DISPLAYMODE_HPP */

