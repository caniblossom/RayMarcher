/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <iostream>

#include "../system/systemlog.hpp"
#include "glerror.hpp"
#include "glframebuffer.hpp"

using namespace std;

namespace flowerpot {
    GLFramebuffer::GLFramebuffer() {
        GLuint id = 0;

        try {
            GLError::clearAll();
            glGenFramebuffers(1, &id);
            setID(id);

            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            glDeleteFramebuffers(1, &id);
            throw GLException(string("Couldn't create framebuffer: ") + string(e.what()));
        }
    }

    GLFramebuffer::~GLFramebuffer() {
        try {
            GLError::clearAll();
            GLuint id = getID();
            glDeleteFramebuffers(1, &id);

            GLError::throwExceptionOnError();
        } catch (exception& e) {
            system::log() << "Couldn't delete framebuffer: " << e.what() << endl;
        }
    }
};

