#pragma once
#include "jhMonsterScript.h"

namespace jh
{
	enum class eBossMonsterState
	{
		IDLE,
		MOVING,
		TURNING_TO_LEFT,
		TURNING_TO_RIGHT,
		MELLE_ATTACKING,
		SPIN_ATTACKING,
		SPIN_END,
		RANGE_ATTACKING,
		BUFF,
		SUPER_ATTACKING,
		DEATH,
		COUNT
	};

	class AcientBossScript final : public Script
	{
	public:
		AcientBossScript(PlayerScript* pPlayerScript);
		virtual ~AcientBossScript() = default;

		void Initialize() override;
		void Update() override;

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

		static const std::wstring ACIENT_BOSS_IDLE_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_MOVING_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_TURN_LEFT_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_TURN_RIGHT_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_MELLE_ATTACK_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_SPIN_ATTACK_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_SPIN_END_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_RANGE_ATTACK_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_BUFF_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_SUPER_ATTACK_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_HITTED_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_DIE_ANIM_KEY;



	private:
		void setAnimKey();
	private:
		Transform*						mpTranform;
		Transform*						mpPlayerTransform;
		Animator*						mpAnimator;
		HitEffectScript*				mpEffectScript;
		int								mMaxHP;
		int								mCurrHP;
		float							mSpeed;
		float							mSpawningTimer;
		eObjectLookDirection			meLookDir;
		PlayerScript*					mpPlayerScript;
		eMonsterType					meMonsterType;
	};

}

