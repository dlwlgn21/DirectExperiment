#include "jhAcientBossMonsterScript.h"
#include "jhAnimator.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"
#include "jhTime.h"

static constexpr UINT ACIENT_BOSS_INITIAL_HP = 30;
static constexpr float ACIENT_BOSS_INITIAL_SPEED = 1.0f;
static constexpr const float SPAWNING_TIME = 3.0f;
static constexpr const float MELEE_ATTACK_AWARENESS_RANGE = 2.0f;


namespace jh
{
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_IDLE_ANIM_KEY				= L"Idle";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_MOVING_ANIM_KEY			= L"Moving";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_TURN_LEFT_ANIM_KEY			= L"TurnLeft";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_TURN_RIGHT_ANIM_KEY		= L"TurnRight";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_MELLE_ATTACK_ANIM_KEY		= L"MelleAttack";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_SPIN_ATTACK_ANIM_KEY		= L"SpinAttack";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_SPIN_END_ANIM_KEY			= L"SpinEnd";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_RANGE_ATTACK_ANIM_KEY		= L"RangeAttack";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_BUFF_ANIM_KEY				= L"Buff";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_SUPER_ATTACK_ANIM_KEY		= L"SuperAttack";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_HITTED_ANIM_KEY			= L"Hitted";
	const std::wstring AcientBossMonsterScript::ACIENT_BOSS_DIE_ANIM_KEY				= L"Die";


	AcientBossMonsterScript::AcientBossMonsterScript(PlayerScript* pPlayerScript)
		: MonsterScript()
		, mpTranform(nullptr)
		, mpPlayerTransform(nullptr)
		, mpAnimator(nullptr)
		, mpEffectScript(nullptr)
		, mMaxHP(ACIENT_BOSS_INITIAL_HP)
		, mCurrHP(ACIENT_BOSS_INITIAL_HP)
		, mSpeed(ACIENT_BOSS_INITIAL_SPEED)
		, mSpawningTimer(SPAWNING_TIME)
		, meLookDir(eObjectLookDirection::LEFT)
		, mpPlayerScript(pPlayerScript)
		, meMonsterType(eMonsterType::LV_1_ACIENT_BOSS)
		, meState(eBossMonsterState::TRACING)
		, mePhase(eBossMonsterPhase::LV_1_PHASE)
	{
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

		if (std::abs(distanceFromPlayer) < MELEE_ATTACK_AWARENESS_RANGE && meState != eBossMonsterState::MELLE_ATTACKING)
		{
			setState(eBossMonsterState::MELLE_ATTACKING);
			if (meLookDir == eObjectLookDirection::LEFT)
			{
				meLookDir = eObjectLookDirection::RIGHT;
			}
			else
			{
				meLookDir = eObjectLookDirection::LEFT;
			}
			return;
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
		case eBossMonsterState::TURNING_TO_LEFT:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_TURN_LEFT_ANIM_KEY, true);
			break;
		}
		case eBossMonsterState::TURNING_TO_RIGHT:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_TURN_RIGHT_ANIM_KEY, true);
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
		case eBossMonsterState::SPIN_END:
		{
			mpAnimator->PlayAnimation(ACIENT_BOSS_SPIN_END_ANIM_KEY, true);
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
	void AcientBossMonsterScript::AnimationTurnLeftStart()
	{

	}
	void AcientBossMonsterScript::AnimationTurnLeftComplete()
	{

	}
	void AcientBossMonsterScript::AnimationTurnRightStart()
	{

	}
	void AcientBossMonsterScript::AnimationTurnRightComplete()
	{

	}
	void AcientBossMonsterScript::AnimationMelleAttackStart()
	{

	}
	void AcientBossMonsterScript::AnimationMelleAttackComplete()
	{
		setState(eBossMonsterState::TRACING);
	}
	void AcientBossMonsterScript::AnimationSpinAttackStart()
	{

	}
	void AcientBossMonsterScript::AnimationSpinAttackComplete()
	{

	}
	void AcientBossMonsterScript::AnimationSpinEndStart()
	{

	}
	void AcientBossMonsterScript::AnimationSpinEndComplete()
	{

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

		mpAnimator->GetStartEvent(ACIENT_BOSS_TURN_LEFT_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationTurnLeftStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_TURN_LEFT_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationTurnLeftComplete, this);

		mpAnimator->GetStartEvent(ACIENT_BOSS_TURN_RIGHT_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationTurnRightStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_TURN_RIGHT_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationTurnRightComplete, this);

		mpAnimator->GetStartEvent(ACIENT_BOSS_MELLE_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationMelleAttackStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_MELLE_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationMelleAttackComplete, this);

		mpAnimator->GetStartEvent(ACIENT_BOSS_SPIN_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationSpinAttackStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_SPIN_ATTACK_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationSpinAttackComplete, this);

		mpAnimator->GetStartEvent(ACIENT_BOSS_SPIN_END_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationSpinEndStart, this);
		mpAnimator->GetCompleteEvent(ACIENT_BOSS_SPIN_END_ANIM_KEY) = std::bind(&AcientBossMonsterScript::AnimationSpinEndComplete, this);

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