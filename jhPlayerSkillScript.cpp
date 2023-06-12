#include "jhPlayerSkillScript.h"
#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhAnimator.h"

using namespace jh::math;

namespace jh
{
	PlayerSkillScript::PlayerSkillScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator)
		: Script()
		, mpPlayerScript(pPlayerScript)
		, mpTransform(nullptr)
		, mpPlayerTransform(pPlayerScript->GetOwner()->GetTransform())
		, mpAnimator(pAnimator)
		, meSkillType(eSkillType)
		, meState(eSKillState::PLAYING)
		, mePlayerLookDirection()
	{
		assert(mpPlayerTransform != nullptr && mpAnimator != nullptr);
	}

	void PlayerSkillScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
		setAnimationEvent();
	}

	void PlayerSkillScript::setAnimationFlip()
	{
		mePlayerLookDirection = mpPlayerScript->GetPlayerLookDirection();
		switch (mePlayerLookDirection)
		{
		case eObjectLookDirection::LEFT:
			mpAnimator->SetCurrAnimationHorizontalFlip(true);
			break;
		case eObjectLookDirection::RIGHT:
			mpAnimator->SetCurrAnimationHorizontalFlip(false);
			break;
		default:
			break;
		}
	}
	void PlayerSkillScript::setOnlyXPositoin()
	{
		mpTransform->SetOnlyXPosition(mpPlayerTransform->GetOnlyXPosition());
	}

}