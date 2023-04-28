#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"


namespace jh
{
	class Transform;
	class OnceAnimator;
	class PlayerScript;
	class PlayerDustEffectScript : public Script
	{
	public:
		PlayerDustEffectScript(PlayerScript* pPlayerScript);
		virtual ~PlayerDustEffectScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void PlayAnimation(eObjectLookDirection eLookDir);

		void DashStart();
		void DashComplete();

	private:
		void setAnimator();

	private:
		OnceAnimator*					mpAnimator;
		const std::wstring				mAnimDashEffectKey;
		PlayerScript*					mpPlayerScript;
		Transform*						mpTransform;
		Transform*						mpPlayerTransform;
	};

}