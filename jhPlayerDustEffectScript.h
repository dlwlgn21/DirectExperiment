#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"


namespace jh
{
	class Transform;
	class OnceAnimator;
	class PlayerDustEffectScript : public Script
	{
	public:
		PlayerDustEffectScript();
		virtual ~PlayerDustEffectScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void PlayAnimation(eObjectLookDirection eLookDir);

		void DashStart();
		void DashComplete();

	private:
		OnceAnimator*					mpAnimator;
		const std::wstring				mAnimDashEffectKey;
	};

}