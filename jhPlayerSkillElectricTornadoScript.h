#pragma once
#include "jhPlayerSkillScript.h"

namespace jh
{
	class PlayerSkillElectricTornadoScript final : public PlayerSkillScript
	{
	public:
		PlayerSkillElectricTornadoScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator);
		virtual ~PlayerSkillElectricTornadoScript() = default;

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