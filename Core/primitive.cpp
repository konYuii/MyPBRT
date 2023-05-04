#include "Core\primitive.h"
#include "Shape\Shape.h"
#include "Core\interaction.h"


namespace Feimos {

	static long long primitiveMemory = 0;

	Primitive::~Primitive() {}
	// GeometricPrimitive Method Definitions
	GeometricPrimitive::GeometricPrimitive(const std::shared_ptr<Shape>& shape,
		const std::shared_ptr<Material>& material)
		: shape(shape), material(material) {
		primitiveMemory += sizeof(*this);
	}
	Bounds3f GeometricPrimitive::WorldBound() const { return shape->WorldBound(); }
	bool GeometricPrimitive::IntersectP(const Ray& r) const {
		return shape->IntersectP(r);
	}
	bool GeometricPrimitive::Intersect(const Ray& r,
		SurfaceInteraction* isect) const {

		float tHit;
		if (!shape->Intersect(r, &tHit, isect)) return false;
		r.tMax = tHit;
		isect->primitive = this;
		//CHECK_GE(Dot(isect->n, isect->shading.n), 0.);
		// Initialize _SurfaceInteraction::mediumInterface_ after _Shape_
		// intersection
		return true;
	}
	void GeometricPrimitive::ComputeScatteringFunctions(
		SurfaceInteraction* isect, TransportMode mode,
		bool allowMultipleLobes) const {
		if (material)
			material->ComputeScatteringFunctions(isect, mode,
				allowMultipleLobes);
		//CHECK_GE(Dot(isect->n, isect->shading.n), 0.);
	}



}





