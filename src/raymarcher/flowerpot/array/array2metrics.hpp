/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_ARRAY2METRICS_HPP
#define	FLOWERPOT_ARRAY2METRICS_HPP

namespace flowerpot {
    namespace array {
        void loopPositions2(
            const unsigned width, 
            const unsigned height,
            std::function<void (const int x, const int y)> func
        );

        void loopPositions2(
            const unsigned maxW, 
            const unsigned maxH, 
            const unsigned maxD,
            const int boxX, 
            const int boxY, 
            const int boxZ, 
            const unsigned boxW,
            const unsigned boxH,
            const unsigned boxD,
            std::function<void (const int x, const int y)> func
        );
        
        inline void loopPositions2(
            const unsigned width, 
            const unsigned height, 
            std::function<void (const int x, const int y)> func
        ) {
            for (int y = 0; y < static_cast<int>(height); y++) {
                for (int x = 0; x < static_cast<int>(width); x++) {
                    func(x, y);
                }
            }
        }
        
        inline void loopPositions2(
            const unsigned maxW, 
            const unsigned maxH, 
            const int boxX, 
            const int boxY, 
            const unsigned boxW,
            const unsigned boxH,
            std::function<void (const int x, const int y)> func
        ) {
            const int tX0 = std::max(0, boxX), tX1 = std::min(static_cast<int>(maxW) - 1, boxX + static_cast<int>(boxW) - 1);
            const int tY0 = std::max(0, boxY), tY1 = std::min(static_cast<int>(maxH) - 1, boxY + static_cast<int>(boxH) - 1);

            const int w = tX1 - tX0 + 1;
            const int h = tY1 - tY0 + 1;

            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    func(boxX + x, boxY + y);
                }
            }        
        }
    }
};

#endif	/* FLOWERPOT_ARRAY2METRICS_HPP */

