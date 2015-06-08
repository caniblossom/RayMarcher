/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLPROGRAM_HPP
#define FLOWERPOT_GLPROGRAM_HPP

#include <string>
#include <vector>

#include "glresource.hpp"
#include "glshader.hpp"

namespace flowerpot {
    class GLProgram : public GLResource {
        public:
             GLProgram();
            ~GLProgram();

            void use() const;

            GLuint getUniformLocation  (const std::string& name) const;
            GLuint getAttributeLocation(const std::string& name) const;

            void bindAttributeLocation   (const std::string& name, const GLuint index) const;
            void bindFragmentDataLocation(const std::string& name, const GLuint index) const;

            void link() const;
            bool isLinked() const;

            std::string getInfoLog() const;

            void attachShader(const GLuint    shader) const;
            void attachShader(const GLShader& shader) const;
            void detachShader(const GLuint    shader) const;
            void detachShader(const GLShader& shader) const;
            void detachAllShaders() const;

            std::vector<GLuint> getShaderList() const;
    };

    inline void GLProgram::use() const {
        glUseProgram(getID());
    }

    inline void GLProgram::attachShader(const GLShader& shader) const { 
        attachShader(shader.getID()); 
    }
    
    inline void GLProgram::detachShader(const GLShader& shader) const { 
        detachShader(shader.getID()); 
    }
};

#endif /* FLOWERPOT_GLPROGRAM_HPP */

