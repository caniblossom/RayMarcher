/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_GLEXCEPTION_HPP
#define FLOWERPOT_GLEXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace flowerpot {
    class GLException : public std::exception {
        public:
            GLException(const std::string& message);
            ~GLException() throw() {}

            const char* what() const throw();

        private:
            std::string _message;
    };

    inline GLException::GLException(const std::string& message) : _message(message) {}

    inline const char* GLException::what() const throw() {
        return _message.c_str();
    }
};

#endif /* FLOWERPOT_GLEXCEPTION_HPP */

