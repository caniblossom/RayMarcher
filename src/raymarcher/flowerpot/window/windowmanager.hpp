/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_WINDOWMANAGER_HPP
#define FLOWERPOT_WINDOWMANAGER_HPP

#include <vector>

#include "../system/sdl.hpp"
#include "window.hpp"

namespace flowerpot {
    class WindowManager {
        public:
            WindowManager(std::vector<Window*>* windowList);

            bool shouldQuit() const;
            void pumpEvents(const int maxEvents = 256);

            const std::vector<Window*>* getWindowList() const;
                  std::vector<Window*>* getWindowList();

            void setWindowList(std::vector<Window*>* list);

            std::vector<Window*>::iterator findWindow(std::uint32_t id) const;

        private:
            SDL _sdl;

            bool _shouldQuit;
            std::vector<Window*>* _windowList;
    };
};

#endif /* FLOWERPOT_WINDOWMANAGER_HPP */

