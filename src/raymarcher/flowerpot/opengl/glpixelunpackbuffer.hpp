/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLPIXELUNPACKBUFFER_HPP
#define FLOWERPOT_GLPIXELUNPACKBUFFER_HPP

#include "glbuffer.hpp"

namespace flowerpot {
    class GLPixelUnpackBuffer : public GLBuffer {
        public:
            virtual ~GLPixelUnpackBuffer() {}
            GLenum getType() const;
    };

    inline GLenum GLPixelUnpackBuffer::getType() const {
        return GL_PIXEL_UNPACK_BUFFER;
    }
};

#endif /* FLOWERPOT_GLPIXELUNPACKBUFFER_HPP */

