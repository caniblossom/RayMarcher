/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLSHADER_HPP
#define FLOWERPOT_GLSHADER_HPP

#include <iostream>
#include <string>

#include "glresource.hpp"

namespace flowerpot {
    class GLShader : public GLResource {
        public:
            GLShader(const GLuint type);
            virtual ~GLShader();

            GLint getType() const;

            bool isVertexShader() const;
            bool isFragmentShader() const;

            void compile() const;
            bool isCompiled() const;

            std::string getInfoLog() const;

            void setSourceFromStream(std::istream& is) const;
            void setSourceFromString(const std::string& source) const;
            void setSourceFromFile(const std::string& filename) const;
    };

    inline bool GLShader::isVertexShader() const { 
        return (getType() == GL_VERTEX_SHADER); 
    }
    
    inline bool GLShader::isFragmentShader() const { 
        return (getType() == GL_FRAGMENT_SHADER); 
    }
};

#endif /* FLOWERPOT_GLSHADER_HPP */

