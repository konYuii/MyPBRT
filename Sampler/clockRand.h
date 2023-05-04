#pragma once
#ifndef __CLOCKRAND_H__
#define __CLOCKRAND_H__

#include "Core\FeimosRender.h"
#include "Sampler\Sampler.h"
#include "Sampler\TimeClockRandom.h"

namespace Feimos {
	class ClockRandSampler : public GlobalSampler {
	public:
		// HaltonSampler Public Methods
		ClockRandSampler(int samplesPerPixel = 16, const Bounds2i& sampleBounds = Bounds2i(Point2i(0, 0), Point2i(100, 100))) :GlobalSampler(samplesPerPixel) {
			ClockRandomInit();
		}
		std::unique_ptr<Sampler> Clone(int seed) {
			return std::unique_ptr<Sampler>(new ClockRandSampler(*this));
		}
		int64_t GetIndexForSample(int64_t sampleNum) const {
			return 0;
		}
		float SampleDimension(int64_t index, int dimension) const {
			return getClockRandom();
		}
	};
}
#endif // !__CLOCKRAND_H__
