/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include "glerror.hpp"
#include "gltexture2d.hpp"

using namespace std;

namespace flowerpot {
    void GLTexture2D::readSurface(const Surface& surface) const {
        try {
            GLError::clearAll();
            glBindTexture(GL_TEXTURE_2D, getID());
            GLError::throwExceptionOnError();

            glTexImage2D
            (
                GL_TEXTURE_2D,
                0,
                GL_RGBA8,
                surface.getWidth(),
                surface.getHeight(),
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                surface.data().data()
            );

            glBindTexture(GL_TEXTURE_2D, 0);
            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            throw GLException(string("Couldn't create a texture from surface: ") + string(e.what()));
        }
    }
};

