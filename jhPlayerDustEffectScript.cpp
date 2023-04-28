#include "jhPlayerDustEffectScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhOnceAnimator.h"
#include "jhAnimation.h"
#include "jhPlayerScript.h"

static constexpr const float LEFT_RIGHT_DISTANCE = 0.0f;

using namespace jh::math;

namespace jh
{
	PlayerDustEffectScript::PlayerDustEffectScript(PlayerScript* pPlayerScript)
		: EffectScript()
		, mpPlayerScript(pPlayerScript)
		, mAnimDashEffectKey(L"PlayerDashAnimKey")
		, mePlayerLookDirection(eObjectLookDirection::RIGHT)
		, mpPlayerTransform(pPlayerScript->GetOwner()->GetTransform())
	{
		assert(mpPlayerScript != nullptr && mpPlayerTransform != nullptr);
	}
	void PlayerDustEffectScript::Initialize()
	{
		setAnimator();
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void PlayerDustEffectScript::Update()
	{
		if (isPlayingAnmation()) { return; }
		switch (meState)
		{
		case eEffectState::WAIT:
			mpTransform->SetPosition(mpPlayerTransform->GetPosition());
			break;
		case eEffectState::PLAYING:
			PlayAnimation();
			break;
		default:
			break;
		}
	}

	void PlayerDustEffectScript::PlayAnimation()
	{
		mpAnimator->SetActive(true);
		mpAnimator->SetPlaying(true);
		mePlayerLookDirection = mpPlayerScript->GetPlayerLookDirection();
		switch (mePlayerLookDirection)
		{
		case eObjectLookDirection::LEFT:
			mpAnimator->SetCurrAnimationHorizontalFlip(false);
			break;
		case eObjectLookDirection::RIGHT:
			mpAnimator->SetCurrAnimationHorizontalFlip(true);
			break;
		default:
			break;
		}
		mpAnimator->PlayAnimationWithReset(mAnimDashEffectKey, false);
	}
	void PlayerDustEffectScript::DashStart()
	{
	}
	void PlayerDustEffectScript::DashComplete()
	{
		mpAnimator->SetComplete();
		SetState(eEffectState::WAIT);
	}
	void PlayerDustEffectScript::setAnimator()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimDashEffectKey) = std::bind(&PlayerDustEffectScript::DashStart, this);
		mpAnimator->GetCompleteEvent(mAnimDashEffectKey) = std::bind(&PlayerDustEffectScript::DashComplete, this);
	}

}