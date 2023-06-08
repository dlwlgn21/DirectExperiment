#include "jhAcientBossMonsterScript.h"
#include "jhAnimator.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"

static constexpr UINT ACIENT_BOSS_INITIAL_HP = 30;
static constexpr float ACIENT_BOSS_INITIAL_SPEED = 1.0f;
static constexpr const float SPAWNING_TIME = 3.0f;

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
		: Script()
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