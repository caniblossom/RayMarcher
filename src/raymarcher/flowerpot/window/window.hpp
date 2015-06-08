/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_WINDOW_HPP
#define FLOWERPOT_WINDOW_HPP

#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

#include <GL/glew.h>

#include "../surface/surface.hpp"
#include "../system/displaymode.hpp"
#include "../system/glattributes.hpp"
#include "../system/sdl.hpp"

#include "windoweventlistener.hpp"

namespace flowerpot {
    class Window : public WindowEventListener {
        public:
            Window(
                const bool          resizable    = false,
                const bool          borderless   = false,
                const int           width        = 1280,
                const int           height       = 720,
                const int           xPos         = SDL_WINDOWPOS_CENTERED,
                const int           yPos         = SDL_WINDOWPOS_CENTERED,
                const GLAttributes& glAttributes = GLAttributes()
            );

            virtual ~Window();

            Window(const Window& window) = delete;
            Window& operator =(const Window& window) = delete;

            uint32_t getID() const;

            const SDL_Window* getWindowHandle() const;
                  SDL_Window* getWindowHandle();

            int getWidth() const;
            int getHeight() const;

            int getXPosition() const;
            int getYPosition() const;

            void setSize(const int width, const int height) const;
            void setPosition(const int x, const int y) const;

            void setTitle(const std::string& title) const;
            void setIcon(const Surface& icon) const;

            bool isVisible() const;
            bool isMinimized() const;
            bool isMaximized() const;

            void show() const;
            void hide() const;

            void minimize() const;
            void maximize() const;
            void restore() const;

            void sendCloseEvent();

            const SDL& getSDL() const;
            const GLAttributes& getGLAttributes() const;

            SDL_GLContext getGLContext() const;
            void          setGLContext(const SDL_GLContext context);

            void setGLContextCurrent() const;

            DisplayMode getFullscreenDisplayMode() const;
            void        setFullscreenDisplayMode(const DisplayMode& displayMode) const;

            bool toggleFullscreen (const bool state) const;
            bool toggleVSync      (const bool state) const;

            void resizeGLViewport() const;
            void flipDisplayBuffer() const;

        private:
            SDL _sdl;

            SDL_Window* _windowHandle;
            GLAttributes _glAttributes;
            SDL_GLContext _glContext;
    };
};

#endif /* FLOWERPOT_WINDOW_HPP */

