/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLRESOURCE_HPP
#define FLOWERPOT_GLRESOURCE_HPP

#include <utility>
#include <GL/glew.h>

namespace flowerpot {
    class GLResource{
        public:
            GLResource();
            virtual ~GLResource() {}

            GLResource(const GLResource& r) = delete;
            GLResource& operator =(const GLResource& r) = delete;

            GLResource(GLResource&& r);
            GLResource& operator =(GLResource&& r);

            bool isOK() const;

            GLuint getID() const;
            void   setID(const GLuint id);

        private:
            GLuint _id;
    };

    inline GLResource::GLResource() : _id(0) {}

    inline GLResource::GLResource(GLResource&& r) : _id(std::move(r._id)) {
        r._id = 0;
    }

    inline GLResource& GLResource::operator =(GLResource&& r) {
        if (this == &r) return *this; 
        _id = std::move(r._id);
        r._id = 0;

        return *this;
    }
    
    inline bool GLResource::isOK() const {
        return _id != 0;
    }

    inline GLuint GLResource::getID() const { 
        return _id; 
    }
    
    inline void GLResource::setID(const GLuint id) { 
        _id = id; 
    }
};

#endif /* FLOWERPOT_GLRESOURCE_HPP */

