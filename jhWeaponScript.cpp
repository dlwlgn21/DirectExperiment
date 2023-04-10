#include "jhWeaponScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhOnceAnimator.h"
#include "jhAnimation.h"
#include "jhPlayerScript.h"


namespace jh
{
	WeaponScript::WeaponScript(PlayerScript* pPlayerScript)
		: Script()
		, mpPlayerScript(pPlayerScript)
		, mpAnimator(nullptr)
		, mAnimTopDownSwingKey(L"SwingTopDown")
		, mePlayerLookDir()
		, meState(eWeaponState::WAITING)
	{
	}
	void WeaponScript::Initialize()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		assert(mpPlayerScript != nullptr);
		mpAnimator->GetStartEvent(mAnimTopDownSwingKey) = std::bind(&WeaponScript::Start, this);
		mpAnimator->GetCompleteEvent(mAnimTopDownSwingKey) = std::bind(&WeaponScript::Complete, this);
		mpAnimator->GetEndEvent(mAnimTopDownSwingKey) = std::bind(&WeaponScript::End, this);
	}
	void WeaponScript::Update()
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
					case eAnimatedObjectLookDirection::LEFT:
						mpAnimator->SetCurrAnimationHorizontalFlip(true);
						break;
					case eAnimatedObjectLookDirection::RIGHT:
						mpAnimator->SetCurrAnimationHorizontalFlip(false);
						break;
					default:
						assert(false);
						break;
					}
					mpAnimator->PlayAnimationWithReset(mAnimTopDownSwingKey, false);
				}
			}

		}
	}
	void WeaponScript::FixedUpdate()
	{
	}
	void WeaponScript::Render()
	{
	}
	void WeaponScript::Start()
	{
	}
	void WeaponScript::Complete()
	{
		meState = eWeaponState::WAITING;
		mpAnimator->SetComplete();
	}
	void WeaponScript::End()
	{
	}
}