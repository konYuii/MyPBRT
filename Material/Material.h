#pragma once
#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include "Core/FeimosRender.h"
namespace Feimos {
	enum class TransportMode { Radiance, Importance };

	// Material Declarations
	class Material {
	public:
		// Material Interface
		virtual void ComputeScatteringFunctions(SurfaceInteraction* si,
			TransportMode mode,
			bool allowMultipleLobes) const = 0;
		virtual ~Material() {}
	};
}
#endif // !__MATERIAL_H__
