/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#ifndef RAYMARCHER_CAMERA_HPP
#define RAYMARCHER_CAMERA_HPP

#include "rgen.hpp"
#include "ray.hpp"

namespace raymarcher {
    class Camera {
		public:
			Camera() {}
			Camera(
				const RVec3& position,
				const RVec3& upAxis,
				const RVec3& lookAt,
				const RVec2& resolution,
                const Real verticalFOV,
				const Real aperture,
				const Real relFocus
			);

			Ray genRay(const RVec2& element, RGen& gen, const Real life) const;

		private:
			RMat4 _tOrigo;
			RMat4 _tPlane;
            RMat3 _tElement;

            Real _rayLife;
	};

    inline Ray Camera::genRay(const RVec2& element, RGen& gen, const Real life) const {
        const RVec2 rAperture = gen.genOnUnitCircle();
        const RVec3 aperture = _tOrigo.transform(RVec3(rAperture.x, rAperture.y, static_cast<Real>(0.0)));

        const RVec2 rElement = 0.5 * RVec2(gen.genRealNP(), gen.genRealNP());
        const RVec2 target = _tElement.transform(element + rElement);
        const RVec3 plane = _tPlane.transform(RVec3(target.x, target.y, static_cast<Real>(0.0)));

        return Ray(aperture, (plane - aperture).normal(), RVec3(static_cast<Real>(1.0), static_cast<Real>(1.0), static_cast<Real>(1.0)), life);
    }
};

#endif /* RAYMARCHER_CAMERA_HPP */

