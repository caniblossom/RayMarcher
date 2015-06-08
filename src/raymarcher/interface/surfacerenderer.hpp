/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_SURFACERENDERER_HPP
#define RAYMARCHER_SURFACERENDERER_HPP

#include "flowerpot/opengl/glarraybuffer.hpp"
#include "flowerpot/opengl/glprogram.hpp"
#include "flowerpot/opengl/gltexture2D.hpp"
#include "flowerpot/opengl/glvertexarray.hpp"
#include "flowerpot/surface/surface.hpp"

namespace raymarcher {
    class SurfaceRenderer {
        public:
            SurfaceRenderer();

            void upload(const flowerpot::Surface& surface);
            void render();

        private:
            flowerpot::GLProgram     _program;
            flowerpot::GLTexture2D   _texture;
            flowerpot::GLArrayBuffer _buffer;
            flowerpot::GLVertexArray _array;

            GLuint _uniformTex0;

            void loadShaders();
            void setupVertexBuffer();
            void setupVertexArray();
            void setupTexture();
    };
}

#endif /* RAYMARCHER_SURFACERENDERER_HPP */

