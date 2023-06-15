#pragma once
#include "jhEffectScript.h"


namespace jh
{
	class PlayerScript;
	class PlayerLevelUpEffectScript final : public EffectScript
	{
	public:
		PlayerLevelUpEffectScript(PlayerScript* pPlayerScript);
		virtual ~PlayerLevelUpEffectScript() = default;

		void Initialize() override;
		void Update() override;

		void AnimStart();
		void AninComplete();

		
	private:
		void setAnimator() override;
		void playAnimation();

	private:
		const std::wstring				mAnimKey;
		PlayerScript*					mpPlayerScript;
		Transform*						mpPlayerTransform;
	};
}