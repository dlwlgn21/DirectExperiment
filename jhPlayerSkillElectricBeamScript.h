#pragma once
#include "jhPlayerSkillScript.h"

namespace jh
{
	class PlayerSkillElectricBeamScript final : public PlayerSkillScript
	{
	public:
		PlayerSkillElectricBeamScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator);
		virtual ~PlayerSkillElectricBeamScript() = default;

		void AnimationSkillStart();
		void AnimationSkillComplete();

	private:
		void setAnimationEvent() override;
		void playAnimation() override;
		void setOnlyYPositoin() override;
		void setWatingPosition() override;
		void initSkillStat() override;
	private:
		const std::wstring mAnimKey;
	};
}


