#include "jhEffectScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhOnceAnimator.h"
#include "jhAnimation.h"
#include "jhPlayerScript.h"


namespace jh
{
	EffectScript::EffectScript(PlayerScript* pPlayerScript)
		: Script()
		, mpPlayerScript(pPlayerScript)
		, mpAnimator(nullptr)
		, mAinmSwingEffectKey(L"SwordSwingEffect")
		, mePlayerLookDir()
		, meState(eWeaponState::WAITING)
	{
	}
	void EffectScript::Initialize()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		assert(mpPlayerScript != nullptr);
		mpAnimator->GetStartEvent(mAinmSwingEffectKey) = std::bind(&EffectScript::Start, this);
		mpAnimator->GetCompleteEvent(mAinmSwingEffectKey) = std::bind(&EffectScript::Complete, this);
		mpAnimator->GetEndEvent(mAinmSwingEffectKey) = std::bind(&EffectScript::End, this);
	}
	void EffectScript::Update()
	{
		if (mpPlayerScript != nullptr)
		{
			if (meState == eWeaponState::WAITING)
			{
				mePlayerLookDir = mpPlayerScript->GetPlayerLookDirection();
				if (Input::GetKeyState(eKeyCode::Z) == eKeyState::PRESSED)
				{
					mpAnimator->SetActive(true);
					mpAnimator->SetPlaying(true);
					meState = eWeaponState::ATTACKING;
					switch (mePlayerLookDir)
					{
					case eObjectLookDirection::LEFT:
						mpAnimator->SetCurrAnimationHorizontalFlip(true);
						break;
					case eObjectLookDirection::RIGHT:
						mpAnimator->SetCurrAnimationHorizontalFlip(false);
						break;
					default:
						//assert(false);
						break;
					}
					mpAnimator->PlayAnimationWithReset(mAinmSwingEffectKey, false);
				}
			}
		}
	}
	void EffectScript::FixedUpdate()
	{
	}

	void EffectScript::Render()
	{
	}

	void EffectScript::PlayAnimation()
	{
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