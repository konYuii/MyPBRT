#pragma once
#ifndef __FeimosRender_h__
#define __FeimosRender_h__

#include <memory>
#include <limits>
#include <cmath>

namespace Feimos {

	static constexpr float Pi = 3.14159265358979323846;
	static constexpr float InvPi = 0.31830988618379067154;
	static constexpr float Inv2Pi = 0.15915494309189533577;
	static constexpr float Inv4Pi = 0.07957747154594766788;
	static constexpr float PiOver2 = 1.57079632679489661923;
	static constexpr float PiOver4 = 0.78539816339744830961;
	static constexpr float Sqrt2 = 1.41421356237309504880;
	inline constexpr float Radians(float deg) { return (Pi / 180) * deg; }

#define MachineEpsilon (std::numeric_limits<float>::epsilon() * 0.5)
	inline float gamma(int n) {
		return (n * MachineEpsilon) / (1 - n * MachineEpsilon);
	}

#define CHECK_NE(a,b) 
#define DCHECK(a)

#define Infinity std::numeric_limits<float>::infinity()

	static constexpr float ShadowEpsilon = 0.0001f;

	template <typename T>
	class Vector2;
	template <typename T>
	class Vector3;
	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector3<float> Vector3f;
	typedef Vector3<int> Vector3i;
	template <typename T>
	class Point3;
	template <typename T>
	class Point2;
	typedef Point2<float> Point2f;
	typedef Point2<int> Point2i;
	typedef Point3<float> Point3f;
	typedef Point3<int> Point3i;
	template <typename T>
	class Normal3;
	template <typename T>
	class Bounds2;
	template <typename T>
	class Bounds3;
	typedef Bounds2<float> Bounds2f;
	typedef Bounds2<int> Bounds2i;
	typedef Bounds3<float> Bounds3f;
	typedef Bounds3<int> Bounds3i;

	template <int nSpectrumSamples>
	class CoefficientSpectrum;
	class RGBSpectrum;
	typedef RGBSpectrum Spectrum;

	struct Matrix4x4;
	class Transform;
	class Ray;

	class Shape;
	struct Interaction;
	class SurfaceInteraction;
	class Primitive;
	class GeometricPrimitive;
	class Aggregate;

	class Camera;
	class ProjectiveCamera;
	class PerspectiveCamera;
	class OrthographicCamera;

	class Sampler;
	class PixelSampler;
	class GlobalSampler;
	class HaltonSampler;
	class ClockRandSampler;

	class Sampler;
	class Scene;
	class BxDF;
	class BSDF;
	class Material;
	class Light;
	class AreaLight;
	class VisibilityTester;

	class Distribution1D;
	class Distribution2D;
	class LightDistribution;

	template <typename T>
	inline bool isNaN(const T x) {
		return std::isnan(x);
	}
	template <>
	inline bool isNaN(const int x) {
		return false;
	}
	inline uint32_t FloatToBits(float f) {
		uint32_t ui;
		memcpy(&ui, &f, sizeof(float));
		return ui;
	}

	inline float BitsToFloat(uint32_t ui) {
		float f;
		memcpy(&f, &ui, sizeof(uint32_t));
		return f;
	}
	inline float NextFloatUp(float v) {
		// Handle infinity and negative zero for _NextFloatUp()_
		if (std::isinf(v) && v > 0.) return v;
		if (v == -0.f) v = 0.f;

		// Advance _v_ to next higher float
		uint32_t ui = FloatToBits(v);
		if (v >= 0)
			++ui;
		else
			--ui;
		return BitsToFloat(ui);
	}
	inline float NextFloatDown(float v) {
		// Handle infinity and positive zero for _NextFloatDown()_
		if (std::isinf(v) && v < 0.) return v;
		if (v == 0.f) v = -0.f;
		uint32_t ui = FloatToBits(v);
		if (v > 0)
			--ui;
		else
			++ui;
		return BitsToFloat(ui);
	}

	template <typename Predicate>
	int FindInterval(int size, const Predicate& pred) {
		int first = 0, len = size;
		while (len > 0) {
			int half = len >> 1, middle = first + half;
			// Bisect range based on value of _pred_ at _middle_
			if (pred(middle)) {
				first = middle + 1;
				len -= half + 1;
			}
			else
				len = half;
		}
		return Clamp(first - 1, 0, size - 2);
	}

	template <typename T, typename U, typename V>
	inline T Clamp(T val, U low, V high) {
		if (val < low)
			return low;
		else if (val > high)
			return high;
		else
			return val;
	}
	inline float Lerp(float t, float v1, float v2) { return (1 - t) * v1 + t * v2; }

	template <typename T>
	inline T Mod(T a, T b) {
		T result = a - (a / b) * b;
		return (T)((result < 0) ? result + b : result);
	}
	template <>
	inline float Mod(float a, float b) {
		return std::fmod(a, b);
	}


}



#endif


