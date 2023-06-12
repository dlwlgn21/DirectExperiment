#pragma once
#include "jhPlayerSkillScript.h"

namespace jh
{
	class PlayerSkillElectricStrikeScript final : public PlayerSkillScript
	{
	public:
		PlayerSkillElectricStrikeScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator);
		virtual ~PlayerSkillElectricStrikeScript() = default;

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