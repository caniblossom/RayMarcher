/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_LOG_HPP
#define FLOWERPOT_LOG_HPP

#include <fstream>
#include <string>

namespace flowerpot {
    class Log {
        public:
            Log(const std::string& filename);
            virtual ~Log();

            Log(const Log& log) = delete;
            Log& operator =(const Log& log) = delete;

            std::fstream& getOutput();
            
            Log& operator <<(std::ostream& (*manipulator)(std::ostream& os));
            template <typename T> Log& operator <<(const T& t);

        private:
            std::fstream _output;
    };

    inline Log& Log::operator <<(std::ostream& (*manipulator)(std::ostream& os)) {
        manipulator(_output);
        return *this;
    }

    template <typename T>
    Log& Log::operator <<(const T& t) {
        _output << t;
        return *this;
    }
};

#endif /* FLOWERPOT_LOG_HPP */

