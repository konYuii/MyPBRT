#pragma once
#ifndef __PERSPECTIVE_H__
#define __PERSPECTIVE_H__

#include "Camera/Camera.h"
#include "Sampler/Sampling.h"

namespace Feimos {
	class PerspectiveCamera : public ProjectiveCamera {
	public:
		// PerspectiveCamera Public Methods
		PerspectiveCamera(const int RasterWidth, const int RasterHeight, const Transform& CameraToWorld,
			const Bounds2f& screenWindow, float lensRadius, float focalDistance,
			float fov);
		float GenerateRay(const CameraSample& sample, Ray*) const;
	};
}

#endif // !__PERSPECTIVE_H__
