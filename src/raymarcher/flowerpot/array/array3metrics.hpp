/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_ARRAY3METRICS_HPP
#define	FLOWERPOT_ARRAY3METRICS_HPP

namespace flowerpot {
    namespace array {
        void loopPositions3(
            const unsigned width, 
            const unsigned height, 
            const unsigned depth, 
            std::function<void (const int x, const int y, const int z)> func
        );

        void loopPositions3(
            const unsigned maxW, 
            const unsigned maxH, 
            const unsigned maxD,
            const int boxX, 
            const int boxY, 
            const int boxZ, 
            const unsigned boxW,
            const unsigned boxH,
            const unsigned boxD,
            std::function<void (const int x, const int y, const int z)> func
        );

        inline void loopPositions3(
            const unsigned width, 
            const unsigned height, 
            const unsigned depth, 
            std::function<void (const int x, const int y, const int z)> func
        ) {
            for (int z = 0; z < static_cast<int>(depth); z++) {
                for (int y = 0; y < static_cast<int>(height); y++) {
                    for (int x = 0; x < static_cast<int>(width); x++) {
                        func(x, y, z);
                    }
                }
            }
        }
        
        inline void loopPositions3(
            const unsigned maxW, 
            const unsigned maxH, 
            const unsigned maxD,
            const int boxX, 
            const int boxY, 
            const int boxZ, 
            const unsigned boxW,
            const unsigned boxH,
            const unsigned boxD,
            std::function<void (const int x, const int y, const int z)> func
        ) {
            const int tX0 = std::max(0, boxX), tX1 = std::min(static_cast<int>(maxW) - 1, boxX + static_cast<int>(boxW) - 1);
            const int tY0 = std::max(0, boxY), tY1 = std::min(static_cast<int>(maxH) - 1, boxY + static_cast<int>(boxH) - 1);
            const int tZ0 = std::max(0, boxZ), tZ1 = std::min(static_cast<int>(maxD) - 1, boxZ + static_cast<int>(boxD) - 1);

            const int w = tX1 - tX0 + 1;
            const int h = tY1 - tY0 + 1;
            const int d = tZ1 - tZ0 + 1;

            for (int z = 0; z < d; z++) {
                for (int y = 0; y < h; y++) {
                    for (int x = 0; x < w; x++) {
                        func(boxX + x, boxY + y, boxZ + z);
                    }
                }        
            }        
        }
    }
};

#endif	/* FLOWERPOT_ARRAY3METRICS_HPP */

