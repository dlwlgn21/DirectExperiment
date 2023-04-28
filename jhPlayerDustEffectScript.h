#pragma once
#include "jhEffectScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"


namespace jh
{
	class PlayerScript;
	class PlayerDustEffectScript : public EffectScript
	{
	public:
		PlayerDustEffectScript(PlayerScript* pPlayerScript);
		virtual ~PlayerDustEffectScript() = default;

		void Initialize() override;
		void Update() override;
		void setAnimator() override;

		void PlayAnimation();

		void DashStart();
		void DashComplete();
	private:
		const std::wstring				mAnimDashEffectKey;
		PlayerScript*					mpPlayerScript;
		eObjectLookDirection			mePlayerLookDirection;
		Transform*						mpPlayerTransform;
	};

}