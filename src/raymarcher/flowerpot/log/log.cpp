/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <ctime>
#include "log.hpp"

using namespace std;

namespace flowerpot {
    const char* timeString() {
        time_t raw;
        time(&raw);
        return ctime(&raw);
    }

    Log::Log(const std::string& filename) {
        _output.open(filename, fstream::out | fstream::app);
        _output << "Log opened: " << timeString();
    }
    
    Log::~Log() {
        _output << endl;
    }

    fstream& Log::getOutput() {
        return _output;
    }
}

