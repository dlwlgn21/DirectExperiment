#define _CRT_SECURE_NO_WARNINGS

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
		, mSpeed(1.0f)
		, mAnimIdleKey(L"PlayerIdle")
		, mAnimMoveKey(L"PlayerMove")
		, mAnimWeaponSwingKey(L"PlayerWeaponSwing")
		, mAnimHittedKey(L"PlayerHitted")
		, mpAnimator(nullptr)
		, mbIsMoving(false)
		, mbIsAttacking(false)
		, meLookDir(eObjectLookDirection::RIGHT)
		, mStat(PlayerStat())
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
		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += mSpeed * Time::DeltaTime();
			meLookDir = eObjectLookDirection::RIGHT;
			mbIsMoving = true;
		}
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x -= mSpeed * Time::DeltaTime();
			mbIsMoving = true;
			meLookDir = eObjectLookDirection::LEFT;
		}

		assert(mpAnimator != nullptr);
		if (meLookDir == eObjectLookDirection::RIGHT)
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

	void PlayerScript::OnCollisionEnter(Collider2D* pOtherCollider)
	{
	}

	void PlayerScript::OnCollisionStay(Collider2D* pOtherCollider)
	{
	}

	void PlayerScript::OnCollisionExit(Collider2D* pOtherCollider)
	{
	}

	void PlayerScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{
		char buffer[64];
		ZeroMemory(buffer, 64);
		sprintf(buffer, "%d\n", mStat.HP);
		OutputDebugStringA(buffer);
	}

	void PlayerScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
	}

	void PlayerScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}

}