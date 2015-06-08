/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_SAMPLE_HPP
#define RAYMARCHER_SAMPLE_HPP

#include "../general/types.hpp"

namespace raymarcher {
    class Sample {
        public:
            RVec3 color;
            Real weight;

            Sample() {}
            Sample(const RVec3& color, const Real weight);

            Sample operator +(const Sample& sample) const;
            Sample& operator +=(const Sample& sample);
    };

    inline Sample::Sample(const RVec3& color, const Real weight) : color(color), weight(weight) {}

    inline Sample Sample::operator +(const Sample& sample) const {
        const Real weightSum = weight + sample.weight;
        return Sample((static_cast<Real>(1.0 / weightSum)) * ((weight * color) + (sample.weight * sample.color)), weightSum);
    }

    inline Sample& Sample::operator +=(const Sample& sample) {
        *this = *this + sample;
        return *this;
    }
};

#endif /* RAYMARCHER_SAMPLE_HPP */

