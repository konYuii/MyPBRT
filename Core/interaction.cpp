#include "Core\interaction.h"
#include "Core\primitive.h"
#include "Material\Reflection.h"

namespace Feimos {

	// SurfaceInteraction Method Definitions
	SurfaceInteraction::SurfaceInteraction(
		const Point3f& p, const Vector3f& pError, const Point2f& uv,
		const Vector3f& wo, const Vector3f& dpdu, const Vector3f& dpdv,
		const Normal3f& dndu, const Normal3f& dndv, float time, const Shape* shape,
		int faceIndex)
		: Interaction(p, Normal3f(Normalize(Cross(dpdu, dpdv))), pError, wo, time),
		uv(uv),
		dpdu(dpdu),
		dpdv(dpdv),
		dndu(dndu),
		dndv(dndv),
		shape(shape) {
		// Initialize shading geometry from true geometry
		shading.n = n;
		shading.dpdu = dpdu;
		shading.dpdv = dpdv;
		shading.dndu = dndu;
		shading.dndv = dndv;

		// Adjust normal based on orientation and handedness
		/*if (shape &&
		(shape->reverseOrientation ^ shape->transformSwapsHandedness)) {
		n *= -1;
		shading.n *= -1;
		}*/
	}

	SurfaceInteraction::~SurfaceInteraction() {
		if (bsdf)
			bsdf->~BSDF();
	}

	void SurfaceInteraction::ComputeScatteringFunctions(const Ray& ray,
		bool allowMultipleLobes,
		TransportMode mode) {
		primitive->ComputeScatteringFunctions(this, mode,
			allowMultipleLobes);
	}


}



