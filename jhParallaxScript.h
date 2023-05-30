#pragma once
#include "jhScript.h"
#include "jhMath.h"

namespace jh
{
	class Transform;
	class ParallaxScript final : public Script
	{
	public:
		ParallaxScript(const float zValue, const float parallaxFactor);
		virtual ~ParallaxScript() = default;

		void Initialize() override;
		void Update() override;
	private:
		Transform*				mpTransform;
		Transform*				mpCameraTransform;
		math::Vector2			mStartPos;
		math::Vector2			mTravelVector;
		const float				mParallaxFactor;
		const float				mOriginZ;
		float					mStartZ;
	};

}

