/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLELEMENTARRAYBUFFER_HPP
#define FLOWERPOT_GLELEMENTARRAYBUFFER_HPP

#include "glbuffer.hpp"

namespace flowerpot {
    class GLElementArrayBuffer : public GLBuffer {
        public:
            virtual ~GLElementArrayBuffer() {}
            GLenum getType() const;
    };

    inline GLenum GLElementArrayBuffer::getType() const {
        return GL_ELEMENT_ARRAY_BUFFER;
    }
};

#endif /* FLOWERPOT_GLELEMENTARRAYBUFFER_HPP */

