/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <algorithm>
#include "windowmanager.hpp"

using namespace std;

namespace flowerpot {
    WindowManager::WindowManager(vector<Window*>* windowList) : _shouldQuit(false), _windowList(windowList) {}

    bool WindowManager::shouldQuit() const {
        return _shouldQuit;
    }

    void WindowManager::pumpEvents(const int maxEvents) {
        if (_shouldQuit == true) return;

        int eventCount = 0;
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN: {
                    vector<Window*>::iterator it = findWindow(event.key.windowID);
                    if (it != _windowList->end()) {
                        (*it)->onKeyDown(event.key.repeat, event.key.keysym);
                    } break;
                }
                case SDL_KEYUP: {
                    vector<Window*>::iterator it = findWindow(event.key.windowID);
                    if (it != _windowList->end()) {
                        (*it)->onKeyUp(event.key.repeat, event.key.keysym);
                    } break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    vector<Window*>::iterator it = findWindow(event.key.windowID);
                    if (it != _windowList->end()) {
                        (*it)->onMouseButtonDown(event.button.state, event.button.x, event.button.y);
                    } break;
                }
                case SDL_MOUSEBUTTONUP: {
                    vector<Window*>::iterator it = findWindow(event.key.windowID);
                    if (it != _windowList->end()) {
                        (*it)->onMouseButtonUp(event.button.state, event.button.x, event.button.y);
                    } break;
                }
                case SDL_MOUSEMOTION: {
                    vector<Window*>::iterator it = findWindow(event.key.windowID);
                    if (it != _windowList->end()) {
                        (*it)->onMouseMotion(event.motion.state, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                    } break;
                }
                case SDL_MOUSEWHEEL: {
                    vector<Window*>::iterator it = findWindow(event.key.windowID);
                    if (it != _windowList->end()) {
                        (*it)->onMouseWheelMotion(event.wheel.x, event.wheel.y);
                    } break;
                }
                case SDL_WINDOWEVENT: {
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_SHOWN: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onShow();
                            } break;
                        }
                        case SDL_WINDOWEVENT_HIDDEN: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onHide();
                            } break;
                        }
                        case SDL_WINDOWEVENT_MOVED: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onMove(event.window.data1, event.window.data2);
                            } break;
                        }
                        case SDL_WINDOWEVENT_RESIZED: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onResize(event.window.data1, event.window.data2);
                            } break;
                        }
                        case SDL_WINDOWEVENT_MINIMIZED: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onMinimize();
                            } break;
                        }
                        case SDL_WINDOWEVENT_MAXIMIZED: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onMinimize();
                            } break;
                        }
                        case SDL_WINDOWEVENT_RESTORED: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onRestore();
                            } break;
                        }
                        case SDL_WINDOWEVENT_ENTER: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onMouseEnter();
                            } break;
                        }
                        case SDL_WINDOWEVENT_LEAVE: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onMouseLeave();
                            } break;
                        }
                        case SDL_WINDOWEVENT_FOCUS_GAINED: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onFocusGained();
                            } break;
                        }
                        case SDL_WINDOWEVENT_FOCUS_LOST: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);
                            if (it != _windowList->end()) {
                                (*it)->onFocusLost();
                            } break;
                        }
                        case SDL_WINDOWEVENT_CLOSE: {
                            vector<Window*>::iterator it = findWindow(event.key.windowID);

                            // Ask the window if it wants to be closed.
                            if (it != _windowList->end()) {
                                if ((*it)->onClose()) {
                                    delete (*it);
                                    _windowList->erase(it);
                                }
                            }

                            break;
                        }
                    }

                    break;
                }
                case SDL_QUIT: {
                    for (Window* window : *_windowList) {
                        if (window->onQuit()) _shouldQuit = true;
                    };

                    // Destroy all windows if even one of them returned true for the quit event call.
                    if (_shouldQuit) {
                        for (Window* window : *_windowList) delete window;
                        _windowList->clear();
                    }

                    break;
                }
            }

            if (eventCount++ >= maxEvents) break;
        }

        for (Window* window : *_windowList) window->onUpdate();
        if  (_windowList->size() == 0) _shouldQuit = true;
    }

    const vector<Window*>* WindowManager::getWindowList() const { 
        return _windowList; 
    }
    
    vector<Window*>* WindowManager::getWindowList() { 
        return _windowList; 
    }

    void WindowManager::setWindowList(vector<Window*>* list) {
        _windowList = list;
    }

    vector<Window*>::iterator WindowManager::findWindow(uint32_t id) const {
        return find_if(_windowList->begin(), _windowList->end(), [=](Window* window){
            return window->getID() == id;
        });
    }
}

