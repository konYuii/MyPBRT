#pragma once
#ifndef __WHITTED_H__
#define __WHITTED_H__

#include "Integrator\Integrator.h"

namespace Feimos {
	class WhittedIntegrator : public SamplerIntegrator {
	public:
		// WhittedIntegrator Public Methods
		WhittedIntegrator(int maxDepth, std::shared_ptr<const Camera> camera,
			std::shared_ptr<Sampler> sampler,
			const Bounds2i& pixelBounds, FrameBuffer* m_FrameBuffer)
			: SamplerIntegrator(camera, sampler, pixelBounds, m_FrameBuffer), maxDepth(maxDepth) {}
		Spectrum Li(const Ray& ray, const Scene& scene,
			Sampler& sampler, int depth) const;
	private:
		// WhittedIntegrator Private Data
		const int maxDepth;
	};
}
#endif // !__WHITTED_H__
