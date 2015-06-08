/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_TYPES_HPP
#define RAYMARCHER_TYPES_HPP

#include "flowerpot/math/vec2.hpp"
#include "flowerpot/math/vec3.hpp"
#include "flowerpot/math/mat3.hpp"
#include "flowerpot/math/mat4.hpp"

namespace raymarcher {
	typedef double Real ;

	typedef flowerpot::Vec2<Real> RVec2;
	typedef flowerpot::Vec3<Real> RVec3;

	typedef flowerpot::Mat3<Real> RMat3;
	typedef flowerpot::Mat4<Real> RMat4;
};

#endif /* RAYMARCHER_TYPES_HPP */

