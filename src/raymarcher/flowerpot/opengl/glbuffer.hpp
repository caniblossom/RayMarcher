/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLBUFFER_HPP
#define FLOWERPOT_GLBUFFER_HPP

#include <vector>
#include "glresource.hpp"

namespace flowerpot {
    class GLBuffer : public GLResource {
        public:
            GLBuffer();
            virtual ~GLBuffer();

            virtual GLenum getType() const = 0;

            void bind() const;
            void unbind() const;
    };

    inline void GLBuffer::bind() const { 
        glBindBuffer(getType(), getID()); 
    }
    
    inline void GLBuffer::unbind() const { 
        glBindBuffer(getType(), 0); 
    }
};

#endif /* FLOWERPOT_GLBUFFER_HPP */

