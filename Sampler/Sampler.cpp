#include "Sampler/Sampler.h"

namespace Feimos {
	Sampler::~Sampler() {}
	Sampler::Sampler(int64_t samplesPerPixel) : samplesPerPixel(samplesPerPixel) {}
	CameraSample Sampler::GetCameraSample(const Point2i& pRaster) {
		CameraSample cs;
		cs.pFilm = (Point2f)pRaster + Get2D();
		cs.time = Get1D();
		cs.pLens = Get2D();
		/*
		cs.pFilm = (Point2f)pRaster;
		cs.time = 0.0f;
		cs.pLens = Point2f(0.0f, 0.0f);
		*/
		return cs;
	}
	void Sampler::StartPixel(const Point2i& p) {
		currentPixel = p;
		currentPixelSampleIndex = 0;
		// Reset array offsets for next pixel sample
		array1DOffset = array2DOffset = 0;
	}
	bool Sampler::StartNextSample() {
		// Reset array offsets for next pixel sample
		array1DOffset = array2DOffset = 0;
		return ++currentPixelSampleIndex < samplesPerPixel;
	}
	bool Sampler::SetSampleNumber(int64_t sampleNum) {
		// Reset array offsets for next pixel sample
		array1DOffset = array2DOffset = 0;
		currentPixelSampleIndex = sampleNum;
		return currentPixelSampleIndex < samplesPerPixel;
	}
	void Sampler::Request1DArray(int n) {
		//CHECK_EQ(RoundCount(n), n);
		samples1DArraySizes.push_back(n);
		sampleArray1D.push_back(std::vector<float>(n * samplesPerPixel));
	}
	void Sampler::Request2DArray(int n) {
		//CHECK_EQ(RoundCount(n), n);
		samples2DArraySizes.push_back(n);
		sampleArray2D.push_back(std::vector<Point2f>(n * samplesPerPixel));
	}
	const float* Sampler::Get1DArray(int n) {
		if (array1DOffset == sampleArray1D.size()) return nullptr;
		//CHECK_EQ(samples1DArraySizes[array1DOffset], n);
		//CHECK_LT(currentPixelSampleIndex, samplesPerPixel);
		return &sampleArray1D[array1DOffset++][currentPixelSampleIndex * n];
	}
	const Point2f* Sampler::Get2DArray(int n) {
		if (array2DOffset == sampleArray2D.size()) return nullptr;
		//CHECK_EQ(samples2DArraySizes[array2DOffset], n);
		//CHECK_LT(currentPixelSampleIndex, samplesPerPixel);
		return &sampleArray2D[array2DOffset++][currentPixelSampleIndex * n];
	}


	PixelSampler::PixelSampler(int64_t samplesPerPixel, int nSampledDimensions)
		: Sampler(samplesPerPixel) {
		for (int i = 0; i < nSampledDimensions; ++i) {
			samples1D.push_back(std::vector<float>(samplesPerPixel));
			samples2D.push_back(std::vector<Point2f>(samplesPerPixel));
		}
	}
	bool PixelSampler::StartNextSample() {
		current1DDimension = current2DDimension = 0;
		return Sampler::StartNextSample();
	}
	bool PixelSampler::SetSampleNumber(int64_t sampleNum) {
		current1DDimension = current2DDimension = 0;
		return Sampler::SetSampleNumber(sampleNum);
	}
	float PixelSampler::Get1D() {
		if (current1DDimension < samples1D.size())
			return samples1D[current1DDimension++][currentPixelSampleIndex];
		else
			return rng.UniformFloat();
	}
	Point2f PixelSampler::Get2D() {
		if (current2DDimension < samples2D.size())
			return samples2D[current2DDimension++][currentPixelSampleIndex];
		else
			return Point2f(rng.UniformFloat(), rng.UniformFloat());
	}


	void GlobalSampler::StartPixel(const Point2i& p) {
		Sampler::StartPixel(p);
		dimension = 0;
		intervalSampleIndex = GetIndexForSample(0);
		// Compute _arrayEndDim_ for dimensions used for array samples
		arrayEndDim =
			arrayStartDim + sampleArray1D.size() + 2 * sampleArray2D.size();

		// Compute 1D array samples for _GlobalSampler_
		for (size_t i = 0; i < samples1DArraySizes.size(); ++i) {
			int nSamples = samples1DArraySizes[i] * samplesPerPixel;
			for (int j = 0; j < nSamples; ++j) {
				int64_t index = GetIndexForSample(j);
				sampleArray1D[i][j] = SampleDimension(index, arrayStartDim + i);
			}
		}

		// Compute 2D array samples for _GlobalSampler_
		int dim = arrayStartDim + samples1DArraySizes.size();
		for (size_t i = 0; i < samples2DArraySizes.size(); ++i) {
			int nSamples = samples2DArraySizes[i] * samplesPerPixel;
			for (int j = 0; j < nSamples; ++j) {
				int64_t idx = GetIndexForSample(j);
				sampleArray2D[i][j].x = SampleDimension(idx, dim);
				sampleArray2D[i][j].y = SampleDimension(idx, dim + 1);
			}
			dim += 2;
		}
	}
	bool GlobalSampler::StartNextSample() {
		dimension = 0;
		intervalSampleIndex = GetIndexForSample(currentPixelSampleIndex + 1);
		return Sampler::StartNextSample();
	}
	bool GlobalSampler::SetSampleNumber(int64_t sampleNum) {
		dimension = 0;
		intervalSampleIndex = GetIndexForSample(sampleNum);
		return Sampler::SetSampleNumber(sampleNum);
	}
	float GlobalSampler::Get1D() {
		if (dimension >= arrayStartDim && dimension < arrayEndDim)
			dimension = arrayEndDim;
		return SampleDimension(intervalSampleIndex, dimension++);
	}
	Point2f GlobalSampler::Get2D() {
		if (dimension + 1 >= arrayStartDim && dimension < arrayEndDim)
			dimension = arrayEndDim;
		Point2f p(SampleDimension(intervalSampleIndex, dimension),
			SampleDimension(intervalSampleIndex, dimension + 1));
		dimension += 2;
		return p;
	}

}