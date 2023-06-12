#include "jhPlayerSkillElectricBeamScript.h"
#include "jhMath.h"
#include "jhAnimator.h"
#include "jhPlayerSkillObject.h"

using namespace jh::math;

namespace jh
{
	PlayerSkillElectricBeamScript::PlayerSkillElectricBeamScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator)
		: PlayerSkillScript(eSkillType, pPlayerScript, pAnimator)
	{
	}

	void PlayerSkillElectricBeamScript::Update()
	{
		switch (meState)
		{
		case eSKillState::WAIT:
		{
			break;
		}
		case eSKillState::PLAYING:
		{
			setOnlyXPositoin();
			setAnimationFlip();
			playAnimation();
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void PlayerSkillElectricBeamScript::setAnimationEvent()
	{
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(PlayerSkillObject::ELECTRIC_BEAM_ANIM_KEY) = std::bind(&PlayerSkillElectricBeamScript::SkillStart, this);
		mpAnimator->GetCompleteEvent(PlayerSkillObject::ELECTRIC_BEAM_ANIM_KEY) = std::bind(&PlayerSkillElectricBeamScript::SkillComplete, this);

	}

	void PlayerSkillElectricBeamScript::playAnimation()
	{
		assert(mpAnimator != nullptr);
		//mpAnimator->SetActive(true);
		mpAnimator->PlayAnimation(PlayerSkillObject::ELECTRIC_BEAM_ANIM_KEY, true);
	}
#pragma region COLLISION_TRIGGER
	void PlayerSkillElectricBeamScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{

	}
	void PlayerSkillElectricBeamScript::OnTriggerStay(Collider2D* pOtherCollider)
	{

	}
	void PlayerSkillElectricBeamScript::OnTriggerExit(Collider2D* pOtherCollider)
	{

	}
#pragma endregion


#pragma region ANIMATION_EVENT
	void PlayerSkillElectricBeamScript::SkillStart()
	{
		mpAnimator->InitializeCurrAnimation();
		mpAnimator->SetActive(true);

	}
	void PlayerSkillElectricBeamScript::SkillComplete()
	{
		SetState(eSKillState::WAIT);
		mpAnimator->SetActive(false);
	}
#pragma endregion


}