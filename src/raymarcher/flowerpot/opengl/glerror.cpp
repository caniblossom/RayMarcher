/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include "glerror.hpp"

using namespace std;

namespace flowerpot {
    string GLError::toString(const GLenum error) {
        switch (error) {
            case GL_NO_ERROR:          return string("GL_NO_ERROR");
            case GL_INVALID_ENUM:      return string("GL_INVALID_ENUM");
            case GL_INVALID_VALUE:     return string("GL_INVALID_VALUE");
            case GL_INVALID_OPERATION: return string("GL_INVALID_OPERATION");
            case GL_STACK_OVERFLOW:    return string("GL_STACK_OVERFLOW");
            case GL_STACK_UNDERFLOW:   return string("GL_STACK_UNDERFLOW");
            case GL_OUT_OF_MEMORY:     return string("GL_OUT_OF_MEMORY");
            case GL_TABLE_TOO_LARGE:   return string("GL_TABLE_TOO_LARGE");
        }

        return string("Unknown OpenGL error.");
    }

    void GLError::clearAll() {
        if (!_checkErrors) return;
        for (int i = 0; i < MAX_ERROR_COUNT; i++) {
            if (glGetError() == GL_NO_ERROR) return;
        }
    }

    void GLError::throwExceptionOnError() {
        if (!_checkErrors) return;

        string str;
        for (int i = 0; i < MAX_ERROR_COUNT; i++) {
            const GLenum error = glGetError();
            if (error == GL_NO_ERROR) break;
            if (i > 0) str.append(", ");
            str.append(toString(error));
        }

        if (str.size() > 0) throw GLException(str);
    }

    void GLError::disableErrors() { 
        _checkErrors = false; 
    }
    
    void GLError::enableErrors() { 
        _checkErrors = true;  
    }

    bool GLError::_checkErrors = true;
}

