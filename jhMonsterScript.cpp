#include "jhMonsterScript.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhMonster.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhHitEffectScript.h"
#include "jhCollider2D.h"
#include "jhPlayerScript.h"
#include "jhMonsterAnimIndexInformation.h"
#include "jhPlayerSkillElectricBeamScript.h"
#include "jhSFXManager.h"


#include "jhMonsterAnimIndexInformation.h"


using namespace jh::math;

static constexpr const UINT PLAYER_VAILED_ATTACK_ANIMATION_INDEX = 1;
static constexpr const float SPAWNING_TIME = 3.0f;
static constexpr const float HIT_PUSH_ATTACK_DISTANCE = 15.0f;

static constexpr const float ATTACK_SFX_INTERVAL_TIME = 0.1f;

#pragma region MONSTERS_AWARENESS_RANGE
static constexpr const float ATTACKING_AWARENESS_DEFAULT_RANGE = 2.0f;

static constexpr const float CAGED_SHOCKER_AWARENESS_RANGE	= ATTACKING_AWARENESS_DEFAULT_RANGE + 1.5f;
static constexpr const float SWEEPER_AWARENESS_RANGE		= ATTACKING_AWARENESS_DEFAULT_RANGE + 1.0f;
static constexpr const float WARDEN_AWARENESS_RANGE			= ATTACKING_AWARENESS_DEFAULT_RANGE + 0.5f;
static constexpr const float HEABY_SLICER_AWARENESS_RANGE	= ATTACKING_AWARENESS_DEFAULT_RANGE + 1.0f;
static constexpr const float LIGHT_SLICER_AWARENESS_RANGE	= ATTACKING_AWARENESS_DEFAULT_RANGE + 1.0f;
static constexpr const float ZOMBIE_AWARENESS_RANGE			= ATTACKING_AWARENESS_DEFAULT_RANGE - 0.5f;
static constexpr const float ARCHER_AWARENESS_RANGE			= ATTACKING_AWARENESS_DEFAULT_RANGE + 2.0f;
static constexpr const float DAGGER_AWARENESS_RANGE			= ATTACKING_AWARENESS_DEFAULT_RANGE + 1.0f;
static constexpr const float BLASTER_AWARENESS_RANGE		= ATTACKING_AWARENESS_DEFAULT_RANGE + 1.5f;
#pragma endregion

#pragma region MONSTERS_HP_SPEED_STAT
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

static constexpr const int DAGGER_INITIAL_HP = 6;
static constexpr const float DAGGER_INITIAL_SPEED = 1.8f;

static constexpr const int ARCHER_INITIAL_HP = 3;
static constexpr const float ARCHER_INITIAL_SPEED = 1.0f;

static constexpr const int BLASTER_INITIAL_HP = 5;
static constexpr const float BLASTER_INITIAL_SPEED = 1.3f;


#pragma endregion

#pragma region ATTACKING_MOVMENT_DISTANCE
static constexpr const float DEFULAT_ATTACKING_MOVEMENT_DISTANCE = 2.0f;

static constexpr const float CAGED_SHOCKER_ATTACKING_MOVEMENT_DISTANCE	= DEFULAT_ATTACKING_MOVEMENT_DISTANCE + 1.5f;
static constexpr const float SWEEPER_ATTACKING_MOVEMENT_DISTANCE		= DEFULAT_ATTACKING_MOVEMENT_DISTANCE + 1.0f;
static constexpr const float WARDEN_ATTACKING_MOVEMENT_DISTANCE			= DEFULAT_ATTACKING_MOVEMENT_DISTANCE + 0.5f;
static constexpr const float HEABY_SLICER_ATTACKING_MOVEMENT_DISTANCE	= DEFULAT_ATTACKING_MOVEMENT_DISTANCE + 2.0f;
static constexpr const float LIGHT_SLICER_ATTACKING_MOVEMENT_DISTANCE	= DEFULAT_ATTACKING_MOVEMENT_DISTANCE + 1.0f;
static constexpr const float ZOMBIE_ATTACKING_MOVEMENT_DISTANCE			= DEFULAT_ATTACKING_MOVEMENT_DISTANCE + 4.0f;
static constexpr const float ARCHER_ATTACKING_MOVEMENT_DISTANCE			= DEFULAT_ATTACKING_MOVEMENT_DISTANCE + 2.0f;
static constexpr const float DAGGER_ATTACKING_MOVEMENT_DISTANCE			= DEFULAT_ATTACKING_MOVEMENT_DISTANCE + 5.0f;
static constexpr const float BLASTER_ATTACKING_MOVEMENT_DISTANCE		= DEFULAT_ATTACKING_MOVEMENT_DISTANCE + 3.0f;
#pragma endregion

#pragma region MONSTER_EXP
static constexpr const UINT CAGED_SHOCKER_EXP	= 4;
static constexpr const UINT SWEEPER_EXP			= 3;
static constexpr const UINT WARDEN_EXP			= 1;
static constexpr const UINT HEABY_SLICER_EXP	= 4;
static constexpr const UINT LIGHT_SLICER_EXP	= 3;
static constexpr const UINT ZOMBIE_EXP			= 1;
static constexpr const UINT ARCHER_EXP			= 2;
static constexpr const UINT DAGGER_EXP			= 3;
static constexpr const UINT BLASTER_EXP			= 3;
#pragma endregion

static constexpr const UINT MANIPULATED_VALUE = 1;

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
		, mExp()
		, mSpeed(0.0f)
		, mAttackingAwarenessRange(ATTACKING_AWARENESS_DEFAULT_RANGE)
		, mAttackingMovementDistance(0.0f)
		, mSpawningTimer(SPAWNING_TIME)
		, mAttackSFXTimer(ATTACK_SFX_INTERVAL_TIME)
		, mHittedPushDistance(HIT_PUSH_ATTACK_DISTANCE)
		, meLookDir(eObjectLookDirection::LEFT)
		, meState(eMonsterState::SPAWNING)
		, meMonsterType(eMonsterType)
	{
		setAwarenessRange();
		setAnimKey();
		setInitialStat();
		setAttackingMovementDistance();
	}

	MonsterScript::MonsterScript()
		: Script()
		, mpTranform(nullptr)
		, mpPlayerTransform(nullptr)
		, mpAnimator(nullptr)
		, mpEffectScript(nullptr)
		, mpPlayerScript(nullptr)
		, mMaxHP(0)
		, mCurrHP(0)
		, mExp(0)
		, mSpeed(0.0f)
		, mAttackingAwarenessRange(0)
		, mAttackingMovementDistance(0.0f)
		, mSpawningTimer(SPAWNING_TIME)
		, mHittedPushDistance(HIT_PUSH_ATTACK_DISTANCE)
		, meLookDir(eObjectLookDirection::LEFT)
		, meState(eMonsterState::SPAWNING)
		, meMonsterType(eMonsterType::LV_1_ACIENT_BOSS)
		, mAttackSFXTimer(ATTACK_SFX_INTERVAL_TIME)
	{
	}

	void MonsterScript::Initialize()
	{
		setAnimationEvent();
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
		if (meState == eMonsterState::ATTACKING)
		{
			mAttackSFXTimer -= Time::DeltaTime();
			if (mAttackSFXTimer < 0.0f)
			{
				playAttackingSFX();
				mAttackSFXTimer = ATTACK_SFX_INTERVAL_TIME;
			}
		}
	}

#pragma region ANIMATION_EVENT
	void MonsterScript::AnimationAttackStart()
	{
		mpAnimator->InitializeCurrAnimation();
	}
	void MonsterScript::AnimationAttackComplete()
	{
		setState(eMonsterState::TRACING);
		mAttackSFXTimer = ATTACK_SFX_INTERVAL_TIME;
	}

	void MonsterScript::AnimationHittedStart()
	{
		SFXManager::GetInstance().Play(eSFXType::MONSTER_HITTED);
		mpAnimator->InitializeCurrAnimation();
	}
	void MonsterScript::AnimationHittedComplete()
	{
		setState(eMonsterState::TRACING);
	}

	void MonsterScript::AnimationDieStart()
	{
		SFXManager::GetInstance().Play(eSFXType::MONSTER_DIE);
		mpAnimator->InitializeCurrAnimation();
	}
	void MonsterScript::AnimationDieComplete()
	{
		static_cast<Monster*>(GetOwner())->SetInactive();
	}
#pragma endregion

#pragma region COLLIDER_TRIGGER
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
				mpPlayerScript->SetIsHitAttack(true);
				if (meState != eMonsterState::DEAD)
				{
					setState(eMonsterState::HITTED);
				}
			}
		}

		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER_SKILL)
		{
			Animator* pPlayerSkillAnimator = static_cast<Animator*>(pOtherCollider->GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
			assert(pPlayerSkillAnimator != nullptr);
			PlayerSkillScript* pScript = static_cast<PlayerSkillScript*>(pOtherCollider->GetOwner()->GetScriptOrNull());
			const SkillStat& skillStat = pScript->GetStat();
			assert(pScript != nullptr);
			switch (pScript->GetSkillType())
			{
			case ePlayerSkillType::ELETRIC_BEAM:
			/* INTENTIONAL FALL THROUGH */
			case ePlayerSkillType::ELETRIC_STRIKE:
			{
				if (pPlayerSkillAnimator->GetCurrentAnimationIndex() == skillStat.VailedAttackIndex)
				{
					decreaseHP(skillStat.Damage);
					mpPlayerScript->SetIsHitSkillAttack(true);
					if (meState != eMonsterState::DEAD)
					{
						setState(eMonsterState::HITTED);
					}
				}
				break;
			}
			case ePlayerSkillType::TORNADO:
			{
				float currXPos = mpTranform->GetOnlyXPosition();
				if (meLookDir == eObjectLookDirection::LEFT)
				{
					mpTranform->SetOnlyXPosition(currXPos + (skillStat.PushDistance * Time::DeltaTime()));
				}
				else
				{
					mpTranform->SetOnlyXPosition(currXPos - (skillStat.PushDistance * Time::DeltaTime()));
				}
				break;
			}
			default:
				assert(false);
				break;
			}


		}
	}
	void MonsterScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
#pragma endregion

#pragma region INITIALIZE
	void MonsterScript::setAnimKey()
	{
		switch (meMonsterType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			mAnimIdleKey	= MonsterManager::CAGED_SHOKER_IDLE_ANIM_KEY;
			mAnimMoveKey	= MonsterManager::CAGED_SHOKER_MOVING_ANIM_KEY;
			mAnimAttackKey	= MonsterManager::CAGED_SHOKER_ATTACK_ANIM_KEY;
			mAnimHittedKey	= MonsterManager::CAGED_SHOKER_HITTED_ANIM_KEY;
			mAnimDieKey		= MonsterManager::CAGED_SHOKER_DIE_ANIM_KEY;
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			mAnimIdleKey	= MonsterManager::SWEEPER_IDLE_ANIM_KEY;
			mAnimMoveKey	= MonsterManager::SWEEPER_MOVING_ANIM_KEY;
			mAnimAttackKey	= MonsterManager::SWEEPER_ATTACK_ANIM_KEY;
			mAnimHittedKey	= MonsterManager::SWEEPER_HITTED_ANIM_KEY;
			mAnimDieKey		= MonsterManager::SWEEPER_DIE_ANIM_KEY;
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			mAnimIdleKey	= MonsterManager::WARDEN_IDLE_ANIM_KEY;
			mAnimMoveKey	= MonsterManager::WARDEN_MOVING_ANIM_KEY;
			mAnimAttackKey	= MonsterManager::WARDEN_ATTACK_ANIM_KEY;
			mAnimHittedKey	= MonsterManager::WARDEN_HITTED_ANIM_KEY;
			mAnimDieKey		= MonsterManager::WARDEN_DIE_ANIM_KEY;
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			mAnimIdleKey	= MonsterManager::ZOMBIE_IDLE_ANIM_KEY;
			mAnimMoveKey	= MonsterManager::ZOMBIE_MOVING_ANIM_KEY;
			mAnimAttackKey	= MonsterManager::ZOMBIE_ATTACK_ANIM_KEY;
			mAnimHittedKey	= MonsterManager::ZOMBIE_HITTED_ANIM_KEY;
			mAnimDieKey		= MonsterManager::ZOMBIE_DIE_ANIM_KEY;
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			mAnimIdleKey	= MonsterManager::HEABY_SLICER_IDLE_ANIM_KEY;
			mAnimMoveKey	= MonsterManager::HEABY_SLICER_MOVING_ANIM_KEY;
			mAnimAttackKey	= MonsterManager::HEABY_SLICER_ATTACK_ANIM_KEY;
			mAnimHittedKey	= MonsterManager::HEABY_SLICER_HITTED_ANIM_KEY;
			mAnimDieKey		= MonsterManager::HEABY_SLICER_DIE_ANIM_KEY;
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			mAnimIdleKey	= MonsterManager::LIGHT_SLICER_IDLE_ANIM_KEY;
			mAnimMoveKey	= MonsterManager::LIGHT_SLICER_MOVING_ANIM_KEY;
			mAnimAttackKey	= MonsterManager::LIGHT_SLICER_ATTACK_ANIM_KEY;
			mAnimHittedKey	= MonsterManager::LIGHT_SLICER_HITTED_ANIM_KEY;
			mAnimDieKey		= MonsterManager::LIGHT_SLICER_DIE_ANIM_KEY;
			break;
		}
		case eMonsterType::LV_1_DAGGER:
		{
			mAnimIdleKey	= MonsterManager::DAGGER_IDLE_ANIM_KEY;
			mAnimMoveKey	= MonsterManager::DAGGER_MOVING_ANIM_KEY;
			mAnimAttackKey	= MonsterManager::DAGGER_ATTACK_ANIM_KEY;
			mAnimHittedKey	= MonsterManager::DAGGER_HITTED_ANIM_KEY;
			mAnimDieKey		= MonsterManager::DAGGER_DIE_ANIM_KEY;
			break;
		}
		case eMonsterType::LV_1_ARCHER:
		{
			mAnimIdleKey	= MonsterManager::ARCHER_IDLE_ANIM_KEY;
			mAnimMoveKey	= MonsterManager::ARCHER_MOVING_ANIM_KEY;
			mAnimAttackKey	= MonsterManager::ARCHER_ATTACK_ANIM_KEY;
			mAnimHittedKey	= MonsterManager::ARCHER_HITTED_ANIM_KEY;
			mAnimDieKey		= MonsterManager::ARCHER_DIE_ANIM_KEY;
			break;
		}
		case eMonsterType::LV_1_BLASTER:
		{
			mAnimIdleKey	= MonsterManager::BLASTER_IDLE_ANIM_KEY;
			mAnimMoveKey	= MonsterManager::BLASTER_MOVING_ANIM_KEY;
			mAnimAttackKey	= MonsterManager::BLASTER_ATTACK_ANIM_KEY;
			mAnimHittedKey	= MonsterManager::BLASTER_HITTED_ANIM_KEY;
			mAnimDieKey		= MonsterManager::BLASTER_DIE_ANIM_KEY;
			break;
		}
		default:
			assert(false);
			break;
		}
	}
	void MonsterScript::setAnimationEvent()
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
	void MonsterScript::setInitialStat()
	{
		switch (meMonsterType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			mMaxHP = CAGED_SHOKER_INITIAL_HP;
			mSpeed = CAGED_SHOKER_INITIAL_SPEED;
			mExp = CAGED_SHOCKER_EXP;
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			mMaxHP = SWEEPER_INITIAL_HP;
			mSpeed = SWEEPER_INITIAL_SPEED;
			mExp = SWEEPER_EXP;
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			mMaxHP = WARDEN_INITIAL_HP;
			mSpeed = WARDEN_INITIAL_SPEED;
			mExp = WARDEN_EXP;
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			mMaxHP = ZOMBIE_INITIAL_HP;
			mSpeed = ZOMBIE_INITIAL_SPEED;
			mExp = ZOMBIE_EXP;
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			mMaxHP = HEABY_SLICER_INITIAL_HP;
			mSpeed = HEABY_SLICER_INITIAL_SPEED;
			mExp = HEABY_SLICER_EXP;
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			mMaxHP = LIGHT_SLICER_INITIAL_HP;
			mSpeed = LIGHT_SLICER_INITIAL_SPEED;
			mExp = LIGHT_SLICER_EXP;
			break;
		}
		case eMonsterType::LV_1_DAGGER:
		{
			mMaxHP = DAGGER_INITIAL_HP;
			mSpeed = DAGGER_INITIAL_SPEED;
			mExp = DAGGER_EXP;
			break;
		}
		case eMonsterType::LV_1_ARCHER:
		{
			mMaxHP = ARCHER_INITIAL_HP;
			mSpeed = ARCHER_INITIAL_SPEED;
			mExp = ARCHER_EXP;
			break;
		}
		case eMonsterType::LV_1_BLASTER:
		{
			mMaxHP = BLASTER_INITIAL_HP;
			mSpeed = BLASTER_INITIAL_SPEED;
			mExp = BLASTER_EXP;
			break;
		}
		default:
			assert(false);
			break;
		}
		mCurrHP = mMaxHP;
	}
	void MonsterScript::setAwarenessRange()
	{
		switch (meMonsterType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			mAttackingAwarenessRange = CAGED_SHOCKER_AWARENESS_RANGE;
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			mAttackingAwarenessRange = SWEEPER_AWARENESS_RANGE;
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			mAttackingAwarenessRange = WARDEN_AWARENESS_RANGE;
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			mAttackingAwarenessRange = ZOMBIE_AWARENESS_RANGE;
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			mAttackingAwarenessRange = HEABY_SLICER_AWARENESS_RANGE;
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			mAttackingAwarenessRange = LIGHT_SLICER_AWARENESS_RANGE;
			break;
		}
		case eMonsterType::LV_1_DAGGER:
		{
			mAttackingAwarenessRange = DAGGER_AWARENESS_RANGE;
			break;
		}
		case eMonsterType::LV_1_ARCHER:
		{
			mAttackingAwarenessRange = ARCHER_AWARENESS_RANGE;
			break;
		}
		case eMonsterType::LV_1_BLASTER:
		{

			mAttackingAwarenessRange = BLASTER_AWARENESS_RANGE;
			break;
		}
		default:
			assert(false);
			break;
		}
	}
	void MonsterScript::setAttackingMovementDistance()
	{
		switch (meMonsterType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			mAttackingMovementDistance = CAGED_SHOCKER_ATTACKING_MOVEMENT_DISTANCE;
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			mAttackingMovementDistance = SWEEPER_ATTACKING_MOVEMENT_DISTANCE;
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			mAttackingMovementDistance = WARDEN_ATTACKING_MOVEMENT_DISTANCE;
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			mAttackingMovementDistance = ZOMBIE_ATTACKING_MOVEMENT_DISTANCE;
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			mAttackingMovementDistance = HEABY_SLICER_ATTACKING_MOVEMENT_DISTANCE;
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			mAttackingMovementDistance = LIGHT_SLICER_ATTACKING_MOVEMENT_DISTANCE;
			break;
		}
		case eMonsterType::LV_1_DAGGER:
		{
			mAttackingMovementDistance = DAGGER_ATTACKING_MOVEMENT_DISTANCE;
			break;
		}
		case eMonsterType::LV_1_ARCHER:
		{
			mAttackingMovementDistance = ARCHER_ATTACKING_MOVEMENT_DISTANCE;
			break;
		}
		case eMonsterType::LV_1_BLASTER:
		{
			mAttackingMovementDistance = BLASTER_ATTACKING_MOVEMENT_DISTANCE;
			break;
		}
		default:
			assert(false);
			break;
		}
	}
#pragma endregion

	void MonsterScript::SetRespawnState()
	{
		setInitialStat();
		calculateDistanceFromPlayerToSetLookDirection();
		setState(eMonsterState::SPAWNING);
		mSpawningTimer = SPAWNING_TIME;
	}

	void MonsterScript::setPosition()
	{
		switch (meState)
		{
		case eMonsterState::TRACING:
		{
			moveOrChangeAttackingState();
			return;
		}
		case eMonsterState::ATTACKING:
		{
			float currXPos = mpTranform->GetOnlyXPosition();
			float movementXDistance = 0.0f;
			switch (meMonsterType)
			{
			case eMonsterType::LV_1_CAGED_SHOKER:
			{
				if (mpAnimator->GetCurrentAnimationIndex() == CAGED_SHOCKER_ATTACk_VAILED_INDEX_1)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos(mAttackingMovementDistance * Time::DeltaTime(), currXPos));
				}
				else if (mpAnimator->GetCurrentAnimationIndex() == CAGED_SHOCKER_ATTACk_VAILED_INDEX_2)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos((mAttackingMovementDistance + 1.0f) * Time::DeltaTime(), currXPos));
				}
				break;
			}
			case eMonsterType::LV_1_SWEEPER:
			{
				if (mpAnimator->GetCurrentAnimationIndex() == SWEEPER_ATTACK_VAILED_INDEX)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos(mAttackingMovementDistance * Time::DeltaTime(), currXPos));
				}
				break;
			}
			case eMonsterType::LV_1_WARDEN:
			{
				if (mpAnimator->GetCurrentAnimationIndex() == WARDEN_ATTACK_VAILED_INDEX)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos(mAttackingMovementDistance * Time::DeltaTime(), currXPos));
				}
				break;
			}
			case eMonsterType::LV_1_ZOMBIE:
			{
				if (mpAnimator->GetCurrentAnimationIndex() == ZOMBIE_ATTACK_VAILED_INDEX)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos(mAttackingMovementDistance * Time::DeltaTime(), currXPos));
				}
				break;
			}
			case eMonsterType::LV_1_HEABY_SLICER:
			{
				if (mpAnimator->GetCurrentAnimationIndex() == HEABY_SLICER_ATTACK_VAILED_INDEX_1)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos(mAttackingMovementDistance * Time::DeltaTime(), currXPos));
				}
				else if (mpAnimator->GetCurrentAnimationIndex() == HEABY_SLICER_ATTACK_VAILED_INDEX_2)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos(mAttackingMovementDistance * Time::DeltaTime(), currXPos));
				}
				break;
			}
			case eMonsterType::LV_1_LIGHT_SLICER:
			{
				if (mpAnimator->GetCurrentAnimationIndex() == LIGHT_SLICER_ATTACK_VAILED_INDEX_1 || mpAnimator->GetCurrentAnimationIndex() == LIGHT_SLICER_ATTACK_VAILED_INDEX_2)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos(mAttackingMovementDistance * Time::DeltaTime(), currXPos));
				}
				else if (mpAnimator->GetCurrentAnimationIndex() == LIGHT_SLICER_ATTACK_VAILED_INDEX_3)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos((mAttackingMovementDistance + 5.0f) * Time::DeltaTime(), currXPos));
				}
				break;
			}
			case eMonsterType::LV_1_DAGGER:
			{
				if (mpAnimator->GetCurrentAnimationIndex() == DAGGER_ATTACK_VAILED_INDEX_1)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos(mAttackingMovementDistance * Time::DeltaTime(), currXPos));
				}
				else if (mpAnimator->GetCurrentAnimationIndex() == DAGGER_ATTACK_VAILED_INDEX_2)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos((mAttackingMovementDistance - 2.0f) * Time::DeltaTime(), currXPos));
				}
				break;
			}
			case eMonsterType::LV_1_ARCHER:
			{
				break;
			}
			case eMonsterType::LV_1_BLASTER:
			{
				if (mpAnimator->GetCurrentAnimationIndex() == BLASTER_ATTACK_VAILED_INDEX)
				{
					mpTranform->SetOnlyXPosition(getMovementAttackingPos(mAttackingMovementDistance * Time::DeltaTime(), currXPos));
				}
				break;
			}
			default:
				assert(false);
				break;
			}

			return;
		}
		case eMonsterState::HITTED:
		{
			if (mpPlayerScript->GetAttackType() == eAttackType::PUSH)
			{
				float monCurrXPos = mpTranform->GetOnlyXPosition();
				if (meLookDir == eObjectLookDirection::LEFT)
				{
					mpTranform->SetOnlyXPosition(monCurrXPos + mHittedPushDistance * Time::DeltaTime());
				}
				else
				{
					mpTranform->SetOnlyXPosition(monCurrXPos - mHittedPushDistance * Time::DeltaTime());
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

	float MonsterScript::getMovementAttackingPos(float movementXAmount, float currXPos)
	{
		if (meLookDir == eObjectLookDirection::LEFT)
		{
			return currXPos -= movementXAmount;
		}
		else
		{
			return currXPos += movementXAmount;
		}
	}
	void MonsterScript::moveOrChangeAttackingState()
	{
		assert(mpTranform != nullptr);
		const float distance = calculateDistanceFromPlayerToSetLookDirection();
		if (isCloseEnoughFromPlayerToChangeAttackingState(distance))
		{
			setState(eMonsterState::ATTACKING);
			return;
		}
		
		float currXPos = mpTranform->GetOnlyXPosition();
		float movementXAmount = 0.0f;
		movementXAmount = mSpeed * Time::DeltaTime();
		if (meLookDir == eObjectLookDirection::LEFT)
			{currXPos -= movementXAmount;}
		else
			{currXPos += movementXAmount;}
		mpTranform->SetOnlyXPosition(currXPos);
	}

	void MonsterScript::setLookDir(const float xPos)
	{
		if (xPos < 0.0f)
		{
			meLookDir = eObjectLookDirection::LEFT;
		}
		else
		{
			meLookDir = eObjectLookDirection::RIGHT;
		}
	}

	bool MonsterScript::isCloseEnoughFromPlayerToChangeAttackingState(const float xPos)
	{
		if (std::abs(xPos) < mAttackingAwarenessRange)
		{
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
			//playHitEffectAnimation();
			break;
		}
		default:
			break;
		}
	}

	void MonsterScript::playAttackingSFX()
	{
		const int RANDOM = std::rand() % 3;
		const UINT CURR_IDX = mpAnimator->GetCurrentAnimationIndex();
		switch (meMonsterType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			if (CURR_IDX == CAGED_SHOCKER_ATTACk_VAILED_INDEX_1 - MANIPULATED_VALUE || CURR_IDX == CAGED_SHOCKER_ATTACk_VAILED_INDEX_2 - MANIPULATED_VALUE)
			{
				choiceAttackingSFX(RANDOM);
			}
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			if (CURR_IDX == SWEEPER_ATTACK_VAILED_INDEX - MANIPULATED_VALUE)
			{
				choiceAttackingSFX(RANDOM);
			}
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			if (CURR_IDX == WARDEN_ATTACK_VAILED_INDEX - MANIPULATED_VALUE)
			{
				playEruptionSFX();
			}
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			if (CURR_IDX == ZOMBIE_ATTACK_VAILED_INDEX)
			{
				choiceAttackingSFX(RANDOM);
			}
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			if (CURR_IDX == HEABY_SLICER_ATTACK_VAILED_INDEX_1 - MANIPULATED_VALUE || CURR_IDX == HEABY_SLICER_ATTACK_VAILED_INDEX_2 - MANIPULATED_VALUE)
			{
				choiceAttackingSFX(RANDOM);
			}
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			if (CURR_IDX == LIGHT_SLICER_ATTACK_VAILED_INDEX_1 || CURR_IDX == LIGHT_SLICER_ATTACK_VAILED_INDEX_2 || CURR_IDX == LIGHT_SLICER_ATTACK_VAILED_INDEX_3)
			{
				choiceAttackingSFX(RANDOM);
			}
			break;
		}
		case eMonsterType::LV_1_DAGGER:
		{
			if (CURR_IDX == DAGGER_ATTACK_VAILED_INDEX_1 - MANIPULATED_VALUE || CURR_IDX == DAGGER_ATTACK_VAILED_INDEX_2 - MANIPULATED_VALUE)
			{
				choiceAttackingSFX(RANDOM);
			}
			break;
		}
		case eMonsterType::LV_1_ARCHER:
		{
			if (CURR_IDX == ARCHER_ATTACK_VAILED_INDEX - MANIPULATED_VALUE)
			{
				playEruptionSFX();
			}
			break;
		}
		case eMonsterType::LV_1_BLASTER:
		{
			if (CURR_IDX == BLASTER_ATTACK_VAILED_INDEX - MANIPULATED_VALUE)
			{
				playEruptionSFX();
			}
			break;
		}
		default:
			assert(false);
			break;
		}
		return;
	}

	void MonsterScript::playEruptionSFX()
	{
		SFXManager::GetInstance().Play(eSFXType::MONSTER_ERUPTION);
	}

	void MonsterScript::choiceAttackingSFX(const int random)
	{
		switch (random)
		{
		case 0:
		{
			SFXManager::GetInstance().Play(eSFXType::MONSTER_SWING_1);
			break;
		}
		case 1:
		{
			SFXManager::GetInstance().Play(eSFXType::MONSTER_SWING_2);
			break;
		}
		case 2:
		{
			SFXManager::GetInstance().Play(eSFXType::MONSTER_SWING_3);
			break;
		}
		default:
			assert(false);
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

	float MonsterScript::calculateDistanceFromPlayerToSetLookDirection()
	{
		float monCurrXPos = mpTranform->GetOnlyXPosition();
		float distance = mpPlayerTransform->GetOnlyXPosition() - monCurrXPos;
		setLookDir(distance);
		return distance;
	}
	void MonsterScript::decreaseHP(const int amount)
	{
		assert(mpPlayerScript != nullptr);
		if (meState == eMonsterState::HITTED)
		{
			return;
		}
		mCurrHP -= std::abs(amount);
		if (mCurrHP <= 0)
		{
			mCurrHP = 0;
			mpPlayerScript->IncreaseEXP(mExp);
			setState(eMonsterState::DEAD);
		}
	}


}