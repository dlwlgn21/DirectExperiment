#include "jhPlayerLevelUpEffectScript.h"
#include "jhOnceAnimator.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"
#include "jhPlayer.h"
#include "jhDebugHelper.h"
#include "jhLayerZValue.h"
#include "jhPlayerLevelManager.h"

using namespace jh::math;

namespace jh
{
	PlayerLevelUpEffectScript::PlayerLevelUpEffectScript(PlayerScript* pPlayerScript)
		: EffectScript()
		, mAnimKey(L"LevelUpKey")
		, mpPlayerScript(pPlayerScript)
		, mpPlayerTransform(pPlayerScript->GetOwner()->GetTransform())
	{
		assert(pPlayerScript != nullptr && mpPlayerTransform != nullptr);
	}
#pragma region INITIALIZE
	void PlayerLevelUpEffectScript::Initialize()
	{
		setAnimator();
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}

	void PlayerLevelUpEffectScript::setAnimator()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimKey) = std::bind(&PlayerLevelUpEffectScript::AnimStart, this);
		mpAnimator->GetCompleteEvent(mAnimKey) = std::bind(&PlayerLevelUpEffectScript::AninComplete, this);
	}
#pragma endregion


	void PlayerLevelUpEffectScript::Update()
	{
		if (isPlayingAnmation()) 
		{ 
			Vector2 pos = mpPlayerTransform->GetOnlyXYPosition();
			mpTransform->SetOnlyXYPosition(pos);
			return; 
		}
		switch (meState)
		{
		case eEffectState::WAIT:
		{
			break;
		}
		case eEffectState::PLAYING:
		{
			playAnimation();
			break;
		}
		default:
			assert(false);
			break;
		}
	}


	void PlayerLevelUpEffectScript::playAnimation()
	{
		mpAnimator->SetActive(true);
		mpAnimator->SetPlaying(true);
		mpAnimator->PlayAnimationWithReset(mAnimKey, false);
	}

	void PlayerLevelUpEffectScript::AnimStart()
	{

	}
	void PlayerLevelUpEffectScript::AninComplete()
	{
		mpAnimator->SetComplete();
		SetState(eEffectState::WAIT);
		PlayerLevelManager::GetInstance().OnPlayerLevelUP();
	}
}