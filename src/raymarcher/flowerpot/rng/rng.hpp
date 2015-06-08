/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

/*
 * A wrapper for the Velox 3b pseudorandom number generator by Elias Yarrkov.
 * See http://cipherdev.org for more information.
 */

#ifndef FLOWERPOT_RNG_HPP
#define FLOWERPOT_RNG_HPP

#include <cstdint>
#include <ctime>

#include "../integer/roll.hpp"

namespace flowerpot {
    class RNG {
        public:
            RNG(const std::uint32_t seed = 0);

            std::uint32_t genUInt();

            template <typename T>
            T genReal();

        private:
            std::uint32_t _pos;
            std::uint32_t _vec[4], _ctr[4];

            void mix();
    };

    inline RNG::RNG(const std::uint32_t seed) : _pos(0) {
        for (int i = 0; i < 4; i++) _vec[i] = _ctr[i] = i * 0x9E3779B9;
        _vec[0] ^= seed;

        for (int i = 0; i < 16; i++) genUInt();
    }

    inline std::uint32_t RNG::genUInt() {
        if (_pos == 0) mix();
        return _vec[--_pos];
    }

    template <typename T>
    T RNG::genReal() {
        return static_cast<T> (genUInt()) / static_cast<T>(4294967296.0);
    }

    inline void RNG::mix() {
        _vec[0] = integer::rol32(_vec[0] + _vec[3], 21);
        _vec[1] = integer::rol32(_vec[1], 12) + _vec[2];
        _vec[2] = _vec[2] ^ _vec[0];
        _vec[3] = _vec[3] ^ _vec[1];
        _vec[0] = integer::rol32(_vec[0] + _vec[3], 19);
        _vec[1] = integer::rol32(_vec[1], 24) + _vec[2];
        _vec[2] = _vec[2] ^ _vec[0];
        _vec[3] = _vec[3] ^ _vec[1];
        _vec[0] = integer::rol32(_vec[0] + _vec[3],  7);
        _vec[1] = integer::rol32(_vec[1], 12) + _vec[2];
        _vec[2] = _vec[2] ^ _vec[0];
        _vec[3] = _vec[3] ^ _vec[1];
        _vec[0] = integer::rol32(_vec[0] + _vec[3], 27);
        _vec[1] = integer::rol32(_vec[1], 17) + _vec[2];
        _vec[2] = _vec[2] ^ _vec[0];
        _vec[3] = _vec[3] ^ _vec[1];

        for (int i = 0; i < 4; i++) _vec[i] += _ctr[i];
        for (int i = 0; i < 4; i++) if(++_ctr[i]) break;

        _pos = 4;
    }
};

#endif /* FLOWERPOT_RNG_HPP */

