/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <iostream>

#include "../system/systemlog.hpp"
#include "glerror.hpp"
#include "gltexture.hpp"

using namespace std;

namespace flowerpot {
    GLTexture::GLTexture() {
        GLuint id = 0;

        try {
            GLError::clearAll();
            glGenTextures(1, &id);
            setID(id);

            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            glDeleteTextures(1, &id);
            throw GLException(string("Couldn't create texture: ") + string(e.what()));
        }
    }

    GLTexture::~GLTexture() {
        try {
            GLError::clearAll();
            GLuint id = getID();
            glDeleteTextures(1, &id);

            GLError::throwExceptionOnError();
        } catch (exception& e) {
            system::log() << "Couldn't delete texture: " << e.what() << endl;
        }
    }
};

