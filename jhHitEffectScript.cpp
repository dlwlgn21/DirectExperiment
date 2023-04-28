#include "jhHitEffectScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhOnceAnimator.h"
#include "jhAnimation.h"
#include "jhMonsterScript.h"

using namespace jh::math;

namespace jh
{
	HitEffectScript::HitEffectScript(Script* pFollwingScript, const std::wstring& animKey)
		: EffectScript()
		, mAnimHitEffectKey(animKey)
		, mpFollwingScript(pFollwingScript)
		, mpFollwingTransform(nullptr)
		, meType(eHitObjectType::MONSTER)
	{
		mpFollwingTransform = mpFollwingScript->GetOwner()->GetTransform();
		assert(mpFollwingTransform != nullptr);
	}
	void HitEffectScript::Initialize()
	{
		setAnimator();
		mpTransform = GetOwner()->GetTransform();
		Vector3 pos = mpFollwingTransform->GetPosition();
		mpTransform->SetPosition(Vector3(pos.x, pos.y, pos.z - 1.0f));
		mpTransform->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		assert(mpTransform != nullptr);
	}
	void HitEffectScript::Update()
	{
		if (isPlayingAnmation()) { return; }
		switch (meState)
		{
		case eEffectState::WAIT:
		{
			Vector3 pos = mpFollwingTransform->GetPosition();
			mpTransform->SetPosition(Vector3(pos.x, pos.y, pos.z - 1.0f));
			break;
		}
		case eEffectState::PLAYING:
			PlayAnimation();
			break;
		default:
			break;
		}
	}
	void HitEffectScript::FixedUpdate()
	{
	}

	void HitEffectScript::Render()
	{
	}

	void HitEffectScript::setAnimator()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimHitEffectKey) = std::bind(&HitEffectScript::HitStart, this);
		mpAnimator->GetCompleteEvent(mAnimHitEffectKey) = std::bind(&HitEffectScript::HitComplete, this);
	}

	void HitEffectScript::PlayAnimation()
	{
		mpAnimator->SetActive(true);
		mpAnimator->SetPlaying(true);
		eObjectLookDirection eLookDir = eObjectLookDirection::LEFT;
		switch (meType)
		{
		case MONSTER:
		{
			eLookDir = static_cast<MonsterScript*>(mpFollwingScript)->GetMonsterLookDirection();
		}
			break;
		case PLAYER:
			break;
		case COUNT:
			break;
		default:
			break;
		}

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
	void HitEffectScript::HitStart()
	{
	}
	void HitEffectScript::HitComplete()
	{
		mpAnimator->SetComplete();
		SetState(eEffectState::WAIT);
	}
}