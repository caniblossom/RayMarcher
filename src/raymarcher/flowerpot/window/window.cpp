/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <cstdint>

#include "../system/systemlog.hpp"
#include "../system/endianness.hpp"
#include "window.hpp"

using namespace std;

namespace flowerpot {
    Window::Window(
        const bool resizable, const bool borderless, const int width, const int height, const int xPos, const int yPos, const GLAttributes& glAttributes
    ) : _sdl(SDL_INIT_VIDEO), _windowHandle(nullptr), _glAttributes(glAttributes), _glContext(nullptr) {
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE,              _glAttributes.getRedBits());
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,            _glAttributes.getGreenBits());
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,             _glAttributes.getBlueBits());
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,            _glAttributes.getAlphaBits());
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,            _glAttributes.getDepthBits());
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,          _glAttributes.getStencilBits());
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, _glAttributes.getContextMajor());
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, _glAttributes.getContextMinor());
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

        system::log() << "Requested window surface format: ";
        system::log() << "R" << glAttributes.getRedBits();
        system::log() << "G" << glAttributes.getGreenBits();
        system::log() << "B" << glAttributes.getBlueBits();
        system::log() << "A" << glAttributes.getAlphaBits();
        system::log() << "Z" << glAttributes.getDepthBits();
        system::log() << "S" << glAttributes.getStencilBits();
        system::log() << ", OpenGL context version ";
        system::log() << glAttributes.getContextMajor() << "." << glAttributes.getContextMinor();
        system::log() << endl;

        const uint32_t flags = (resizable ? SDL_WINDOW_RESIZABLE : 0) | (borderless ? SDL_WINDOW_BORDERLESS : 0);

        _windowHandle = SDL_CreateWindow("Window", xPos, yPos, width, height, flags | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        if (_windowHandle == nullptr) throw runtime_error("Couldn't create a new window.");

        _glContext = _sdl.createGLContext(_windowHandle);
        resizeGLViewport();
    }

    Window::~Window() {
        system::log() << "Deleting OpenGL context." << endl;
        if (_glContext) _sdl.deleteGLContext(_glContext);
        system::log() << "Destroying window." << endl;
        if (_windowHandle) SDL_DestroyWindow(_windowHandle);
    }

    uint32_t Window::getID() const {
        return SDL_GetWindowID(_windowHandle);
    }

    const SDL_Window* Window::getWindowHandle() const { 
        return _windowHandle; 
    }
    
    SDL_Window* Window::getWindowHandle() { 
        return _windowHandle; 
    }

    int Window::getWidth() const {
        int w, h; 
        SDL_GetWindowSize(_windowHandle, &w, &h);
        return w;
    }

    int Window::getHeight() const {
        int w, h; 
        SDL_GetWindowSize(_windowHandle, &w, &h);
        return h;
    }

    int Window::getXPosition() const {
        int x, y; 
        SDL_GetWindowPosition(_windowHandle, &x, &y);
        return x;
    }

    int Window::getYPosition() const {
        int x, y; 
        SDL_GetWindowPosition(_windowHandle, &x, &y);
        return y;
    }

    void Window::setSize(const int width, const int height) const {
        SDL_SetWindowSize(_windowHandle, width, height);
    }

    void Window::setPosition(const int x, const int y) const {
        SDL_SetWindowPosition(_windowHandle, x, y);
    }

    void Window::setTitle(const std::string& title) const {
        SDL_SetWindowTitle(_windowHandle, title.c_str());

    }

    void Window::setIcon(const Surface& icon) const {
        uint32_t rMask = 0x000000ff;
        uint32_t gMask = 0x0000ff00;
        uint32_t bMask = 0x00ff0000;
        uint32_t aMask = 0xff000000;

        system::flipIfBEnd(rMask);
        system::flipIfBEnd(gMask);
        system::flipIfBEnd(bMask);
        system::flipIfBEnd(aMask);

        SDL_Surface* iconSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, 32, 32, 32, rMask, gMask, bMask, aMask);
        if (iconSurface == nullptr) return;

        SDL_LockSurface (iconSurface);
        uint8_t* pixels = reinterpret_cast<uint8_t*>(iconSurface->pixels);

        for (int y = 0; y < 32; y++) {
            for (int x = 0; x < 32; x++) {
                if (!icon.isInside(x, y)) continue;
                
                pixels[4 * x + 0 + y * iconSurface->pitch] = icon.at(x, y).r;
                pixels[4 * x + 1 + y * iconSurface->pitch] = icon.at(x, y).g;
                pixels[4 * x + 2 + y * iconSurface->pitch] = icon.at(x, y).b;
                pixels[4 * x + 3 + y * iconSurface->pitch] = icon.at(x, y).a;
            }
        }

        SDL_UnlockSurface(iconSurface);
        SDL_SetWindowIcon(_windowHandle, iconSurface);
    }

    bool Window::isVisible() const {
        return SDL_GetWindowFlags(_windowHandle) | SDL_WINDOW_SHOWN;
    }

    bool Window::isMinimized() const {
        return SDL_GetWindowFlags(_windowHandle) | SDL_WINDOW_MINIMIZED;
    }

    bool Window::isMaximized() const {
        return SDL_GetWindowFlags(_windowHandle) | SDL_WINDOW_MAXIMIZED;
    }

    void Window::show() const {
        SDL_ShowWindow(_windowHandle);
    }

    void Window::hide() const {
        SDL_HideWindow(_windowHandle);
    }

    void Window::minimize() const {
        SDL_MinimizeWindow(_windowHandle);
    }

    void Window::maximize() const {
        SDL_MaximizeWindow(_windowHandle);
    }

    void Window::restore() const {
        SDL_RestoreWindow (_windowHandle);
    }

    void Window::sendCloseEvent() {
        SDL_Event event;

        event.type            = SDL_WINDOWEVENT;
        event.window.type     = SDL_WINDOWEVENT;
        event.window.event    = SDL_WINDOWEVENT_CLOSE;
        event.window.windowID = getID();

        SDL_PushEvent(&event);
    }

    const SDL& Window::getSDL() const {
        return _sdl;
    }

    const GLAttributes& Window::getGLAttributes() const {
        return _glAttributes;
    }

    SDL_GLContext Window::getGLContext() const {
        return _glContext;
    }

    void Window::setGLContext(const SDL_GLContext context) {
        _glContext = context;
    }

    void Window::setGLContextCurrent() const {
        if (SDL_GL_MakeCurrent(_windowHandle, _glContext) != 0) {
            throw runtime_error("Couldn't make an OpenGL context current.");
        }
    }

    DisplayMode Window::getFullscreenDisplayMode() const {
        SDL_DisplayMode mode;
        SDL_GetWindowDisplayMode(_windowHandle, &mode);
        return DisplayMode(mode.w, mode.h, mode.refresh_rate, mode.format);
    }

    void Window::setFullscreenDisplayMode(const DisplayMode& displayMode) const {
        SDL_DisplayMode mode;
        
        mode.w = displayMode.getWidth();
        mode.h = displayMode.getHeight();
        mode.refresh_rate = displayMode.getRefreshRate();
        mode.format = displayMode.getFormat();
        mode.driverdata = nullptr;

        SDL_SetWindowDisplayMode(_windowHandle, &mode);
    }

    bool Window::toggleFullscreen(const bool state) const {
        return SDL_SetWindowFullscreen(_windowHandle, (state ? SDL_TRUE : SDL_FALSE)) == 0;
    }

    bool Window::toggleVSync(const bool state) const {
        return SDL_GL_SetSwapInterval(state ? 1 : 0) == 0;
    }

    void Window::resizeGLViewport() const {
        glViewport(0, 0, getWidth(), getHeight());
    }

    void Window::flipDisplayBuffer() const {
        SDL_GL_SwapWindow(_windowHandle);
    }
};

