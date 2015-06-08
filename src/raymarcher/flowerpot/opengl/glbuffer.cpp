/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <iostream>

#include "../system/systemlog.hpp"
#include "glerror.hpp"
#include "glbuffer.hpp"

using namespace std;

namespace flowerpot {
    GLBuffer::GLBuffer() {
        GLuint id = 0;

        try {
            GLError::clearAll();
            glGenBuffers(1, &id);
            setID(id);

            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            glDeleteBuffers(1, &id);
            throw GLException(string("Couldn't create buffer: ") + string(e.what()));
        }
    }

    GLBuffer::~GLBuffer() {
        try {
            GLError::clearAll();
            GLuint id = getID();
            glDeleteBuffers(1, &id);

            GLError::throwExceptionOnError();
        } catch (exception& e) {
            system::log() << "Couldn't delete buffer: " << e.what() << endl;
        }
    }
};

