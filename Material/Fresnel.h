#pragma once
#ifndef __FRESNEL_H__
#define __FRESNEL_H__

#include "Core\FeimosRender.h"
#include "Core\Spectrum.h"



namespace Feimos {

	// Reflection Declarations
	float FrDielectric(float cosThetaI, float etaI, float etaT);
	Spectrum FrConductor(float cosThetaI, const Spectrum& etaI,
		const Spectrum& etaT, const Spectrum& k);

	class Fresnel {
	public:
		// Fresnel Interface
		virtual ~Fresnel() {}
		virtual Spectrum Evaluate(float cosI) const = 0;
	};

	class FresnelConductor : public Fresnel {
	public:
		// FresnelConductor Public Methods
		Spectrum Evaluate(float cosThetaI) const;
		FresnelConductor(const Spectrum& etaI, const Spectrum& etaT,
			const Spectrum& k)
			: etaI(etaI), etaT(etaT), k(k) {}

	private:
		Spectrum etaI, etaT, k;
	};

	class FresnelDielectric : public Fresnel {
	public:
		// FresnelDielectric Public Methods
		Spectrum Evaluate(float cosThetaI) const;
		FresnelDielectric(float etaI, float etaT) : etaI(etaI), etaT(etaT) {}

	private:
		float etaI, etaT;
	};

	class FresnelNoOp : public Fresnel {
	public:
		Spectrum Evaluate(float) const { return Spectrum(1.); }
	};
}
#endif // !__FRESNEL_H__
