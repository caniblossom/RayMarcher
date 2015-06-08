/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLFRAGMENTSHADER_HPP
#define FLOWERPOT_GLFRAGMENTSHADER_HPP

#include "glshader.hpp"

namespace flowerpot {
    class GLFragmentShader : public GLShader  {
        public:
            GLFragmentShader();
            virtual ~GLFragmentShader() {}
    };

    inline GLFragmentShader::GLFragmentShader() : GLShader(GL_FRAGMENT_SHADER) {}
};

#endif /* FLOWERPOT_GLFRAGMENTSHADER_HPP */

