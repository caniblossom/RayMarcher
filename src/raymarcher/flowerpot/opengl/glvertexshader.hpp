/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLVERTEXSHADER_HPP
#define FLOWERPOT_GLVERTEXSHADER_HPP

#include "glshader.hpp"

namespace flowerpot {
    class GLVertexShader : public GLShader {
        public:
            GLVertexShader();
            virtual ~GLVertexShader() {}
    };

    inline GLVertexShader::GLVertexShader() : GLShader(GL_VERTEX_SHADER) {}
};

#endif /* FLOWERPOT_GLVERTEXSHADER_HPP */

