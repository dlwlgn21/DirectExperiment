#pragma once
#include "jhPlayerSkillScript.h"

namespace jh
{
	class PlayerSkillElectricBeamScript final : public PlayerSkillScript
	{
	public:
		PlayerSkillElectricBeamScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator);
		virtual ~PlayerSkillElectricBeamScript() = default;
		
		void Update() override;

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

	public:
		void SkillStart();
		void SkillComplete();

	private:
		void setAnimationEvent() override;
		void playAnimation() override;
	};
}


