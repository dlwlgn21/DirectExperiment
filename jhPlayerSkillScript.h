#pragma once
#include "jhScript.h"

namespace jh
{
	enum class eSKillState
	{
		WAIT,
		PLAYING,
		COUNT
	};

	struct SkillStat
	{
		UINT Damage;
		float CoolTime;
		UINT VailedAttackIndex;
	};

	class Transform;
	class PlayerScript;
	class Animator;
	class PlayerSkillScript : public Script
	{
	public:
		PlayerSkillScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator);
		virtual ~PlayerSkillScript() = default;
	
		void Initialize() override;
		void Update() override;

		void SetState(const eSKillState eState);
		const SkillStat& GetStat() const		{ return mSkillStat; }

	protected:
		virtual void setAnimationEvent() = 0;
		virtual void playAnimation() = 0;
		virtual void setOnlyYPositoin() = 0;
		virtual void setWatingPosition() = 0;
		virtual void initSkillStat() = 0;
		void setAnimationFlip();
		void resetCoolTimer();


	protected:
		Transform*				mpTransform;
		Transform*				mpPlayerTransform;
		PlayerScript*			mpPlayerScript;
		Animator*				mpAnimator;
		ePlayerSkillType		meSkillType;
		eSKillState				meState;
		eObjectLookDirection	mePlayerLookDirection;
		SkillStat				mSkillStat;
		float					mTimer;
	};
}
