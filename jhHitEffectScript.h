#pragma once
#include "jhEffectScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"

namespace jh
{
	enum eHitObjectType
	{
		MONSTER,
		PLAYER,
		COUNT
	};
	class Transform;
	class OnceAnimator;
	class Script;
	class PlayerScript;
	class MonsterScript;
	class HitEffectScript : public EffectScript
	{
	public:
		HitEffectScript(MonsterScript* pFollwingScript, PlayerScript* pPlayerScript);
		virtual ~HitEffectScript() = default;

		void Initialize() override;
		void Update() override;


		void setAnimator() override;

		void Hit1Start();
		void Hit1Complete();

		void Hit2Start();
		void Hit2Complete();

		void Hit3Start();
		void Hit3Complete();

		void SetRespawnState()		{ meState = eEffectState::WAIT; }

	public:
		void PlayAnimation();

	private:
		const std::wstring				mAnimHit1EffectKey;
		const std::wstring				mAnimHit2EffectKey;
		const std::wstring				mAnimHit3EffectKey;
		Script*							mpFollwingScript;
		Transform*						mpFollwingTransform;
		eHitObjectType					meType;
		PlayerScript*					mpPlayerScript;
	};

}

