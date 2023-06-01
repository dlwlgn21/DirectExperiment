#include "jhPlayerHitEffectScript.h"
#include "jhOnceAnimator.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"
#include "jhPlayer.h"
#include "jhDebugHelper.h"
#include "jhLayerZValue.h"

using namespace jh::math;

namespace jh
{
	PlayerHitEffectScript::PlayerHitEffectScript(PlayerScript* pPlayerScript)
		: EffectScript()
		, mHit1AnimKey(Player::HIT_1_ANIM_KEY)
		, mHit2AnimKey(Player::HIT_2_ANIM_KEY)
		, mHit3AnimKey(Player::HIT_3_ANIM_KEY)
		, mpPlayerScript(pPlayerScript)
		, mpPlayerTransform(pPlayerScript->GetOwner()->GetTransform())
		, mePlayerLookDirection(pPlayerScript->GetPlayerLookDirection())
	{
		assert(pPlayerScript != nullptr && mpPlayerTransform != nullptr);
	}
	void PlayerHitEffectScript::Initialize()
	{
		setAnimator();
		const float EFFECT_SCALE_VALUE = 6.0f;
		mpTransform = GetOwner()->GetTransform();
		Vector3 pos = mpPlayerTransform->GetPosition();
		mpTransform->SetPosition(Vector3(pos.x, pos.y, PLAYER_EFFECT_Z_VALUE));
		mpTransform->SetOnlyXYScale(EFFECT_SCALE_VALUE);
		assert(mpTransform != nullptr);
		//SetState(eEffectState::PLAYING);
	}
	void PlayerHitEffectScript::Update()
	{
		if (isPlayingAnmation()) { return; }
		switch (meState)
		{
		case eEffectState::WAIT:
		{
			Vector3 pos = mpPlayerTransform->GetPosition();
			mpTransform->SetOnlyXYPosition(pos.x, pos.y);
			break;
		}
		case eEffectState::PLAYING:
		{
			playAnimation();
			break;
		}
		default:
			break;
		}
	}

	void PlayerHitEffectScript::playAnimation()
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
		mpAnimator->PlayAnimationWithReset(mHit3AnimKey, false);
	}

	void PlayerHitEffectScript::Hit1Start()
	{
	}

	void PlayerHitEffectScript::Hit1Complete()
	{
		mpAnimator->SetComplete();
		SetState(eEffectState::WAIT);
	}

	void PlayerHitEffectScript::Hit2Start()
	{
	}

	void PlayerHitEffectScript::Hit2Complete()
	{
		mpAnimator->SetComplete();
		SetState(eEffectState::WAIT);
	}

	void PlayerHitEffectScript::Hit3Start()
	{
	}

	void PlayerHitEffectScript::Hit3Complete()
	{
		mpAnimator->SetComplete();
		SetState(eEffectState::WAIT);
	}

	void PlayerHitEffectScript::setAnimator()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mHit1AnimKey) = std::bind(&PlayerHitEffectScript::Hit1Start, this);
		mpAnimator->GetCompleteEvent(mHit1AnimKey) = std::bind(&PlayerHitEffectScript::Hit1Complete, this);

		mpAnimator->GetStartEvent(mHit2AnimKey) = std::bind(&PlayerHitEffectScript::Hit2Start, this);
		mpAnimator->GetCompleteEvent(mHit2AnimKey) = std::bind(&PlayerHitEffectScript::Hit2Complete, this);

		mpAnimator->GetStartEvent(mHit3AnimKey) = std::bind(&PlayerHitEffectScript::Hit3Start, this);
		mpAnimator->GetCompleteEvent(mHit3AnimKey) = std::bind(&PlayerHitEffectScript::Hit3Complete, this);
	}
}