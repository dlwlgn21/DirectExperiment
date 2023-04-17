#include "jhEffectScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhOnceAnimator.h"
#include "jhAnimation.h"


namespace jh
{
	EffectScript::EffectScript()
		: Script()
		, mpAnimator(nullptr)
		, mAnimHitEffectKey(L"MonsterHitAnim")
		, meState(eWeaponState::WAITING)
	{
	}
	void EffectScript::Initialize()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimHitEffectKey) = std::bind(&EffectScript::Start, this);
		mpAnimator->GetCompleteEvent(mAnimHitEffectKey) = std::bind(&EffectScript::Complete, this);
		mpAnimator->GetEndEvent(mAnimHitEffectKey) = std::bind(&EffectScript::End, this);
	}
	void EffectScript::Update()
	{
		
	}
	void EffectScript::FixedUpdate()
	{
	}

	void EffectScript::Render()
	{
	}

	void EffectScript::PlayAnimation(eObjectLookDirection eLookDir)
	{
		mpAnimator->SetActive(true);
		mpAnimator->SetPlaying(true);
		meState = eWeaponState::ATTACKING;
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
		mpAnimator->PlayAnimationWithReset(mAnimHitEffectKey, false);
	}
	void EffectScript::Start()
	{
	}
	void EffectScript::Complete()
	{
		meState = eWeaponState::WAITING;
		mpAnimator->SetComplete();
	}
	void EffectScript::End()
	{
	}
}