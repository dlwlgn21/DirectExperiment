#include "jhHitEffectScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhOnceAnimator.h"
#include "jhAnimation.h"
#include "jhMonsterScript.h"
#include "jhPlayerScript.h"
#include "jhLayerZValue.h"

using namespace jh::math;

namespace jh
{
	HitEffectScript::HitEffectScript(MonsterScript* pFollwingScript, PlayerScript* pPlayerScript)
		: EffectScript()
		, mAnimHit1EffectKey(MonsterManager::HIT_COMBO_1_ELECTRIC_EFFECT_ANIM_KEY)
		, mAnimHit2EffectKey(MonsterManager::HIT_COMBO_2_ELECTRIC_EFFECT_ANIM_KEY)
		, mAnimHit3EffectKey(MonsterManager::HIT_COMBO_3_ELECTRIC_EFFECT_ANIM_KEY)
		, mpFollwingScript(pFollwingScript)
		, mpFollwingTransform(nullptr)
		, mpPlayerScript(pPlayerScript)
		, meType(eHitObjectType::MONSTER)
	{
		mpFollwingTransform = mpFollwingScript->GetOwner()->GetTransform();
		assert(mpFollwingTransform != nullptr && mpPlayerScript != nullptr);
	}
	void HitEffectScript::Initialize()
	{
		setAnimator();
		const float EFFECT_SCALUE_VALUE = 6.0f;
		mpTransform = GetOwner()->GetTransform();
		Vector3 pos = mpFollwingTransform->GetPosition();
		mpTransform->SetPosition(Vector3(pos.x, pos.y, MONSTER_EFFECT_Z_VALUE));
		mpTransform->SetOnlyXYScale(EFFECT_SCALUE_VALUE);
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
			mpTransform->SetOnlyXYPosition(pos.x, pos.y);
			break;
		}
		case eEffectState::PLAYING:
			PlayAnimation();
			break;
		default:
			break;
		}
	}


	void HitEffectScript::setAnimator()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimHit1EffectKey) = std::bind(&HitEffectScript::Hit1Start, this);
		mpAnimator->GetCompleteEvent(mAnimHit1EffectKey) = std::bind(&HitEffectScript::Hit1Complete, this);

		mpAnimator->GetStartEvent(mAnimHit2EffectKey) = std::bind(&HitEffectScript::Hit2Start, this);
		mpAnimator->GetCompleteEvent(mAnimHit2EffectKey) = std::bind(&HitEffectScript::Hit2Complete, this);

		mpAnimator->GetStartEvent(mAnimHit3EffectKey) = std::bind(&HitEffectScript::Hit3Start, this);
		mpAnimator->GetCompleteEvent(mAnimHit3EffectKey) = std::bind(&HitEffectScript::Hit3Complete, this);
	}

	void HitEffectScript::Hit1Start()
	{
	}

	void HitEffectScript::Hit1Complete()
	{
		mpAnimator->SetComplete();
		SetState(eEffectState::WAIT);
	}

	void HitEffectScript::Hit2Start()
	{
	}

	void HitEffectScript::Hit2Complete()
	{
		mpAnimator->SetComplete();
		SetState(eEffectState::WAIT);
	}

	void HitEffectScript::Hit3Start()
	{

	}

	void HitEffectScript::Hit3Complete()
	{
		mpAnimator->SetComplete();
		SetState(eEffectState::WAIT);
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
			break;
		}
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

		switch (mpPlayerScript->GetComboAttackType())
		{
		case eComboAttackType::ONE:
		{
			mpAnimator->PlayAnimationWithReset(mAnimHit1EffectKey, false);
			break;
		}
		case eComboAttackType::TWO:
		{
			mpAnimator->PlayAnimationWithReset(mAnimHit2EffectKey, false);
			break;
		}
		case eComboAttackType::THREE:
		{
			mpAnimator->PlayAnimationWithReset(mAnimHit3EffectKey, false);
			break;
		}
		default:
			assert(false);
			break;
		}
	}
}