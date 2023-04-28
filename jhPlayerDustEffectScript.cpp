#include "jhPlayerDustEffectScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhOnceAnimator.h"
#include "jhAnimation.h"


namespace jh
{
	PlayerDustEffectScript::PlayerDustEffectScript(PlayerScript* pPlayerScript)
		: Script()
		, mpAnimator(nullptr)
		, mpPlayerScript(pPlayerScript)
		, mAnimDashEffectKey(L"PlayerDashAnimKey")
	{
	}
	void PlayerDustEffectScript::Initialize()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimDashEffectKey) = std::bind(&PlayerDustEffectScript::DashStart, this);
		mpAnimator->GetCompleteEvent(mAnimDashEffectKey) = std::bind(&PlayerDustEffectScript::DashStart, this);
	}
	void PlayerDustEffectScript::Update()
	{

	}
	void PlayerDustEffectScript::FixedUpdate()
	{
	}

	void PlayerDustEffectScript::Render()
	{
	}

	void PlayerDustEffectScript::PlayAnimation(eObjectLookDirection eLookDir)
	{
		mpAnimator->SetActive(true);
		mpAnimator->SetPlaying(true);
		switch (eLookDir)
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
		mpAnimator->PlayAnimationWithReset(mAnimDashEffectKey, false);
	}
	void PlayerDustEffectScript::DashStart()
	{
	}
	void PlayerDustEffectScript::DashComplete()
	{
		mpAnimator->SetComplete();
	}
}