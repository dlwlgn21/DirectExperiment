#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"
#include "jhAnimation.h"

using namespace jh::math;

namespace jh
{
	PlayerScript::PlayerScript()
		: Script()
		, mpTranform(nullptr)
		, mSpeed(3.0f)
		, mAnimIdleKey(L"PlayerIdle")
		, mAnimMoveKey(L"PlayerMove")
		, mAnimWeaponSwingKey(L"PlayerWeaponSwing")
		, mpAnimator(nullptr)
		, mbIsMoving(false)
		, mbIsAttacking(false)
		, meLookDir(eAnimatedObjectLookDirection::RIGHT)
	{
	}

	void PlayerScript::Initialize()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimMoveKey) = std::bind(&PlayerScript::Start, this);
		mpAnimator->GetCompleteEvent(mAnimMoveKey) = std::bind(&PlayerScript::Complete, this);
		mpAnimator->GetEndEvent(mAnimMoveKey) = std::bind(&PlayerScript::End, this);
	}
	void PlayerScript::Update()
	{
		mpTranform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(mpTranform != nullptr);
		Vector3 pos = mpTranform->GetPosition();
		if (mbIsAttacking)
		{
			if (mpAnimator->GetCurrentAnimatingAnimation()->IsAnimComplete())
			{
				mbIsAttacking = false;
			}
			goto PROCESSING_INPUT;
		}

		if (!Input::IsAnyKeyPressed())
		{
			mpAnimator->PlayAnimation(mAnimIdleKey, true);
			mbIsMoving = false;
		}


PROCESSING_INPUT:
		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			pos.y += mSpeed * Time::DeltaTime();
			mbIsMoving = true;
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos.y -= mSpeed * Time::DeltaTime();
			mbIsMoving = true;
		}
		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += mSpeed * Time::DeltaTime();
			meLookDir = eAnimatedObjectLookDirection::RIGHT;
			mbIsMoving = true;
		}
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x -= mSpeed * Time::DeltaTime();
			mbIsMoving = true;
			meLookDir = eAnimatedObjectLookDirection::LEFT;
		}

		assert(mpAnimator != nullptr);
		if (meLookDir == eAnimatedObjectLookDirection::RIGHT)
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(false);
		}
		else
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(true);
		}

		if (mbIsMoving && !mbIsAttacking)
		{
			mpAnimator->PlayAnimation(mAnimMoveKey, true);
		}

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::PRESSED)
		{
			pos.z -= mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::O) == eKeyState::PRESSED)
		{
			pos.z += mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::PRESSED)
		{
			mpAnimator->PlayAnimation(mAnimWeaponSwingKey, true);
			mbIsAttacking = true;
		}
		//else if (Input::GetKeyState(eKeyCode::X) == eKeyState::PRESSED)
		//{
		//	mpAnimator->PlayAnimation(mAnimRightPunchKey, true);
		//	mbIsAttacking = true;
		//}
		mpTranform->SetPosition(pos);
	}

	void PlayerScript::FixedUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}

	void PlayerScript::Start()
	{
	}

	void PlayerScript::Complete()
	{
	}

	void PlayerScript::End()
	{
	}

}