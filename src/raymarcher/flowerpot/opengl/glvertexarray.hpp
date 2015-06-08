/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */
#ifndef FLOWERPOT_GLVERTEXARRAY_HPP
#define FLOWERPOT_GLVERTEXARRAY_HPP

#include "glresource.hpp"

namespace flowerpot {
    class GLVertexArray : public GLResource {
        public:
            GLVertexArray();
            virtual ~GLVertexArray();

            void bind() const;
            void unbind() const;
    };

    inline void GLVertexArray::bind() const { 
        glBindVertexArray(getID()); 
    }
    
    inline void GLVertexArray::unbind() const { 
        glBindVertexArray(0); 
    }
};

#endif /* FLOWERPOT_GLVERTEXARRAY_HPP */

