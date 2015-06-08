/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLTEXTURE_HPP
#define FLOWERPOT_GLTEXTURE_HPP

#include "glresource.hpp"

namespace flowerpot {
     class GLTexture : public GLResource {
        public:
            GLTexture();
            virtual ~GLTexture();
     };
};

#endif /* FLOWERPOT_GLTEXTURE_HPP */

