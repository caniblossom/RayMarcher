/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_KEYBOARDSTATE_HPP
#define FLOWERPOT_KEYBOARDSTATE_HPP

#include <cstdint>
#include <SDL2/SDL.h>

namespace flowerpot {
    class KeyboardState {
        public:
            KeyboardState(
                const uint32_t keyCount = 0,
                const std::uint8_t* keyList = nullptr,
                const SDL_Keymod modifiers = KMOD_NONE
            );

            bool keyIsDown(const SDL_Scancode code) const;
            bool hasModifier(const SDL_Keymod mod) const;

        private:
            const uint32_t _keyCount = 0;
            const std::uint8_t* _keyList;

            SDL_Keymod _modifiers;
    };

    inline KeyboardState::KeyboardState(
        const uint32_t keyCount, const std::uint8_t* keyList, const SDL_Keymod modifiers
    ) : _keyCount(keyCount), _keyList(keyList), _modifiers(modifiers) {}

    inline bool KeyboardState::keyIsDown(const SDL_Scancode code) const {
        if (static_cast<unsigned>(code) < 0 || static_cast<unsigned>(code) >= _keyCount) return false;
        else return _keyList[code] == 1;
    }

    inline bool KeyboardState::hasModifier(const SDL_Keymod mod) const {
        return (_modifiers & mod) == mod;
    }
};

#endif /* FLOWERPOT_KEYBOARDSTATE_HPP */

