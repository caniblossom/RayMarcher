/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef KUKKAGEN_TRACERSETTINGS_HPP
#define KUKKAGEN_TRACERSETTINGS_HPP

#include "../general/types.hpp"

namespace raymarcher {
    class TracerSettings {
        public:
            unsigned blockWidth;
            unsigned blockHeight;
            unsigned sampleCount;
            unsigned lambertianRadSamples;
            unsigned lambertianAngSamples;
            Real rayInitialLife;

            TracerSettings(
                const unsigned blockWidth  = 16,
                const unsigned blockHeight = 16,
                const unsigned sampleCount = 64,
                const unsigned lambertianRadSamples = 8,
                const unsigned lambertianAngSamples = 8,
                const Real rayInitialLife = static_cast<Real>(1.0)
            );
    };

    inline TracerSettings::TracerSettings(
        const unsigned blockWidth,
        const unsigned blockHeight,
        const unsigned sampleCount,
        const unsigned lambertianRadSamples,
        const unsigned lambertianAngSamples,
        const Real rayInitialLife
    ) :
        blockWidth(blockWidth),
        blockHeight(blockHeight),
        sampleCount(sampleCount),
        lambertianRadSamples(lambertianRadSamples),
        lambertianAngSamples(lambertianAngSamples),
        rayInitialLife(rayInitialLife)
    {}
};

#endif /* KUKKAGEN_TRACERSETTINGS_HPP */

