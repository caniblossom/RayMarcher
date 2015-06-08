/*
 * Raymarcher
 * Copyright (C) Jani Salo 2015. All rights reserved unless otherwise stated.
 */

#include <cmath>
#include <iostream>

#include "flowerpot/math/constants.hpp"
#include "camera.hpp"

using namespace std;
using namespace flowerpot;

namespace raymarcher {
    Camera::Camera(
        const RVec3& position,
        const RVec3& upAxis,
        const RVec3& lookAt,
        const RVec2& resolution,
        const Real verticalFOV,
        const Real aperture,
        const Real relFocus
    ) {
        const Real z = static_cast<Real>(0.0);
        const Real u = static_cast<Real>(1.0);

        const RVec3 view = lookAt - position;

        // TODO See if it's ok to normalize less.
        const RVec3 zAxis = -view.normal();
        const RVec3 xAxis = upAxis.cross(zAxis).normal();
        const RVec3 yAxis = zAxis.cross(xAxis).normal();

        const RVec3 origoU = aperture * xAxis;
        const RVec3 origoV = aperture * yAxis;
        const RVec3 origoO = position;

        const Real aspectRatio = resolution.x / resolution.y;
        const Real planeYSize = view.length() *  tan(2.0 * math::pi() * 0.5 * verticalFOV / 360.0);
        const RVec2 planeSize(aspectRatio * planeYSize, planeYSize);

        const RVec3 planeU = relFocus * planeSize.x * xAxis;
        const RVec3 planeV = relFocus * planeSize.y * yAxis;
        const RVec3 planeO = relFocus * view + position;

        const RVec2 elementU(2.0 / resolution.x, z);
        const RVec2 elementV(z, 2.0 / resolution.y);
        const RVec2 elementO(-u, -u);

        _tOrigo = RMat4(
            origoU.x, origoU.y, origoU.z, z,
            origoV.x, origoV.y, origoV.z, z,
                   z,        z,        z, z,
            origoO.x, origoO.y, origoO.z, u
        );

        _tPlane = RMat4(
            planeU.x, planeU.y, planeU.z, z,
            planeV.x, planeV.y, planeV.z, z,
                   z,        z,        z, z,
            planeO.x, planeO.y, planeO.z, u
        );

        _tElement = RMat3(
            elementU.x, elementU.y, z,
            elementV.x, elementV.y, z,
            elementO.x, elementO.y, u
        );
    }
};

