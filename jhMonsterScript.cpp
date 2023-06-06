#include "jhMonsterScript.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhMonster.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhHitEffectScript.h"
#include "jhCollider2D.h"
#include "jhPlayerScript.h"

using namespace jh::math;
static constexpr const float ATTACK_RANGE_DISTANCE = 2.0f;
static constexpr const UINT PLAYER_VAILED_ATTACK_ANIMATION_INDEX = 1;

static constexpr const int CAGED_SHOKER_INITIAL_HP = 10;
static constexpr const float CAGED_SHOKER_INITIAL_SPEED = 1.5f;

static constexpr const int SWEEPER_INITIAL_HP = 5;
static constexpr const float SWEEPER_INITIAL_SPEED = 2.0f;

static constexpr const int WARDEN_INITIAL_HP = 3;
static constexpr const float WARDEN_INITIAL_SPEED = 3.0f;

static constexpr const int ZOMBIE_INITIAL_HP = 7;
static constexpr const float ZOMBIE_INITIAL_SPEED = 1.0f;

static constexpr const int HEABY_SLICER_INITIAL_HP = 12;
static constexpr const float HEABY_SLICER_INITIAL_SPEED = 1.5f;

static constexpr const int LIGHT_SLICER_INITIAL_HP = 6;
static constexpr const float LIGHT_SLICER_INITIAL_SPEED = 2.0f;

static constexpr const float SPAWNING_TIME = 3.0f;

namespace jh
{
	MonsterScript::MonsterScript(eMonsterType eMonsterType, PlayerScript* pPlayerScript)
		: Script()
		, mpTranform(nullptr)
		, mpPlayerTransform(nullptr)
		, mpAnimator(nullptr)
		, mpEffectScript(nullptr)
		, mpPlayerScript(pPlayerScript)
		, mMaxHP(0)
		, mCurrHP(0)
		, mSpeed(0.0f)
		, mSpawningTimer(SPAWNING_TIME)
		, mHittedPushDistance(2.0f)
		, meLookDir(eObjectLookDirection::LEFT)
		, meState(eMonsterState::SPAWNING)
		, meMonsterType(eMonsterType)
		
	{
		switch (meMonsterType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			setAnimKey(
				MonsterManager::CAGED_SHOKER_IDLE_ANIM_KEY, 
				MonsterManager::CAGED_SHOKER_MOVING_ANIM_KEY,
				MonsterManager::CAGED_SHOKER_ATTACK_ANIM_KEY,
				MonsterManager::CAGED_SHOKER_HITTED_ANIM_KEY,
				MonsterManager::CAGED_SHOKER_DIE_ANIM_KEY
			);
			setInitialStat(CAGED_SHOKER_INITIAL_HP, CAGED_SHOKER_INITIAL_SPEED);
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			setAnimKey(
				MonsterManager::SWEEPER_IDLE_ANIM_KEY,
				MonsterManager::SWEEPER_MOVING_ANIM_KEY,
				MonsterManager::SWEEPER_ATTACK_ANIM_KEY,
				MonsterManager::SWEEPER_HITTED_ANIM_KEY,
				MonsterManager::SWEEPER_DIE_ANIM_KEY
			);
			setInitialStat(SWEEPER_INITIAL_HP, SWEEPER_INITIAL_SPEED);
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			setAnimKey(
				MonsterManager::WARDEN_IDLE_ANIM_KEY,
				MonsterManager::WARDEN_MOVING_ANIM_KEY,
				MonsterManager::WARDEN_ATTACK_ANIM_KEY,
				MonsterManager::WARDEN_HITTED_ANIM_KEY,
				MonsterManager::WARDEN_DIE_ANIM_KEY
			);
			setInitialStat(WARDEN_INITIAL_HP, WARDEN_INITIAL_SPEED);
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			setAnimKey(
				MonsterManager::ZOMBIE_IDLE_ANIM_KEY,
				MonsterManager::ZOMBIE_MOVING_ANIM_KEY,
				MonsterManager::ZOMBIE_ATTACK_ANIM_KEY,
				MonsterManager::ZOMBIE_HITTED_ANIM_KEY,
				MonsterManager::ZOMBIE_DIE_ANIM_KEY
			);
			setInitialStat(ZOMBIE_INITIAL_HP, ZOMBIE_INITIAL_SPEED);
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			setAnimKey(
				MonsterManager::HEABY_SLICER_IDLE_ANIM_KEY,
				MonsterManager::HEABY_SLICER_MOVING_ANIM_KEY,
				MonsterManager::HEABY_SLICER_ATTACK_ANIM_KEY,
				MonsterManager::HEABY_SLICER_HITTED_ANIM_KEY,
				MonsterManager::HEABY_SLICER_DIE_ANIM_KEY
			);
			setInitialStat(HEABY_SLICER_INITIAL_HP, HEABY_SLICER_INITIAL_SPEED);
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			setAnimKey(
				MonsterManager::LIGHT_SLICER_IDLE_ANIM_KEY,
				MonsterManager::LIGHT_SLICER_MOVING_ANIM_KEY,
				MonsterManager::LIGHT_SLICER_ATTACK_ANIM_KEY,
				MonsterManager::LIGHT_SLICER_HITTED_ANIM_KEY,
				MonsterManager::LIGHT_SLICER_DIE_ANIM_KEY
			);
			setInitialStat(LIGHT_SLICER_INITIAL_HP, LIGHT_SLICER_INITIAL_SPEED);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void MonsterScript::Initialize()
	{
		setAnimator();
		mpTranform = GetOwner()->GetTransform();
		assert(mpTranform != nullptr);
		assert(mpPlayerScript != nullptr);
		mpPlayerTransform = mpPlayerScript->GetOwner()->GetTransform();
		calculateDistanceFromPlayerToSetLookDirection();
	}

	void MonsterScript::Update()
	{
		if (meState == eMonsterState::SPAWNING)
		{
			setAnimationFlip();
			playAnimation();
			mSpawningTimer -= Time::DeltaTime();
			if (mSpawningTimer <= 0.0f)
			{
				setState(eMonsterState::TRACING);
			}
			return;
		}
		setPosition();
		setAnimationFlip();
		playAnimation();
	}

	void MonsterScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{
		if (meState == eMonsterState::HITTED || meState == eMonsterState::DEAD)
		{
			return;
		}
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER)
		{
			setState(eMonsterState::ATTACKING);
			return;
		}

	}
	void MonsterScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
		if (meState == eMonsterState::HITTED || meState == eMonsterState::DEAD)
		{
			return;
		}
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER_WEAPON)
		{
			Animator* pPlayerAnimator = static_cast<Animator*>(mpPlayerScript->GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
			assert(pPlayerAnimator != nullptr);
			if (pPlayerAnimator->GetCurrentAnimationIndex() == PLAYER_VAILED_ATTACK_ANIMATION_INDEX)
			{
				decreaseHP(mpPlayerScript->GetPlayerStat().AttackDamage);
				if (mpPlayerScript->GetComboAttackType() == eComboAttackType::THREE)
				{
					mpPlayerScript->SetIsHitPowerAttack(true);
				}
				if (meState != eMonsterState::DEAD)
				{
					setState(eMonsterState::HITTED);
				}
			}
		}
	}
	void MonsterScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
	void MonsterScript::AnimationAttackStart()
	{
		mpAnimator->InitializeCurrAnimation();
	}
	void MonsterScript::AnimationAttackComplete()
	{
		setState(eMonsterState::TRACING);
	}

	void MonsterScript::AnimationHittedStart()
	{
		mpAnimator->InitializeCurrAnimation();
	}
	void MonsterScript::AnimationHittedComplete()
	{
		setState(eMonsterState::TRACING);
	}

	void MonsterScript::AnimationDieStart()
	{
		mpAnimator->InitializeCurrAnimation();
	}

	void MonsterScript::AnimationDieComplete()
	{
		static_cast<Monster*>(GetOwner())->SetInactive();
	}

	void MonsterScript::SetRespawnState()
	{
		switch (meMonsterType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			setInitialStat(CAGED_SHOKER_INITIAL_HP, CAGED_SHOKER_INITIAL_SPEED);
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			setInitialStat(SWEEPER_INITIAL_HP, SWEEPER_INITIAL_SPEED);
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			setInitialStat(WARDEN_INITIAL_HP, WARDEN_INITIAL_SPEED);
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			setInitialStat(ZOMBIE_INITIAL_HP, ZOMBIE_INITIAL_SPEED);
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			setInitialStat(HEABY_SLICER_INITIAL_HP, HEABY_SLICER_INITIAL_SPEED);
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			setInitialStat(LIGHT_SLICER_INITIAL_HP, LIGHT_SLICER_INITIAL_SPEED);
			break;
		}
		default:
			assert(false);
			break;
		}
		calculateDistanceFromPlayerToSetLookDirection();
		setState(eMonsterState::SPAWNING);
		mSpawningTimer = SPAWNING_TIME;
	}

	void MonsterScript::setAnimKey(const std::wstring& idleKey, const std::wstring& movingkey, const std::wstring& attackKey, const std::wstring& hittedKey, const std::wstring& dieKey)
	{
		mAnimIdleKey = idleKey;
		mAnimMoveKey = movingkey;
		mAnimAttackKey = attackKey;
		mAnimHittedKey = hittedKey;
		mAnimDieKey = dieKey;
	}

	void MonsterScript::setAnimator()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimAttackKey) = std::bind(&MonsterScript::AnimationAttackStart, this);
		mpAnimator->GetCompleteEvent(mAnimAttackKey) = std::bind(&MonsterScript::AnimationAttackComplete, this);

		mpAnimator->GetStartEvent(mAnimHittedKey) = std::bind(&MonsterScript::AnimationHittedStart, this);
		mpAnimator->GetCompleteEvent(mAnimHittedKey) = std::bind(&MonsterScript::AnimationHittedComplete, this);

		mpAnimator->GetStartEvent(mAnimDieKey) = std::bind(&MonsterScript::AnimationDieStart, this);
		mpAnimator->GetCompleteEvent(mAnimDieKey) = std::bind(&MonsterScript::AnimationDieComplete, this);
	}

	void MonsterScript::setPosition()
	{
		switch (meState)
		{
		case eMonsterState::TRACING:
		{
			moveOrChangeState();
			return;
		}
		case eMonsterState::ATTACKING:
			return;
		case eMonsterState::HITTED:
		{
			if (mpPlayerScript->GetAttackType() == eAttackType::PUSH)
			{
				Vector3 monCurrPos = mpTranform->GetPosition();
				if (meLookDir == eObjectLookDirection::LEFT)
				{
					mpTranform->SetPosition(Vector3(monCurrPos.x + mHittedPushDistance * Time::DeltaTime(), monCurrPos.y, monCurrPos.z));
				}
				else
				{
					mpTranform->SetPosition(Vector3(monCurrPos.x - mHittedPushDistance * Time::DeltaTime(), monCurrPos.y, monCurrPos.z));
				}
			}
			return;
			break;
		}
		case eMonsterState::DEAD:
			break;
		default:
			break;
		}
	}


	void MonsterScript::moveOrChangeState()
	{
		assert(mpTranform != nullptr);
		Vector3 monCurrPos = mpTranform->GetPosition();
		Vector3 dir = mpPlayerTransform->GetPosition() - monCurrPos;
		Vector3 lookDirVector(dir);
		setLookDir(lookDirVector);

		if (isDistanceCloseToPlayer(lookDirVector))
		{
			setState(eMonsterState::ATTACKING);
			return;
		}


		dir.Normalize();
		Vector3 moveVector = monCurrPos;
		moveVector += dir * mSpeed * Time::DeltaTime();
		mpTranform->SetPosition(Vector3(moveVector.x, monCurrPos.y, monCurrPos.z));
	}

	void MonsterScript::setLookDir(const jh::math::Vector3& lookDirVector)
	{
		if (lookDirVector.x < 0.0f)
		{
			meLookDir = eObjectLookDirection::LEFT;
		}
		else
		{
			meLookDir = eObjectLookDirection::RIGHT;
		}
	}

	bool MonsterScript::isDistanceCloseToPlayer(const Vector3& lookDirVector)
	{
		if (std::abs(lookDirVector.x) <= ATTACK_RANGE_DISTANCE)
		{
			setLookDir(lookDirVector);
			return true;
		}
		return false;
	}

	void MonsterScript::setAnimationFlip()
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
	void MonsterScript::playAnimation()
	{
		switch (meState)
		{
		case eMonsterState::SPAWNING:
		{
			mpAnimator->PlayAnimation(mAnimIdleKey, true);
			break;
		}
		case eMonsterState::TRACING:
		{
			mpAnimator->PlayAnimation(mAnimMoveKey, true);
			break;
		}
		case eMonsterState::ATTACKING:
		{
			mpAnimator->PlayAnimation(mAnimAttackKey, true);
			break;
		}
		case eMonsterState::HITTED:
		{
			mpAnimator->PlayAnimation(mAnimHittedKey, true);
			playHitEffectAnimation();
			break;
		}
		case eMonsterState::DEAD:
		{
			mpAnimator->PlayAnimation(mAnimDieKey, true);
			playHitEffectAnimation();
			break;
		}
		default:
			break;
		}
	}

	void MonsterScript::playHitEffectAnimation()
	{
		if (mpPlayerScript->GetAttackType() == eAttackType::NORMAL)
		{
			assert(mpEffectScript != nullptr);
			mpEffectScript->SetStatePlaying();
		}
	}

	void MonsterScript::calculateDistanceFromPlayerToSetLookDirection()
	{
		Vector3 monCurrPos = mpTranform->GetPosition();
		Vector3 dir = mpPlayerTransform->GetPosition() - monCurrPos;
		Vector3 lookDirVector(dir);
		setLookDir(lookDirVector);
	}
	void MonsterScript::decreaseHP(const int amount)
	{
		if (meState == eMonsterState::HITTED)
		{
			return;
		}
		mCurrHP -= std::abs(amount);
		if (mCurrHP <= 0)
		{
			mCurrHP = 0;
			setState(eMonsterState::DEAD);
		}
	}
}