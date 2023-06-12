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

	class Transform;
	class PlayerScript;
	class Animator;
	class PlayerSkillScript : public Script
	{
	public:
		PlayerSkillScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator);
		virtual ~PlayerSkillScript() = default;
	
		void Initialize() override;
		void SetState(const eSKillState eState) { meState = eState; }


	protected:
		virtual void setAnimationEvent() = 0;
		virtual void playAnimation() = 0;
		void setAnimationFlip();
		void setOnlyXPositoin();


	protected:
		Transform*				mpTransform;
		Transform*				mpPlayerTransform;
		PlayerScript*			mpPlayerScript;
		Animator*				mpAnimator;
		ePlayerSkillType		meSkillType;
		eSKillState				meState;
		eObjectLookDirection	mePlayerLookDirection;
	};
}
