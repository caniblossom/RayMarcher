/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#include <array>
#include <iostream>
#include <vector>

#include "flowerpot/system/systemlog.hpp"
#include "interface/mainwindow.hpp"

using namespace std;
using namespace flowerpot;
using namespace raymarcher;

int main(int argc, char *argv[]) {
    vector<Window*> windowList;

    try {
        Window* window = new MainWindow();

        windowList.push_back(window);
        WindowManager manager(&windowList);

        while (!manager.shouldQuit()) {
            manager.pumpEvents();
        }
    }
    catch (exception& e) {
        system::log() << e.what() << endl;
    }

    for (Window* window : windowList) {
        delete window;
    } return 0;
}

