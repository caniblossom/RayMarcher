/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_SDL_HPP
#define FLOWERPOT_SDL_HPP

#include <SDL2/SDL.h>

#include "keyboardstate.hpp"
#include "mousestate.hpp"

namespace flowerpot {
    class SDL{
        public:
            SDL(const std::uint32_t sdlFlags = 0);
            ~SDL();

            SDL(const SDL& sdl) = delete;
            SDL& operator =(const SDL& sdl) = delete;

            KeyboardState readKeyboard() const;
            MouseState    readMouse() const;

            SDL_GLContext createGLContext(SDL_Window* window = nullptr) const;
            void          deleteGLContext(SDL_GLContext glContext) const;

        private:
            static int _instanceCount;
    };
};

#endif /* FLOWERPOT_SDL_HPP */

