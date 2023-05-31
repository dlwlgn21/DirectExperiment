#pragma once
#include "jhComponent.h"
#include "jhGraphics.h"

namespace jh
{
	class Light final : public Component
	{
	public:
		Light(const LightAttribute& lightAttribute);
		virtual ~Light() = default;

		void Initialize() override;
		void FixedUpdate() override;

		void SetFollowingTransform(Transform* pTransform) { assert(pTransform != nullptr && mpFollowingTransform == nullptr); mpFollowingTransform = pTransform; }

		jh::math::Vector4 GetDiffuse() const	{ mLightAttirbute.Diffuse; }
		eLightType GetType() const				{ return (eLightType)mLightAttirbute.ELightType; }
		float GetRadius() const					{ mLightAttirbute.Radius; }
		float GetAngle() const					{ mLightAttirbute.Angle; }

	private:
		LightAttribute	mLightAttirbute;
		Transform*		mpTransform;
		Transform*		mpFollowingTransform;
	};
}