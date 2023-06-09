#include "Core\FeimosRender.h"

#include "Material\MatteMaterial.h"
#include "Material/Reflection.h"

#include "Core\Spectrum.h"
#include "Core\interaction.h"


namespace Feimos {

	// MatteMaterial Method Definitions
	void MatteMaterial::ComputeScatteringFunctions(SurfaceInteraction* si,
		TransportMode mode,
		bool allowMultipleLobes) const {
		// Evaluate textures for _MatteMaterial_ material and allocate BRDF
		si->bsdf = std::make_shared<BSDF>(*si);

		Spectrum r = Kd->Evaluate(*si).Clamp();
		float sig = Clamp(sigma->Evaluate(*si), 0, 90);
		if (!r.IsBlack()) {
			if (sig == 0)
				si->bsdf->Add(new LambertianReflection(r));
			//else
				//si->bsdf->Add(ARENA_ALLOC(arena, OrenNayar)(r, sig));
		}
	}


}







