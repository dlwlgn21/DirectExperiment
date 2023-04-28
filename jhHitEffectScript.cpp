#include "jhHitEffectScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhOnceAnimator.h"
#include "jhAnimation.h"


namespace jh
{
	HitEffectScript::HitEffectScript()
		: Script()
		, mpAnimator(nullptr)
		, mAnimHitEffectKey(L"MonsterHitAnim")
		, meState(eWeaponState::WAITING)
	{
	}
	void HitEffectScript::Initialize()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimHitEffectKey) = std::bind(&HitEffectScript::Start, this);
		mpAnimator->GetCompleteEvent(mAnimHitEffectKey) = std::bind(&HitEffectScript::Complete, this);
		mpAnimator->GetEndEvent(mAnimHitEffectKey) = std::bind(&HitEffectScript::End, this);
	}
	void HitEffectScript::Update()
	{
		
	}
	void HitEffectScript::FixedUpdate()
	{
	}

	void HitEffectScript::Render()
	{
	}

	void HitEffectScript::PlayAnimation(eObjectLookDirection eLookDir)
	{
		mpAnimator->SetActive(true);
		mpAnimator->SetPlaying(true);
		meState = eWeaponState::ATTACKING;
		switch (eLookDir)
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
		mpAnimator->PlayAnimationWithReset(mAnimHitEffectKey, false);
	}
	void HitEffectScript::Start()
	{
	}
	void HitEffectScript::Complete()
	{
		meState = eWeaponState::WAITING;
		mpAnimator->SetComplete();
	}
	void HitEffectScript::End()
	{
	}
}