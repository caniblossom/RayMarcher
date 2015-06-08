/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLFRAMEBUFFER_HPP
#define FLOWERPOT_GLFRAMEBUFFER_HPP

#include <vector>
#include "glresource.hpp"

namespace flowerpot {
    class GLFramebuffer : public GLResource {
        public:
            GLFramebuffer();
            virtual ~GLFramebuffer();

            void bindAsDraw() const;
            void bindAsRead() const;

            void unbindFromDraw() const;
            void unbindFromRead() const;
    };

    inline void GLFramebuffer::bindAsDraw() const { 
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, getID()); 
    }
    
    inline void GLFramebuffer::bindAsRead() const { 
        glBindFramebuffer(GL_READ_FRAMEBUFFER, getID()); 
    }

    inline void GLFramebuffer::unbindFromDraw() const { 
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); 
    }
    
    inline void GLFramebuffer::unbindFromRead() const { 
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0); 
    }
};

#endif /* FLOWERPOT_GLFRAMEBUFFER_HPP */

