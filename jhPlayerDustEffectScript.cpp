#include "jhPlayerDustEffectScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhOnceAnimator.h"
#include "jhAnimation.h"
#include "jhPlayerScript.h"

static constexpr const float LEFT_RIGHT_DISTANCE = 1.5f;

using namespace jh::math;

namespace jh
{
	PlayerDustEffectScript::PlayerDustEffectScript(PlayerScript* pPlayerScript)
		: Script()
		, mpAnimator(nullptr)
		, mpPlayerScript(pPlayerScript)
		, mAnimDashEffectKey(L"PlayerDashAnimKey")
		, mpTransform(nullptr)
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
		Vector3 playerPos = mpPlayerTransform->GetPosition();
		Vector3 pos = mpTransform->GetPosition();
		const eObjectLookDirection ePlayerLookDir = mpPlayerScript->GetPlayerLookDirection();
		switch (ePlayerLookDir)
		{
		case eObjectLookDirection::LEFT:
			pos.x = playerPos.x + LEFT_RIGHT_DISTANCE;
			break;
		case eObjectLookDirection::RIGHT:
			pos.x = playerPos.x - LEFT_RIGHT_DISTANCE;
			break;
		default:
			break;
		}
		mpTransform->SetPosition(pos);
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
	}
	void PlayerDustEffectScript::setAnimator()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimDashEffectKey) = std::bind(&PlayerDustEffectScript::DashStart, this);
		mpAnimator->GetCompleteEvent(mAnimDashEffectKey) = std::bind(&PlayerDustEffectScript::DashStart, this);
	}
}