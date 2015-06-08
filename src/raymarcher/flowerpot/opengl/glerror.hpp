/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLERROR_HPP
#define FLOWERPOT_GLERROR_HPP

#include <string>
#include <GL/glew.h>

#include "glexception.hpp"

namespace flowerpot {
    class GLError {
        public:
            static const int MAX_ERROR_COUNT = 256;

            static std::string toString(const GLenum error);

            static void clearAll();
            static void throwExceptionOnError();

            // Checking errors forces OpenGL to flush the pipeline.
            static void disableErrors();
            static void enableErrors();

        private:
            static bool _checkErrors;
    };
};

#endif /* FLOWERPOT_GLERROR_HPP */

