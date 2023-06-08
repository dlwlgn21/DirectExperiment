#include "jhBossMonsterScript.h"

static constexpr UINT ACIENT_BOSS_INITIAL_HP = 30;
static constexpr float ACIENT_BOSS_INITIAL_SPEED = 1.0f;
static constexpr const float SPAWNING_TIME = 3.0f;

namespace jh
{
	const std::wstring AcientBossScript::ACIENT_BOSS_IDLE_ANIM_KEY				= L"Idle";
	const std::wstring AcientBossScript::ACIENT_BOSS_MOVING_ANIM_KEY			= L"Moving";
	const std::wstring AcientBossScript::ACIENT_BOSS_TURN_LEFT_ANIM_KEY			= L"TurnLeft";
	const std::wstring AcientBossScript::ACIENT_BOSS_TURN_RIGHT_ANIM_KEY		= L"TurnRight";
	const std::wstring AcientBossScript::ACIENT_BOSS_MELLE_ATTACK_ANIM_KEY		= L"MelleAttack";
	const std::wstring AcientBossScript::ACIENT_BOSS_SPIN_ATTACK_ANIM_KEY		= L"SpinAttack";
	const std::wstring AcientBossScript::ACIENT_BOSS_SPIN_END_ANIM_KEY			= L"SpinEnd";
	const std::wstring AcientBossScript::ACIENT_BOSS_RANGE_ATTACK_ANIM_KEY		= L"RangeAttack";
	const std::wstring AcientBossScript::ACIENT_BOSS_BUFF_ANIM_KEY				= L"Buff";
	const std::wstring AcientBossScript::ACIENT_BOSS_SUPER_ATTACK_ANIM_KEY		= L"SuperAttack";
	const std::wstring AcientBossScript::ACIENT_BOSS_HITTED_ANIM_KEY			= L"Hitted";
	const std::wstring AcientBossScript::ACIENT_BOSS_DIE_ANIM_KEY				= L"Die";


	AcientBossScript::AcientBossScript(PlayerScript* pPlayerScript)
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

	void AcientBossScript::Initialize()
	{
	}
	void AcientBossScript::Update()
	{

	}

	void AcientBossScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{
	}
	void AcientBossScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
	}
	void AcientBossScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
}