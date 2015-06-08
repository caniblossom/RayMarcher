/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_WINDOWEVENTLISTENER_HPP
#define FLOWERPOT_WINDOWEVENTLISTENER_HPP

#include <cstdint>

namespace flowerpot {
    class WindowEventListener {
        public:
            virtual void onUpdate() {}

            virtual void onKeyUp(const std::uint8_t repeat, const SDL_Keysym& keysym) {}
            virtual void onKeyDown(const std::uint8_t repeat, const SDL_Keysym& keysym) {}

            virtual void onMouseMotion(const std::uint8_t buttonState, const int xPos, const int yPos, const int xMotion, const int yMotion) {}
            virtual void onMouseButtonUp(const std::uint8_t buttonState, const int xPos, const int yPos) {}
            virtual void onMouseButtonDown(const std::uint8_t buttonState, const int xPos, const int yPos) {}
            virtual void onMouseWheelMotion(const int xMotion, const int yMotion) {}

            virtual void onMouseEnter() {}
            virtual void onMouseLeave() {}

            virtual void onFocusGained() {}
            virtual void onFocusLost() {}

            virtual void onShow() {}
            virtual void onHide() {}

            virtual void onMove(const int xPos, const int yPos) {}
            virtual void onResize(const int width, const int height) {}

            virtual void onMinimize() {}
            virtual void onMaximize() {}
            virtual void onRestore() {}

            virtual bool onClose();
            virtual bool onQuit();
    };

    inline bool WindowEventListener::onClose() { 
        return true; 
    }
    
    inline bool WindowEventListener::onQuit() { 
        return true; 
    }
};

#endif /* FLOWERPOT_WINDOWEVENTLISTENERHPP */

