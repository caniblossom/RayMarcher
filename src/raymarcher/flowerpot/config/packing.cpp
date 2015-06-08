/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#include <climits>
#include <GL/glew.h>

#include "packing.hpp"

namespace flowerpot {
    static_assert(CHAR_BIT == 8, "Type char needs to be eight bits in size.");

    static_assert((sizeof(float)    % FLOWERPOT_FLOATING_POINT_TYPE_PACKING) == 0, "Type float doesn't seem to pack tightly with current floating point packing value.");
    static_assert((sizeof(double)   % FLOWERPOT_FLOATING_POINT_TYPE_PACKING) == 0, "Type double doesn't seem to pack tightly with current floating point packing value.");
    static_assert((sizeof(GLfloat)  % FLOWERPOT_FLOATING_POINT_TYPE_PACKING) == 0, "Type GLfloat doesn't seem to pack tightly with current floating point packing value.");
    static_assert((sizeof(GLdouble) % FLOWERPOT_FLOATING_POINT_TYPE_PACKING) == 0, "Type GLdouble doesn't seem to pack tightly with current floating point packing value.");
};

