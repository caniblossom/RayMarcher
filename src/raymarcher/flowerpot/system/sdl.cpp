/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <string>
#include <stdexcept>
#include <GL/glew.h>

#include "sdl.hpp"

using namespace std;

namespace flowerpot {
    void tryInit(const uint32_t sdlFlags, const uint32_t flag, const string& errorMessage) {
        if ((sdlFlags & flag) && SDL_WasInit(flag) == 0) {
            if (SDL_InitSubSystem(flag) != 0) throw runtime_error(errorMessage + string(SDL_GetError()));
        }
    }

    SDL::SDL(const uint32_t sdlFlags) {
        try {
            if (_instanceCount == 0) {
                if(SDL_Init(0) != 0) throw runtime_error(string("Couldn't initialize SDL: ") + string(SDL_GetError()));
            }

            tryInit(sdlFlags, SDL_INIT_VIDEO,    string("Couldn't initialize SDL video subsystem: "));
            tryInit(sdlFlags, SDL_INIT_AUDIO,    string("Couldn't initialize SDL audio subsystem: "));
            tryInit(sdlFlags, SDL_INIT_TIMER,    string("Couldn't initialize SDL timer subsystem: "));
            tryInit(sdlFlags, SDL_INIT_JOYSTICK, string("Couldn't initialize SDL joystick subsystem: "));
            tryInit(sdlFlags, SDL_INIT_HAPTIC,   string("Couldn't initialize SDL haptic subsystem: "));
        }
        catch (exception& e) {
            if (_instanceCount == 0) SDL_Quit();
            throw;
        }

        _instanceCount++;
    }

    SDL::~SDL() {
        _instanceCount--;
        if (_instanceCount == 0) SDL_Quit();
    }

    KeyboardState SDL::readKeyboard() const {
        int keyCount;
        const Uint8* state;
        SDL_Keymod modifiers;

        SDL_PumpEvents();
        state = SDL_GetKeyboardState(&keyCount);
        modifiers = SDL_GetModState();

        return KeyboardState(keyCount, state, modifiers);
    }

    MouseState SDL::readMouse() const {
        int posX, posY;
        int motionX, motionY;
        int buttons;

        SDL_PumpEvents();
        buttons = SDL_GetMouseState(&posX, &posY);
        SDL_GetRelativeMouseState(&motionX, &motionY);

        return MouseState(posX, posY, motionX, motionY, buttons);
    }

    SDL_GLContext SDL::createGLContext(SDL_Window* window) const {
        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        if (glContext == 0) throw runtime_error("Couldn't create a new GL context.");

        // Tell GLEW to report all valid extensions. This at least used to be
        // necessary to get proper OpenGL 3.2+ support, and won't hurt anyway.
        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK) {
            SDL_GL_DeleteContext(glContext);
            throw runtime_error("Couldn't initialize GLEW.");
        };

        return glContext;
    }

    void SDL::deleteGLContext(SDL_GLContext glContext) const {
        SDL_GL_DeleteContext(glContext);
    }

    int SDL::_instanceCount = 0;
};

