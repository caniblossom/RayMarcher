/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_MOUSESTATE_HPP
#define FLOWERPOT_MOUSESTATE_HPP

#include <cstdint>

namespace flowerpot {
    class MouseState {
        public:
            MouseState(
                const int xPos    = 0, const int yPos    = 0,
                const int xMotion = 0, const int yMotion = 0,
                const std::uint8_t buttonMask = 0
            );

            int getPosX() const;
            int getPosY() const;
            int getMotionX() const;
            int getMotionY() const;

            bool isButtonDown(const std::uint8_t button) const ;

        private:
            int _xPos,    _yPos;
            int _xMotion, _yMotion;
            std::uint8_t _buttonMask;
    };


    inline MouseState::MouseState(
        const int xPos, const int yPos, const int xMotion, const int yMotion, const std::uint8_t buttonMask
    ) : _xPos(xPos), _yPos(yPos), _xMotion(xMotion), _yMotion(yMotion), _buttonMask(buttonMask) {}

    inline int MouseState::getPosX() const { 
        return _xPos; 
    }
    
    inline int MouseState::getPosY() const { 
        return _yPos; 
    }
    
    inline int MouseState::getMotionX() const { 
        return _xMotion; 
    }
    
    inline int MouseState::getMotionY() const { 
        return _yMotion; 
    }

    inline bool MouseState::isButtonDown(const std::uint8_t button) const {
        return _buttonMask & button;
    }
};

#endif /* FLOWERPOT_MOUSESTATE_HPP */

