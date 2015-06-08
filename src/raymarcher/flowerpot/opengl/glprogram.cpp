/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <fstream>
#include <iostream>
#include <memory>

#include "../system/systemlog.hpp"
#include "glerror.hpp"
#include "glprogram.hpp"

using namespace std;

namespace flowerpot {
    GLProgram::GLProgram() {
        try {
            GLError::clearAll();
            setID(glCreateProgram());
            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            glDeleteProgram(getID());
            throw GLException(string("Couldn't create program: ") + string(e.what()));
        }
    }

    GLProgram::~GLProgram() {
        try {
            GLError::clearAll();
            glDeleteProgram(getID());
            GLError::throwExceptionOnError();
        } catch (exception& e) {
            system::log() << "Couldn't delete program: " << e.what() << endl;
        }
    };

    GLuint GLProgram::getUniformLocation(const string& name) const {
        GLuint uniform;

        try {
            GLError::clearAll();
            uniform = glGetUniformLocation(getID(), name.c_str());
            GLError::throwExceptionOnError();

            if (uniform == static_cast<GLuint>(-1)) {
                throw GLException(string("No such uniform."));
            }
        }
        catch (GLException& e) {
            throw GLException(string("Couldn't get uniform location for \"") + name + string("\": ") + string(e.what()));
        }

        return uniform;
    }

    GLuint GLProgram::getAttributeLocation(const string& name) const {
        GLuint attribute;

        try {
            GLError::clearAll();
            attribute = glGetAttribLocation(getID(), name.c_str());
            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            throw GLException(string("Couldn't get attribute location for \"") + name + string("\": ") + string(e.what()));
        }

        return attribute;
    }

    void GLProgram::bindAttributeLocation(const string& name, const GLuint index) const {
        try {
            GLError::clearAll();
            glBindAttribLocation(getID(), index, name.c_str());
            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            throw GLException(string("Couldn't bind attribute location for \"") + name + string("\": ") + string(e.what()));
        }
    }

    void GLProgram::bindFragmentDataLocation(const string& name, const GLuint index) const {
        try {
            GLError::clearAll();
            glBindFragDataLocation(getID(), index, name.c_str());
            GLError::throwExceptionOnError();
        }
        catch (GLException& e) {
            throw GLException(string("Couldn't bind fragment shader output location for \"") + name + string("\": ") + string(e.what()));
        }
    }

    void GLProgram::link() const {
        try {
            GLError::clearAll();
            glLinkProgram(getID());
            GLError::throwExceptionOnError();
        } catch (GLException& e) {
            throw GLException(string("Couldn't link program: ") + string(e.what()));
        }
    }

    bool GLProgram::isLinked() const {
        GLint isLinked = GL_FALSE;

        try {
            GLError::clearAll();
            glGetProgramiv(getID(), GL_LINK_STATUS, &isLinked);
            GLError::throwExceptionOnError();
        } catch (GLException& e) {
            throw GLException(string("Couldn't get program linking status: ") + string(e.what()));
        }

        return isLinked == GL_TRUE;
    }

    string GLProgram::getInfoLog() const {
        string str;

        try {
            int maxLength = 0;
            GLError::clearAll();
            glGetProgramiv(getID(), GL_INFO_LOG_LENGTH, &maxLength);
            GLError::throwExceptionOnError();

            if (maxLength == 0) return string();

            unique_ptr< char[] > log(new char[maxLength]);
            glGetProgramInfoLog(getID(), maxLength, 0, log.get());
            GLError::throwExceptionOnError();

            str = string(log.get());
        }
        catch (GLException& e) {
            throw GLException(string("Couldn't get program infolog: ") + string(e.what()));
        }

        return str;
    }

    void GLProgram::attachShader(const GLuint shader) const {
        try {
            GLError::clearAll();
            glAttachShader(getID(), shader);
            GLError::throwExceptionOnError();
        } catch (GLException& e) {
            throw GLException(string("Couldn't attach shader: ") + string(e.what()));
        }
    }

    void GLProgram::detachShader(const GLuint shader) const {
        try {
            GLError::clearAll();
            glDetachShader(getID(), shader);
            GLError::throwExceptionOnError();
        } catch (GLException& e) {
            throw GLException(string("Couldn't detach shader: ") + string(e.what()));
        }
    }

    void GLProgram::detachAllShaders() const {
        vector<GLuint> shaderList = getShaderList();
        for (GLint shader : shaderList) detachShader(shader);
    }

    vector<GLuint> GLProgram::getShaderList() const {
        vector<GLuint> shaderList;

        try {
            GLError::clearAll();

            GLint shaderCount = 0;
            glGetProgramiv(getID(), GL_ATTACHED_SHADERS, &shaderCount);
            GLError::throwExceptionOnError();

            if (shaderCount == 0) return vector<GLuint>();

            unique_ptr<GLuint[]> shaderNames(new GLuint[shaderCount]);
            glGetAttachedShaders(getID(), shaderCount, 0, shaderNames.get());
            GLError::throwExceptionOnError();

            for (int i = 0; i < shaderCount; i++) shaderList.push_back(shaderNames[i]);
        } catch (GLException& e) {
            throw GLException(string("Couldn't get a list of attached shaders: ") + string(e.what()));
        }

        return shaderList;
    }
};

