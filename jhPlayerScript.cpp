#define _CRT_SECURE_NO_WARNINGS

#include "jhPlayerScript.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhAnimator.h"
#include "jhAnimation.h"
#include "jhCollider2D.h"
#include "jhDebugHelper.h"
#include "jhPlayerDustEffectScript.h"

static constexpr const float DASH_AMOUNT = 3.0f;
using namespace jh::math;

namespace jh
{
	PlayerScript::PlayerScript()
		: Script()
		, mpTranform(nullptr)
		, mSpeed(3.0f)
		, mAnimIdleKey(L"PlayerIdle")
		, mAnimMoveKey(L"PlayerMove")
		, mAnimAttackKey(L"PlayerWeaponSwing")
		, mAnimPushAttackKey(L"PlayerPushAttack")
		, mAnimDashKey(L"PlayerDash")
		, mAnimHittedKey(L"PlayerHitted")
		, mpAnimator(nullptr)
		, meLookDir(eObjectLookDirection::RIGHT)
		, mStat(PlayerStat())
		, meState(ePlayerState::IDLE)
		, meAttackType(eAttackType::NORMAL)
		, mStaminaTimer(STAMINA_RECOVER_SECOND)
		, mpPlayerDustEffetScript(nullptr)
	{
	}

	void PlayerScript::Initialize()
	{
		setAnimationEvent();
		mpTranform = GetOwner()->GetTransform();

	}
	void PlayerScript::Update()
	{
		assert(mpTranform != nullptr);
		Vector3 pos = mpTranform->GetPosition();
		setStateByInput(pos);
		setAnimationFlip();
		setAnimatorByState();
		recoverStamina();
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


	void PlayerScript::AttackAnimationStart()
	{
		decreaseStamina(ATTACK_STAMINA_COST);
	}

	void PlayerScript::AttackAnimationComplete()
	{
		setState(ePlayerState::IDLE);
	}

	void PlayerScript::PushAttackAnimationStart()
	{
		decreaseStamina(ATTACK_STAMINA_COST);
	}

	void PlayerScript::PushAttackAnimationComplete()
	{
		setState(ePlayerState::IDLE);
	}

	void PlayerScript::DashAnimationStart()
	{
		decreaseStamina(DASH_STAMINA_COST);
	}

	void PlayerScript::DashAnimationComplete()
	{
		setState(ePlayerState::IDLE);
	}

	void PlayerScript::HitAnimationComplete()
	{
		setState(ePlayerState::IDLE);
	}

	void PlayerScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::MONSTER_WEAPON)
		{
			return;
		}
		//if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::MONSTER)
		//{
		//	setState(ePlayerState::HITTED);
		//	decreaseHP(1);
		//}
	}

	void PlayerScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
	}

	void PlayerScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}

	void PlayerScript::setAnimationEvent()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimMoveKey) = std::bind(&PlayerScript::Start, this);
		mpAnimator->GetCompleteEvent(mAnimMoveKey) = std::bind(&PlayerScript::Complete, this);
		mpAnimator->GetEndEvent(mAnimMoveKey) = std::bind(&PlayerScript::End, this);

		mpAnimator->GetStartEvent(mAnimAttackKey) = std::bind(&PlayerScript::AttackAnimationStart, this);
		mpAnimator->GetCompleteEvent(mAnimAttackKey) = std::bind(&PlayerScript::AttackAnimationComplete, this);


		mpAnimator->GetStartEvent(mAnimPushAttackKey) = std::bind(&PlayerScript::PushAttackAnimationStart, this);
		mpAnimator->GetCompleteEvent(mAnimPushAttackKey) = std::bind(&PlayerScript::PushAttackAnimationComplete, this);
		
		mpAnimator->GetStartEvent(mAnimDashKey) = std::bind(&PlayerScript::DashAnimationStart, this);
		mpAnimator->GetCompleteEvent(mAnimDashKey) = std::bind(&PlayerScript::DashAnimationComplete, this);
		mpAnimator->GetCompleteEvent(mAnimHittedKey) = std::bind(&PlayerScript::HitAnimationComplete, this);
	}

	void PlayerScript::setState(const ePlayerState eState)
	{
		assert(eState != ePlayerState::COUNT);
		meState = eState;
	}

	void PlayerScript::setAttackType(const eAttackType eType)
	{
		meAttackType = eType;
	}

	void PlayerScript::setStateByInput(Vector3& pos)
	{
		if (meState == ePlayerState::ATTACKING || meState == ePlayerState::HITTED || meState == ePlayerState::DASH)	
			{return;}
		if (!Input::IsAnyKeyPressed())			
			{ setState(ePlayerState::IDLE); }

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

		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::DOWN)
		{
			if (mStat.CurrentStamina >= ATTACK_STAMINA_COST)
			{
				setState(ePlayerState::ATTACKING);
				setAttackType(eAttackType::NORMAL);
			}
		}
		else if (Input::GetKeyState(eKeyCode::X) == eKeyState::DOWN)
		{
			if (mStat.CurrentStamina >= ATTACK_STAMINA_COST)
			{
				setState(ePlayerState::ATTACKING);
				setAttackType(eAttackType::PUSH);
			}
		}
		else if (Input::GetKeyState(eKeyCode::C) == eKeyState::DOWN)
		{
			if (mStat.CurrentStamina >= DASH_STAMINA_COST)
			{
				setState(ePlayerState::DASH);
				if (meLookDir == eObjectLookDirection::LEFT)
				{
					pos.x -= (DASH_AMOUNT);
				}
				else
				{
					pos.x += (DASH_AMOUNT);
				}
			}
		}
	}

	void PlayerScript::setAnimationFlip()
	{
		assert(mpAnimator != nullptr);
		if (meLookDir == eObjectLookDirection::RIGHT)
			{mpAnimator->SetCurrAnimationHorizontalFlip(false);}
		else
			{mpAnimator->SetCurrAnimationHorizontalFlip(true);}

	}

	void PlayerScript::setAnimatorByState()
	{
		switch (meState)
		{
		case ePlayerState::IDLE:
			mpAnimator->PlayAnimation(mAnimIdleKey, true);
			break;
		case ePlayerState::MOVING:
			mpAnimator->PlayAnimation(mAnimMoveKey, true);
			break;
		case ePlayerState::ATTACKING:
			switch (meAttackType)
			{
			case eAttackType::NORMAL:
				mpAnimator->PlayAnimation(mAnimAttackKey, true);
				break;
			case eAttackType::PUSH:
				mpAnimator->PlayAnimation(mAnimPushAttackKey, true);
				break;
			default:
				break;
			}
			break;
		case ePlayerState::DASH:
		{
			mpAnimator->PlayAnimation(mAnimDashKey, true);
			assert(mpPlayerDustEffetScript != nullptr);
			mpPlayerDustEffetScript->SetStatePlaying();
			break;
		}
		case ePlayerState::HITTED:
			mpAnimator->PlayAnimation(mAnimHittedKey, true);
			break;
		case ePlayerState::DEAD:
			break;
		default:
			assert(false);
			break;
		}
	}

	void PlayerScript::recoverStamina()
	{
		mStaminaTimer -= Time::DeltaTime();
		if (mStaminaTimer <= 0.0f)
		{
			mStaminaTimer = STAMINA_RECOVER_SECOND;
			if (mStat.CurrentStamina >= mStat.MaxStamina)	{return;}
			mStat.CurrentStamina += STAMINA_RECOVER_AMOUNT;
		}
	}

	void PlayerScript::decreaseStamina(CHAR amount)
	{
		mStat.CurrentStamina -= std::abs(amount);
	}

	void PlayerScript::decreaseHP(CHAR amount)
	{
		mStat.CurrentHP -= std::abs(amount);
		if (mStat.CurrentHP <= 0)
		{
			mStat.CurrentHP = 0;
		}
	}

	void PlayerScript::EnemyAttackHiited(UINT damage)
	{
		if (meState == ePlayerState::HITTED)
		{
			return;
		}
		setState(ePlayerState::HITTED);
		decreaseHP(damage);
	}
}