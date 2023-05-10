#pragma once
#include "jhEffectScript.h"


namespace jh
{
	class PlayerScript;
	class PlayerHitEffectScript final : public EffectScript
	{
	public:
		PlayerHitEffectScript(PlayerScript* pPlayerScript);
		virtual ~PlayerHitEffectScript() = default;

		void Initialize() override;
		void Update() override;


		void Hit1Start();
		void Hit1Complete();

		void Hit2Start();
		void Hit2Complete();

		void Hit3Start();
		void Hit3Complete();

	private:
		void playAnimation();
		void setAnimator() override;
	
	private:
		const std::wstring				mHit1AnimKey;
		const std::wstring				mHit2AnimKey;
		const std::wstring				mHit3AnimKey;
		PlayerScript*					mpPlayerScript;
		Transform*						mpPlayerTransform;
		eObjectLookDirection			mePlayerLookDirection;
	};
}