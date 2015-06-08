/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <iostream>

#include "../system/systemlog.hpp"
#include "glerror.hpp"
#include "glvertexarray.hpp"

using namespace std;

namespace flowerpot {
    GLVertexArray::GLVertexArray() {
        GLuint id = 0;

        try {
            GLError::clearAll();
            glGenVertexArrays(1, &id);
            setID(id);

            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            glDeleteBuffers(1, &id);
            throw GLException(string("Couldn't create vertex array ") + string(e.what()));
        }
    }

    GLVertexArray::~GLVertexArray() {
        try {
            GLError::clearAll();
            GLuint id = getID();
            glDeleteVertexArrays(1, &id);

            GLError::throwExceptionOnError();
        } catch (exception& e) {
            system::log() << "Couldn't delete vertex array: " << e.what() << endl;
        }
    }
};

