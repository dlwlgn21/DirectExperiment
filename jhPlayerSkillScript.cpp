#include "jhPlayerSkillScript.h"
#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhTime.h"

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
		, meState(eSKillState::WAIT)
		, mePlayerLookDirection()
		, mSkillStat({ 0, 0.0f, 0 })
		, mTimer(0.0f)
	{
		assert(mpPlayerTransform != nullptr && mpAnimator != nullptr);
	}

	void PlayerSkillScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
		setAnimationEvent();
	}

	void PlayerSkillScript::Update()
	{
		mePlayerLookDirection = mpPlayerScript->GetPlayerLookDirection();
		switch (meState)
		{
		case eSKillState::WAIT:
		{
			setWatingPosition();
			mTimer -= Time::DeltaTime();
			if (mTimer < 0.0f)
			{
				resetCoolTimer();
				setAnimationFlip();
				SetState(eSKillState::PLAYING);
			}
			break;
		}
		case eSKillState::PLAYING:
		{
			setAnimationFlip();
			setOnlyYPositoin();
			playAnimation();
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void PlayerSkillScript::setAnimationFlip()
	{
		if (meState == eSKillState::PLAYING)
		{
			return;
		}
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

	void PlayerSkillScript::resetCoolTimer()
	{
		mTimer = mSkillStat.CoolTime;
	}

	void PlayerSkillScript::SetState(const eSKillState eState)
	{
		meState = eState;
		if (meState == eSKillState::PLAYING)
		{
			mpAnimator->InitializeCurrAnimation();
		}
	}
}