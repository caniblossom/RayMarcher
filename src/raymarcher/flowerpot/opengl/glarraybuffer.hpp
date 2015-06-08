/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLARRAYBUFFER_HPP
#define FLOWERPOT_GLARRAYBUFFER_HPP

#include "glbuffer.hpp"

namespace flowerpot {
    class GLArrayBuffer : public GLBuffer {
        public:
            virtual ~GLArrayBuffer() {}
            GLenum getType() const;
    };

    inline GLenum GLArrayBuffer::getType() const {
        return GL_ARRAY_BUFFER;
    }
};

#endif /* FLOWERPOT_GLARRAYBUFFER_HPP */

