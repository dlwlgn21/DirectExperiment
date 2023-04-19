#define _CRT_SECURE_NO_WARNINGS

#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"
#include "jhAnimation.h"
#include "jhCollider2D.h"

using namespace jh::math;

namespace jh
{
	PlayerScript::PlayerScript()
		: Script()
		, mpTranform(nullptr)
		, mSpeed(2.0f)
		, mAnimIdleKey(L"PlayerIdle")
		, mAnimMoveKey(L"PlayerMove")
		, mAnimAttackKey(L"PlayerWeaponSwing")
		, mAnimDashKey(L"PlayerDash")
		, mAnimHittedKey(L"PlayerHitted")
		, mpAnimator(nullptr)
		, meLookDir(eObjectLookDirection::RIGHT)
		, mStat(PlayerStat())
		, meState(ePlayerState::IDLE)
	{
	}

	void PlayerScript::Initialize()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimMoveKey) = std::bind(&PlayerScript::Start, this);
		mpAnimator->GetCompleteEvent(mAnimMoveKey) = std::bind(&PlayerScript::Complete, this);
		mpAnimator->GetEndEvent(mAnimMoveKey) = std::bind(&PlayerScript::End, this);

		mpAnimator->GetCompleteEvent(mAnimAttackKey) = std::bind(&PlayerScript::AttackAnimationComplete, this);
		mpAnimator->GetCompleteEvent(mAnimDashKey) = std::bind(&PlayerScript::DashAnimationComplete, this);
		mpAnimator->GetCompleteEvent(mAnimHittedKey) = std::bind(&PlayerScript::HitAnimationComplete, this);

		mpTranform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));

	}
	void PlayerScript::Update()
	{
		assert(mpTranform != nullptr);
		Vector3 pos = mpTranform->GetPosition();
		setStateByInput(pos);
		setAnimationFlip();

		switch (meState)
		{
		case ePlayerState::IDLE:
			mpAnimator->PlayAnimation(mAnimIdleKey, true);
			break;
		case ePlayerState::MOVING:
			mpAnimator->PlayAnimation(mAnimMoveKey, true);
			break;
		case ePlayerState::ATTACKING:
			mpAnimator->PlayAnimation(mAnimAttackKey, true);
			break;
		case ePlayerState::DASH:
			mpAnimator->PlayAnimation(mAnimDashKey, true);
			break;
		case ePlayerState::HITTED:
			mpAnimator->PlayAnimation(mAnimHittedKey, true);
			break;
		case ePlayerState::DEAD:
			break;
		default:
			assert(false);
			break;
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


	void PlayerScript::AttackAnimationComplete()
	{
		setState(ePlayerState::IDLE);
	}

	void PlayerScript::DashAnimationComplete()
	{
		setState(ePlayerState::IDLE);
	}

	void PlayerScript::HitAnimationComplete()
	{
		setState(ePlayerState::IDLE);
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
		if (pOtherCollider->GetOwner()->GetLayer() == eLayerType::MONSTER)
		{
			setState(ePlayerState::HITTED);
		}
	}

	void PlayerScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
	}

	void PlayerScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}

	void PlayerScript::setState(const ePlayerState eState)
	{
		assert(eState != ePlayerState::COUNT);
		meState = eState;
	}

	void PlayerScript::setStateByInput(Vector3& pos)
	{
		if (meState == ePlayerState::ATTACKING || meState == ePlayerState::HITTED || meState == ePlayerState::DASH)	{return;}
		if (!Input::IsAnyKeyPressed())			{ setState(ePlayerState::IDLE); }

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += (mSpeed * Time::DeltaTime());
			setState(ePlayerState::MOVING);
			meLookDir = eObjectLookDirection::RIGHT;
		}
		else if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x -= (mSpeed * Time::DeltaTime());
			setState(ePlayerState::MOVING);
			meLookDir = eObjectLookDirection::LEFT;
		}

		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::PRESSED)
		{
			setState(ePlayerState::ATTACKING);
		}
		else if (Input::GetKeyState(eKeyCode::X) == eKeyState::PRESSED)
		{
			setState(ePlayerState::DASH);
			const float DASH_AMOUNT = 2.0f;
			if (meLookDir == eObjectLookDirection::LEFT)
			{
				pos.x -= (mSpeed * DASH_AMOUNT);
			}
			else
			{
				pos.x += (mSpeed * DASH_AMOUNT);
			}
		}
	}

	void PlayerScript::setAnimationFlip()
	{
		assert(mpAnimator != nullptr);
		if (meLookDir == eObjectLookDirection::RIGHT)
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(false);
		}
		else
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(true);
		}

	}

}