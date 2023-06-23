#include "jhAcientBossMonsterScript.h"
#include "jhAnimator.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"
#include "jhTime.h"
#include "jhCollider2D.h"
#include "jhBossMonster.h"
#include "jhSFXManager.h"
#include "jhGameStateManager.h"
#include <random>

static constexpr const float ATTACK_SFX_INTERVAL_TIME = 0.1f;
static constexpr const UINT MELLE_ATTACK_VAILED_INDEX = 12;
static constexpr const UINT SPIN_ATTACK_VAILED_INDEX_1 = 9;
static constexpr const UINT SPIN_ATTACK_VAILED_INDEX_2 = 16;
static constexpr const UINT RANGE_ATTACK_VAILED_INDEX = 10;
static constexpr const UINT SUPER_ATTACK_VAILED_INDEX = 12;

static constexpr const UINT PLAYER_VAILED_ATTACK_ANIMATION_INDEX = 1;

static constexpr const float INVINCIBILITY_TIME = 0.5f;
static constexpr const float MELEE_ATTACK_AWARENESS_RANGE = 3.5f;
static constexpr const float SPIN_ATTACK_AWARENESS_RANGE = 2.5f;
static constexpr const float RANGE_ATTACK_AWARENESS_RANGE = 4.5f;

static constexpr const UINT MELEE_ATTACK_NUMBER = 0;
static constexpr const UINT SPIN_ATTACK_NUMBER = 1;
static constexpr const UINT RANGE_ATTACK_NUMBER = 2;

static constexpr UINT ACIENT_BOSS_INITIAL_HP = 30;
static constexpr float ACIENT_BOSS_INITIAL_SPEED = 1.0f;

static constexpr const UINT PHASE_2_HP = static_cast<UINT>(ACIENT_BOSS_INITIAL_HP * 0.7f);
static constexpr const UINT PHASE_3_HP = static_cast<UINT>(ACIENT_BOSS_INITIAL_HP * 0.5f);



namespace jh
{
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_IDLE_ANIM_KEY				= L"Idle";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_MOVING_ANIM_KEY				= L"Moving";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_MELLE_ATTACK_ANIM_KEY		= L"MelleAttack";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_SPIN_ATTACK_ANIM_KEY		= L"SpinAttack";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_RANGE_ATTACK_ANIM_KEY		= L"RangeAttack";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_BUFF_ANIM_KEY				= L"Buff";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_SUPER_ATTACK_ANIM_KEY		= L"SuperAttack";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_DIE_ANIM_KEY				= L"Die";


	AcientBossMonsterScript::AcientBossMonsterScript(PlayerScript* pPlayerScript)
		: MonsterScript()
		, meState(eBossMonsterState::TRACING)
		, mePhase(eBossMonsterPhase::LV_1_PHASE)
		, mInvincibilityTimer(INVINCIBILITY_TIME)
		, mbIsCountingInvincibilityTime(false)
		, mbIsHittted(false)
		, mAttackSFXTimer(ATTACK_SFX_INTERVAL_TIME)
	{
		mAttackingAwarenessRange = MELEE_ATTACK_AWARENESS_RANGE;
		mpPlayerScript = pPlayerScript;
		assert(mpPlayerScript != nullptr);
		mMaxHP = ACIENT_BOSS_INITIAL_HP;
		mCurrHP = mMaxHP;
		mSpeed = ACIENT_BOSS_INITIAL_SPEED;
	}

	void AcientBossMonsterScript::Initialize()
	{
		setAnimationEvent();
		mpTranform = GetOwner()->GetTransform();
		assert(mpTranform != nullptr);
		assert(mpPlayerScript != nullptr);
		mpPlayerTransform = mpPlayerScript->GetOwner()->GetTransform();
		assert(mpPlayerTransform);
		SFXManager::GetInstance().Play(eSFXType::BOSS_MONSTER_MOVING);
	}
	void AcientBossMonsterScript::Update()
	{
		assert(mpTranform != nullptr);

		float currPos = mpTranform->GetOnlyXPosition();
		float distanceFromPlayer = currPos - mpPlayerTransform->GetOnlyXPosition();
		float absDisatanceFromPlayer = std::abs(distanceFromPlayer);
		float moveXPos = 0.0f;
		if (mbIsCountingInvincibilityTime)
		{
			mInvincibilityTimer -= Time::DeltaTime();
			if (mbIsHittted)
			{
				playHitEffectAnimation();
			}
			if (mInvincibilityTimer < 0.0f)
			{
				mInvincibilityTimer = INVINCIBILITY_TIME;
				mbIsCountingInvincibilityTime = false;
				mbIsHittted = false;
			}
		}


		switch (mePhase)
		{
		case eBossMonsterPhase::LV_1_PHASE:
		{
			static std::random_device sRd;
			static std::mt19937 sGen(sRd());
			static std::uniform_int_distribution<> sDist(MELEE_ATTACK_NUMBER, SPIN_ATTACK_NUMBER);
			if (absDisatanceFromPlayer < MELEE_ATTACK_AWARENESS_RANGE &&
				meState != eBossMonsterState::MELLE_ATTACKING &&
				meState != eBossMonsterState::SPIN_ATTACKING)
			{
				if (absDisatanceFromPlayer < SPIN_ATTACK_AWARENESS_RANGE)
				{
					setState(eBossMonsterState::SPIN_ATTACKING);
				}
				else
				{
					setLookDir(distanceFromPlayer);
					flipLookDirection();
					setState(eBossMonsterState::MELLE_ATTACKING);
				}
				return;
			}
			break;
		}
		case eBossMonsterPhase::LV_2_PHASE:
		{
			if (absDisatanceFromPlayer < SPIN_ATTACK_AWARENESS_RANGE &&
				meState != eBossMonsterState::SPIN_ATTACKING &&
				meState != eBossMonsterState::RANGE_ATTACKING)
			{
				setState(eBossMonsterState::SPIN_ATTACKING);
				return;
			}

			if (absDisatanceFromPlayer < RANGE_ATTACK_AWARENESS_RANGE &&
				meState != eBossMonsterState::SPIN_ATTACKING &&
				meState != eBossMonsterState::RANGE_ATTACKING)
			{
				setLookDir(distanceFromPlayer);
				setState(eBossMonsterState::RANGE_ATTACKING);
				return;
			}
			break;
		}
		case eBossMonsterPhase::LV_3_PHASE:
		{
			if (meState == eBossMonsterState::BUFF || meState == eBossMonsterState::DEATH)
			{
				break;
			}

			if (absDisatanceFromPlayer < MELEE_ATTACK_AWARENESS_RANGE && absDisatanceFromPlayer > SPIN_ATTACK_AWARENESS_RANGE &&
					 meState != eBossMonsterState::SPIN_ATTACKING &&
					 meState != eBossMonsterState::SUPER_ATTACKING &&
					 meState != eBossMonsterState::MELLE_ATTACKING)
			{
				setLookDir(distanceFromPlayer);
				flipLookDirection();
				setState(eBossMonsterState::MELLE_ATTACKING);
				return;
			}
			if (absDisatanceFromPlayer < SPIN_ATTACK_AWARENESS_RANGE &&
					 meState != eBossMonsterState::SPIN_ATTACKING &&
					 meState != eBossMonsterState::SUPER_ATTACKING &&
					 meState != eBossMonsterState::MELLE_ATTACKING)
			{
				setState(eBossMonsterState::SPIN_ATTACKING);
				return;
			}
			if (absDisatanceFromPlayer < RANGE_ATTACK_AWARENESS_RANGE &&
				meState != eBossMonsterState::SPIN_ATTACKING &&
				meState != eBossMonsterState::SUPER_ATTACKING &&
				meState != eBossMonsterState::MELLE_ATTACKING)
			{
				setLookDir(distanceFromPlayer);
				setState(eBossMonsterState::SUPER_ATTACKING);
				return;
			}
			break;
		}
		default:
			assert(false);
			break;
		}
#pragma region TRACING
		if (meState == eBossMonsterState::TRACING)
		{
			if (distanceFromPlayer < 0.0f)
			{
				meLookDir = eObjectLookDirection::LEFT;
				moveXPos = mSpeed * Time::DeltaTime();
			}
			else
			{
				meLookDir = eObjectLookDirection::RIGHT;
				moveXPos = -(mSpeed * Time::DeltaTime());
			}
			mpTranform->SetOnlyXPosition(currPos + moveXPos);
		}
#pragma endregion


		if (meState == eBossMonsterState::SUPER_ATTACKING ||
			meState == eBossMonsterState::MELLE_ATTACKING ||
			meState == eBossMonsterState::RANGE_ATTACKING)
		{
			mAttackSFXTimer -= Time::DeltaTime();
			if (mAttackSFXTimer < 0.0f)
			{
				playAttackingSFX();
				mAttackSFXTimer = ATTACK_SFX_INTERVAL_TIME;
			}
		}


		setAnimaionFlip();
		playAnimation();
	}



#pragma region UTILL

	void AcientBossMonsterScript::decreaseHP(const int amount)
	{
		mCurrHP -= std::abs(amount);
		SFXManager::GetInstance().Play(eSFXType::MONSTER_HITTED);
		if (mePhase == eBossMonsterPhase::LV_1_PHASE && mCurrHP <= PHASE_2_HP)
		{
			if (mePhase != eBossMonsterPhase::LV_2_PHASE)
			{
				setPhaseState(eBossMonsterPhase::LV_2_PHASE);
			}
		}

		if (mePhase == eBossMonsterPhase::LV_2_PHASE && mCurrHP <= PHASE_3_HP)
		{
			if (mePhase != eBossMonsterPhase::LV_3_PHASE)
			{
				setPhaseState(eBossMonsterPhase::LV_3_PHASE);
				setState(eBossMonsterState::BUFF);
			}
		}

		if (mCurrHP <= 0)
		{
			mCurrHP = 0;
			setState(eBossMonsterState::DEATH);
			SFXManager::GetInstance().Stop(eSFXType::BOSS_MONSTER_MOVING);
		}

	}

	void AcientBossMonsterScript::flipLookDirection()
	{
		if (meLookDir == eObjectLookDirection::LEFT)
		{
			meLookDir = eObjectLookDirection::RIGHT;
		}
		else
		{
			meLookDir = eObjectLookDirection::LEFT;
		}
	}

	void AcientBossMonsterScript::playAttackingSFX()
	{
		const UINT CURR_IDX = mpAnimator->GetCurrentAnimationIndex();

		switch (meState)
		{
		case jh::eBossMonsterState::MELLE_ATTACKING:
		{
			if (CURR_IDX == MELLE_ATTACK_VAILED_INDEX)
			{
				SFXManager::GetInstance().Play(eSFXType::BOSS_MONSTER_FISTING);
			}
			break;
		}
		case jh::eBossMonsterState::RANGE_ATTACKING:
		{
			if (CURR_IDX == RANGE_ATTACK_VAILED_INDEX)
			{
				SFXManager::GetInstance().Play(eSFXType::BOSS_MONSTER_ERUPTION);
			}
			break;
		}
		case jh::eBossMonsterState::SUPER_ATTACKING:
		{
			if (CURR_IDX == (SUPER_ATTACK_VAILED_INDEX - 5))
			{
				SFXManager::GetInstance().Play(eSFXType::BOSS_MONSTER_POWER_ERUPTION);
			}
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void AcientBossMonsterScript::setAnimaionFlip()
	{
		if (meLookDir == eObjectLookDirection::LEFT)
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(false);
		}
		else
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(true);
		}
	}

	void AcientBossMonsterScript::playAnimation()
	{
		assert(mpAnimator != nullptr);
		switch (meState)
		{
		case eBossMonsterState::IDLE:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_IDLE_ANIM_KEY, true);
			break;
		}
		case eBossMonsterState::TRACING:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_MOVING_ANIM_KEY, true);
			break;
		}
		case eBossMonsterState::MELLE_ATTACKING:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_MELLE_ATTACK_ANIM_KEY, true);
			break;
		}
		case eBossMonsterState::SPIN_ATTACKING:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_SPIN_ATTACK_ANIM_KEY, true);
			break;
		}
		case eBossMonsterState::RANGE_ATTACKING:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_RANGE_ATTACK_ANIM_KEY, true);
			break;
		}
		case eBossMonsterState::BUFF:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_BUFF_ANIM_KEY, true);
			break;
		}
		case eBossMonsterState::SUPER_ATTACKING:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_SUPER_ATTACK_ANIM_KEY, true);
			break;
		}
		case eBossMonsterState::DEATH:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_DIE_ANIM_KEY, true);
			break;
		}
		default:
			assert(false);
			break;
		}
	}
#pragma endregion



#pragma region ANIMATION_EVENT
	void AcientBossMonsterScript::AnimationIdleStart()
	{
	}

	void AcientBossMonsterScript::AnimationMovingStart()
	{
	}
	void AcientBossMonsterScript::AnimationMovingComplete()
	{
	}

	void AcientBossMonsterScript::AnimationMelleAttackStart()
	{
		mpAnimator->InitializeCurrAnimation();
	}
	void AcientBossMonsterScript::AnimationMelleAttackComplete()
	{
		flipLookDirection();
		setState(eBossMonsterState::TRACING);
	}
	void AcientBossMonsterScript::AnimationSpinAttackStart()
	{
		SFXManager::GetInstance().Play(eSFXType::BOSS_MONSTER_SWING);
		mpAnimator->InitializeCurrAnimation();
	}
	void AcientBossMonsterScript::AnimationSpinAttackComplete()
	{
		setState(eBossMonsterState::TRACING);
	}
	void AcientBossMonsterScript::AnimationRangeAttackStart()
	{
		mpAnimator->InitializeCurrAnimation();
	}
	void AcientBossMonsterScript::AnimationRangeAttackComplete()
	{
		setState(eBossMonsterState::TRACING);
	}
	void AcientBossMonsterScript::AnimationBuffStart()
	{
		SFXManager::GetInstance().Play(eSFXType::BOSS_MONSTER_BUFF);
		mpAnimator->InitializeCurrAnimation();
		mbIsCountingInvincibilityTime = true;
	}
	void AcientBossMonsterScript::AnimationBuffComplete()
	{
		setState(eBossMonsterState::TRACING);
	}
	void AcientBossMonsterScript::AnimationSuperAttackStart()
	{
		mpAnimator->InitializeCurrAnimation();
	}
	void AcientBossMonsterScript::AnimationSuperAttackComplete()
	{
		setState(eBossMonsterState::TRACING);
	}
	void AcientBossMonsterScript::AnimationDieStart()
	{
		SFXManager::GetInstance().Play(eSFXType::BOSS_MONSTER_DIE);
		mpAnimator->InitializeCurrAnimation();
	}
	void AcientBossMonsterScript::AnimationDieComplete()
	{
		static_cast<BossMonster*>(GetOwner())->SetInactive();
		GameStateManager::GetInstance().OnKillBossMonster();
	}
#pragma endregion

#pragma region COLLIDER_TRIGGER
	void AcientBossMonsterScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{
	}
	void AcientBossMonsterScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER_WEAPON)
		{
			Animator* pPlayerAnimator = static_cast<Animator*>(mpPlayerScript->GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
			assert(pPlayerAnimator != nullptr);
			const ePlayerState eState = mpPlayerScript->GetPlayerState();

			if (pPlayerAnimator->GetCurrentAnimationIndex() == PLAYER_VAILED_ATTACK_ANIMATION_INDEX && eState == ePlayerState::ATTACKING)
			{
				if (mbIsCountingInvincibilityTime)
				{
					return;
				}
				mbIsHittted = true;
				mbIsCountingInvincibilityTime = true;
				decreaseHP(mpPlayerScript->GetPlayerStat().AttackDamage);
				mpPlayerScript->SetIsHitAttack(true);
			}
		}

	}
	void AcientBossMonsterScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
#pragma endregion

#pragma region INITIALIZE
	void AcientBossMonsterScript::setAnimationEvent()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(ACIENT_BOSS_IDLE_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationIdleStart, this);


		mpAnimator->GetStartEvent(ACIENT_BOSS_MOVING_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationMovingStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_MOVING_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationMovingComplete, this);


		mpAnimator->GetStartEvent(ACIENT_BOSS_MELLE_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationMelleAttackStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_MELLE_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationMelleAttackComplete, this);

		mpAnimator->GetStartEvent(ACIENT_BOSS_SPIN_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationSpinAttackStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_SPIN_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationSpinAttackComplete, this);

	
		mpAnimator->GetStartEvent(ACIENT_BOSS_RANGE_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationRangeAttackStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_RANGE_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationRangeAttackComplete, this);

		mpAnimator->GetStartEvent(ACIENT_BOSS_BUFF_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationBuffStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_BUFF_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationBuffComplete, this);

		mpAnimator->GetStartEvent(ACIENT_BOSS_SUPER_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationSuperAttackStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_SUPER_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationSuperAttackComplete, this);

		mpAnimator->GetStartEvent(ACIENT_BOSS_DIE_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationDieStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_DIE_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationDieComplete, this);
	}
#pragma endregion




}