/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#include <array>
#include <string>

#include "flowerpot/opengl/glfragmentshader.hpp"
#include "flowerpot/opengl/glvertexshader.hpp"
#include "flowerpot/system/systemlog.hpp"

#include "surfacerenderer.hpp"

using namespace std;
using namespace flowerpot;

namespace raymarcher {
    SurfaceRenderer::SurfaceRenderer() {
        loadShaders();
        setupVertexBuffer();
        setupVertexArray();
        setupTexture();
    }

    void SurfaceRenderer::upload(const flowerpot::Surface& surface) {
        _texture.readSurface(surface);
    }

    void SurfaceRenderer::render() {
        glEnable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        _texture.bind();
        _array.bind();

        _program.use();
        glUniform1i(_uniformTex0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        _array.unbind();
        _texture.unbind();
        glDisable(GL_TEXTURE_2D);
    }

    void SurfaceRenderer::loadShaders() {
        GLVertexShader vShader;
        vShader.setSourceFromFile(string("shader/vertex.shader"));
        vShader.compile();

        system::log() << vShader.getInfoLog() << endl;

        GLFragmentShader fShader;
        fShader.setSourceFromFile(string("shader/fragment.shader"));
        fShader.compile();

        system::log() << fShader.getInfoLog() << endl;

        _program.attachShader(vShader);
        _program.attachShader(fShader);
        _program.link();

        system::log() << _program.getInfoLog() << endl;

        _uniformTex0 = _program.getUniformLocation(string("tex0"));
    }

    void SurfaceRenderer::setupVertexBuffer() {
        const std::array<GLfloat, 12> vertices = {
            0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f
        };

        _buffer.bind();
        glBufferData(
            _buffer.getType(),
            vertices.size() * sizeof(vertices[0]),
            vertices.data(),
            GL_STATIC_DRAW
        );
        _buffer.unbind();
    }

    void SurfaceRenderer::setupVertexArray() {
        _array.bind();

        _buffer.bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(0);

        _array.unbind();

        glDisableVertexAttribArray(0);
        _buffer.unbind();
    }

    void SurfaceRenderer::setupTexture() {
        _texture.bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        _texture.unbind();
    }
};

