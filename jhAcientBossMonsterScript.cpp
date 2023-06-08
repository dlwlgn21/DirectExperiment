#include "jhAcientBossMonsterScript.h"
#include "jhAnimator.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"
#include "jhTime.h"
#include "jhCollider2D.h"
#include <random>
static constexpr const UINT PLAYER_VAILED_ATTACK_ANIMATION_INDEX = 1;

static constexpr const float INVINCIBILITY_TIME = 0.5f;
static constexpr const float MELEE_ATTACK_AWARENESS_RANGE = 2.0f;
static constexpr const UINT MELEE_ATTACK_NUMBER = 0;
static constexpr const UINT SPIN_ATTACK_NUMBER = 1;


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
	{
		mAttackingAwarenessRange = MELEE_ATTACK_AWARENESS_RANGE;
		mpPlayerScript = pPlayerScript;
		assert(mpPlayerScript != nullptr);
	}

	void AcientBossMonsterScript::Initialize()
	{
		setAnimationEvent();
		mpTranform = GetOwner()->GetTransform();
		assert(mpTranform != nullptr);
		assert(mpPlayerScript != nullptr);
		mpPlayerTransform = mpPlayerScript->GetOwner()->GetTransform();
		assert(mpPlayerTransform);
	}
	void AcientBossMonsterScript::Update()
	{
		assert(mpTranform != nullptr);

		float currPos = mpTranform->GetOnlyXPosition();
		float distanceFromPlayer = currPos - mpPlayerTransform->GetOnlyXPosition();
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
			if (std::abs(distanceFromPlayer) < MELEE_ATTACK_AWARENESS_RANGE &&
				meState != eBossMonsterState::MELLE_ATTACKING &&
				meState != eBossMonsterState::SPIN_ATTACKING)
			{
				if (sDist(sGen) == MELEE_ATTACK_NUMBER)
				{
					setState(eBossMonsterState::MELLE_ATTACKING);
					flipLookDirection();
				}
				else
				{
					setState(eBossMonsterState::SPIN_ATTACKING);
				}
				return;
			}

			break;
		}
		case eBossMonsterPhase::LV_2_PHASE:
		{

			break;
		}
		case eBossMonsterPhase::LV_3_PHASE:
		{

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

		setAnimaionFlip();
		playAnimation();
	}

	void AcientBossMonsterScript::playAnimation()
	{
		assert(mpAnimator != nullptr);
		switch (meState)
		{
		case eBossMonsterState::IDLE:
		{
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

#pragma region ANIMATION_EVENT
	void AcientBossMonsterScript::AnimationMovingStart()
	{

	}
	void AcientBossMonsterScript::AnimationMovingComplete()
	{

	}


	void AcientBossMonsterScript::AnimationMelleAttackStart()
	{

	}
	void AcientBossMonsterScript::AnimationMelleAttackComplete()
	{
		flipLookDirection();
		setState(eBossMonsterState::TRACING);
	}
	void AcientBossMonsterScript::AnimationSpinAttackStart()
	{

	}
	void AcientBossMonsterScript::AnimationSpinAttackComplete()
	{
		setState(eBossMonsterState::TRACING);
	}
	void AcientBossMonsterScript::AnimationRangeAttackStart()
	{

	}
	void AcientBossMonsterScript::AnimationRangeAttackComplete()
	{

	}
	void AcientBossMonsterScript::AnimationBuffStart()
	{

	}
	void AcientBossMonsterScript::AnimationBuffComplete()
	{

	}
	void AcientBossMonsterScript::AnimationSuperAttackStart()
	{

	}
	void AcientBossMonsterScript::AnimationSuperAttackComplete()
	{

	}
	void AcientBossMonsterScript::AnimationDieStart()
	{

	}
	void AcientBossMonsterScript::AnimationDieComplete()
	{

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