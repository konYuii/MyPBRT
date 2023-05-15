#pragma once
#ifndef __MIRROR_H__
#define __MIRROR_H__

#include "Core\FeimosRender.h"
#include "Material\Reflection.h"
#include "Texture\Texture.h"

namespace Feimos {

	// MirrorMaterial Declarations
	class MirrorMaterial : public Material {
	public:
		// MirrorMaterial Public Methods
		MirrorMaterial(const std::shared_ptr<Texture<Spectrum>>& r,
			const std::shared_ptr<Texture<float>>& bump) {
			Kr = r;
			bumpMap = bump;
		}
		void ComputeScatteringFunctions(SurfaceInteraction* si, TransportMode mode,
			bool allowMultipleLobes) const;

	private:
		// MirrorMaterial Private Data
		std::shared_ptr<Texture<Spectrum>> Kr;
		std::shared_ptr<Texture<float>> bumpMap;
	};

}
#endif // !__MIRROR_H__
