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
#include "jhPlayerHitEffectScript.h"

static constexpr const float DASH_DISTANCE = 45.0f;
static constexpr const float DASH_INTERVAL_SECOND = 1.0f;

static constexpr const float ROLLING_DISTANCE = 8.0f;
static constexpr const float ROLLING_INTERVAL_SECOND = 1.0f;
static constexpr const UINT ROLLING_STAMINA_COST = 1;

static constexpr const float DEFAULT_MOVEMENT_DISTNANCE		= 5.0f;
static constexpr const float ATTACK_1_MOVEMENT_DISTANCE		= DEFAULT_MOVEMENT_DISTNANCE;
static constexpr const float ATTACK_2_MOVEMENT_DISTANCE		= DEFAULT_MOVEMENT_DISTNANCE * 2;
static constexpr const float ATTACK_3_MOVEMENT_DISTANCE		= DEFAULT_MOVEMENT_DISTNANCE * 3;
static constexpr const float PUSH_ATTACK_MOVEMENT_DISTANCE	= DEFAULT_MOVEMENT_DISTNANCE;

static constexpr const UINT PLAYER_VALIED_ATTACK_INDEX = 1;
static constexpr const UINT PLAYER_VALIED_DASH_INDEX = 0;

using namespace jh::math;

namespace jh
{
	PlayerScript::PlayerScript()
		: Script()
		, mpTranform(nullptr)
		, mSpeed(5.0f)
		, mAnimIdleKey(L"PlayerIdle")
		, mAnimMoveKey(L"PlayerMove")
		, mAnimNormalAttack1Key(L"PlayerNormalAttack1")
		, mAnimNormalAttack2Key(L"PlayerNormalAttack2")
		, mAnimNormalAttack3Key(L"PlayerNormalAttack3")
		, mAnimPushAttackKey(L"PlayerPushAttack")
		, mAnimDashKey(L"PlayerDash")
		, mAnimHittedKey(L"PlayerHitted")
		, mAnimRollingKey(L"PlayerRolling")
		, mpAnimator(nullptr)
		, meLookDir(eObjectLookDirection::RIGHT)
		, mStat(PlayerStat())
		, meState(ePlayerState::IDLE)
		, meAttackType(eAttackType::NORMAL)
		, meComboType(eComboAttackType::ONE)
		, mStaminaTimer(STAMINA_RECOVER_SECOND)
		, mpPlayerDustEffetScript(nullptr)
		, mpPlayerHitEffectScript(nullptr)
		, mbIsContiueAttacking(false)
		, mbIsHitPowerAttack(false)
		, mbIsStartCountingDashTimer(false)
		, mbIsStartCountingRollingTimer(false)
		, mDashIntervalTimer(DASH_INTERVAL_SECOND)
		, mDashIntervalTime(DASH_INTERVAL_SECOND)
		, mRollingIntervalTimer(ROLLING_INTERVAL_SECOND)
		, mRollingIntervalTime(ROLLING_INTERVAL_SECOND)
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
		float xPos = mpTranform->GetOnlyXPosition();
		if (meState == ePlayerState::ATTACKING)
		{
			setIsContinueAttacking();
			setXPosByComboAttackType(xPos);
		}
		else
		{
			setStateByInput(xPos);
		}
		processIfDash(xPos);
		processIfRolling(xPos);
		setAnimationFlip();
		setAnimatorByState();
		recoverStamina();
		mpTranform->SetOnlyXPosition(xPos);
	}

	void PlayerScript::FixedUpdate()
	{
	}
	void PlayerScript::Render()
	{
	}


#pragma region ANIMATION_EVENT
	void PlayerScript::IdleAnimStart()
	{
		mpAnimator->InitializeCurrAnimation();
	}

	void PlayerScript::AttackOneAnimationStart()
	{
		mpAnimator->InitializeCurrAnimation();
		mbIsContiueAttacking = false;
		decreaseStamina(ATTACK_STAMINA_COST);
	}

	void PlayerScript::AttackOneAnimationComplete()
	{
		if (mbIsContiueAttacking)
		{
			setComboType(eComboAttackType::TWO);
			setState(ePlayerState::ATTACKING);
		}
		else
		{
			setComboType(eComboAttackType::ONE);
			setState(ePlayerState::IDLE);
		}
	}

	void PlayerScript::AttackTwoAnimationStart()
	{
		mpAnimator->InitializeCurrAnimation();
		mbIsContiueAttacking = false;
	}

	void PlayerScript::AttackTwoAnimationComplete()
	{
		if (mbIsContiueAttacking)
		{
			setComboType(eComboAttackType::THREE);
			setState(ePlayerState::ATTACKING);
		}
		else
		{
			setComboType(eComboAttackType::ONE);
			setState(ePlayerState::IDLE);
		}
	}


	void PlayerScript::AttackThreeAnimationStart()
	{
		mpAnimator->InitializeCurrAnimation();
		mbIsContiueAttacking = false;
	}

	void PlayerScript::AttackThreeAnimationComplete()
	{
		setState(ePlayerState::IDLE);
		setComboType(eComboAttackType::ONE);
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

	void PlayerScript::RollingAnimationStart()
	{
	}

	void PlayerScript::RollingAnimationComplete()
	{
		setState(ePlayerState::IDLE);
	}
#pragma endregion

#pragma region COLLISION_TRIGGER
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
#pragma endregion

#pragma region SETTER
	void PlayerScript::setAnimationEvent()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);

		mpAnimator->GetStartEvent(mAnimIdleKey) = std::bind(&PlayerScript::IdleAnimStart, this);

		mpAnimator->GetStartEvent(mAnimNormalAttack1Key) = std::bind(&PlayerScript::AttackOneAnimationStart, this);
		mpAnimator->GetCompleteEvent(mAnimNormalAttack1Key) = std::bind(&PlayerScript::AttackOneAnimationComplete, this);

		mpAnimator->GetStartEvent(mAnimNormalAttack2Key) = std::bind(&PlayerScript::AttackTwoAnimationStart, this);
		mpAnimator->GetCompleteEvent(mAnimNormalAttack2Key) = std::bind(&PlayerScript::AttackTwoAnimationComplete, this);

		mpAnimator->GetStartEvent(mAnimNormalAttack3Key) = std::bind(&PlayerScript::AttackThreeAnimationStart, this);
		mpAnimator->GetCompleteEvent(mAnimNormalAttack3Key) = std::bind(&PlayerScript::AttackThreeAnimationComplete, this);


		mpAnimator->GetStartEvent(mAnimPushAttackKey) = std::bind(&PlayerScript::PushAttackAnimationStart, this);
		mpAnimator->GetCompleteEvent(mAnimPushAttackKey) = std::bind(&PlayerScript::PushAttackAnimationComplete, this);
		
		mpAnimator->GetStartEvent(mAnimDashKey) = std::bind(&PlayerScript::DashAnimationStart, this);
		mpAnimator->GetCompleteEvent(mAnimDashKey) = std::bind(&PlayerScript::DashAnimationComplete, this);

		mpAnimator->GetCompleteEvent(mAnimHittedKey) = std::bind(&PlayerScript::HitAnimationComplete, this);

		mpAnimator->GetStartEvent(mAnimRollingKey) = std::bind(&PlayerScript::RollingAnimationStart, this);
		mpAnimator->GetCompleteEvent(mAnimRollingKey) = std::bind(&PlayerScript::RollingAnimationComplete, this);
	}

	void PlayerScript::setStateByInput(float& xPos)
	{
		if (meState == ePlayerState::ATTACKING || meState == ePlayerState::HITTED || meState == ePlayerState::DASH || meState == ePlayerState::ROLLING)
		{
			return;
		}
		if (!Input::IsAnyKeyPressed())
		{
			setState(ePlayerState::IDLE);
		}

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			xPos += (mSpeed * Time::DeltaTime());
			setState(ePlayerState::MOVING);
			meLookDir = eObjectLookDirection::RIGHT;
		}
		else if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			xPos -= (mSpeed * Time::DeltaTime());
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
			if (mStat.CurrentStamina >= DASH_STAMINA_COST && !mbIsStartCountingDashTimer)
			{
				setState(ePlayerState::DASH);
				mbIsStartCountingDashTimer = true;
			}
		}
		else if (Input::GetKeyState(eKeyCode::V) == eKeyState::DOWN)
		{
			if (mStat.CurrentStamina >= ROLLING_STAMINA_COST && !mbIsStartCountingRollingTimer)
			{
				setState(ePlayerState::ROLLING);
				mbIsStartCountingRollingTimer = true;
			}
		}
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

	void PlayerScript::setComboType(const eComboAttackType eType)
	{
		meComboType = eType;
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
			{
				switch (meComboType)
				{
				case eComboAttackType::ONE:
					mpAnimator->PlayAnimation(mAnimNormalAttack1Key, true);
					break;
				case eComboAttackType::TWO:
					mpAnimator->PlayAnimation(mAnimNormalAttack2Key, true);
					break;
				case eComboAttackType::THREE:
					mpAnimator->PlayAnimation(mAnimNormalAttack3Key, true);
					break;
				default:
					assert(false);
					break;
				}
			}
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
		case ePlayerState::ROLLING:
		{
			mpAnimator->PlayAnimation(mAnimRollingKey, true);
			break;
		}
		case ePlayerState::HITTED:
			mpAnimator->PlayAnimation(mAnimHittedKey, true);
			assert(mpPlayerHitEffectScript != nullptr);
			mpPlayerHitEffectScript->SetStatePlaying();
			break;
		case ePlayerState::DEAD:
			break;
		default:
			assert(false);
			break;
		}
	}

	void PlayerScript::setIsContinueAttacking()
	{
		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::DOWN)
		{
			mbIsContiueAttacking = true;
		}
	}

	void PlayerScript::setXPosByComboAttackType(float& xPos)
	{
		switch (meComboType)
		{
		case eComboAttackType::ONE:
		{
			if (mpAnimator->GetCurrentAnimationIndex() == PLAYER_VALIED_ATTACK_INDEX)
			{
				setPosByLookDirection(xPos, ATTACK_1_MOVEMENT_DISTANCE);
			}
			break;
		}
		case eComboAttackType::TWO:
		{
			if (mpAnimator->GetCurrentAnimationIndex() == PLAYER_VALIED_ATTACK_INDEX)
			{
				setPosByLookDirection(xPos, ATTACK_2_MOVEMENT_DISTANCE);
			}
			break;
		}
		case eComboAttackType::THREE:
		{
			if (mpAnimator->GetCurrentAnimationIndex() == PLAYER_VALIED_ATTACK_INDEX)
			{
				setPosByLookDirection(xPos, ATTACK_3_MOVEMENT_DISTANCE);
			}
			break;
		}
		default:
			assert(false);
			break;
		}

		if (meAttackType == eAttackType::PUSH)
		{
			if (mpAnimator->GetCurrentAnimationIndex() == PLAYER_VALIED_ATTACK_INDEX)
			{
				setPosByLookDirection(xPos, PUSH_ATTACK_MOVEMENT_DISTANCE);
			}
		}

	}
	
	void PlayerScript::setPosByLookDirection(float& xPos, const float xDistance)
	{
		if (meLookDir == eObjectLookDirection::LEFT)
		{
			xPos -= xDistance * Time::DeltaTime();
		}
		else
		{
			xPos += xDistance * Time::DeltaTime();
		}
	}

#pragma endregion

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

	bool PlayerScript::checkIsNormalAttackKeyPressed()
	{
		if (Input::GetKeyState(eKeyCode::Z) == eKeyState::DOWN)
		{
			return true;
		}
		return false;
	}

	void PlayerScript::processIfDash(float& xPos)
	{
		if (mbIsStartCountingDashTimer)
		{
			mDashIntervalTimer -= Time::DeltaTime();
			if (meState == ePlayerState::DASH)
			{
				if (mpAnimator->GetCurrentAnimationIndex() == PLAYER_VALIED_DASH_INDEX)
				{
					if (meLookDir == eObjectLookDirection::LEFT)
					{
						xPos -= DASH_DISTANCE * Time::DeltaTime();
					}
					else
					{
						xPos += DASH_DISTANCE * Time::DeltaTime();
					}
				}
			}
			if (mDashIntervalTimer < 0.0f)
			{
				mDashIntervalTimer = mDashIntervalTime;
				mbIsStartCountingDashTimer = false;
			}
		}
	}

	void PlayerScript::processIfRolling(float& xPos)
	{
		if (mbIsStartCountingRollingTimer)
		{
			mRollingIntervalTimer -= Time::DeltaTime();
			if (meState == ePlayerState::ROLLING)
			{
				if (meLookDir == eObjectLookDirection::LEFT)
				{
					xPos -= ROLLING_DISTANCE * Time::DeltaTime();
				}
				else
				{
					xPos += ROLLING_DISTANCE * Time::DeltaTime();
				}
			}
			if (mRollingIntervalTimer < 0.0f)
			{
				mRollingIntervalTimer = mRollingIntervalTime;
				mbIsStartCountingRollingTimer = false;
			}
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