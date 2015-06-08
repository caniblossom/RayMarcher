/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLTEXTURE2D_HPP
#define FLOWERPOT_GLTEXTURE2D_HPP

#include <iostream>

#include "../surface/surface.hpp"
#include "gltexture.hpp"

namespace flowerpot {
     class GLTexture2D : public GLTexture {
        public:
            GLTexture2D() {}
            GLTexture2D(const Surface& surface);

            virtual ~GLTexture2D() {}

            void bind() const;
            void unbind() const;

            void readSurface(const Surface& surface) const;
    };

    inline GLTexture2D::GLTexture2D(const Surface& surface) {
        readSurface(surface);
    }

    inline void GLTexture2D::bind() const { 
        glBindTexture(GL_TEXTURE_2D, getID()); 
    }
    
    inline void GLTexture2D::unbind() const { 
        glBindTexture(GL_TEXTURE_2D, 0); 
    }
};

#endif /* FLOWERPOT_GLTEXTURE2D_HPP */

