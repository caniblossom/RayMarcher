/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLPIXELPACKBUFFER_HPP
#define FLOWERPOT_GLPIXELPACKBUFFER_HPP

#include "glbuffer.hpp"

namespace flowerpot {
    class GLPixelPackBuffer : public GLBuffer {
        public:
            virtual ~GLPixelPackBuffer() {}
            GLenum getType() const;
    };

    inline GLenum GLPixelPackBuffer::getType() const {
        return GL_PIXEL_PACK_BUFFER;
    }
};

#endif /* FLOWERPOT_GLPIXELPACKBUFFER_HPP */

