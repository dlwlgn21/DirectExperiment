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

	class AcientBossMonsterScript final : public Script
	{
	public:
		AcientBossMonsterScript(PlayerScript* pPlayerScript);
		virtual ~AcientBossMonsterScript() = default;

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


#pragma region ANIMATION_EVENT
		void AnimationMovingStart();
		void AnimationMovingComplete();

		void AnimationTurnLeftStart();
		void AnimationTurnLeftComplete();

		void AnimationTurnRightStart();
		void AnimationTurnRightComplete();

		void AnimationMelleAttackStart();
		void AnimationMelleAttackComplete();

		void AnimationSpinAttackStart();
		void AnimationSpinAttackComplete();

		void AnimationSpinEndStart();
		void AnimationSpinEndComplete();

		void AnimationRangeAttackStart();
		void AnimationRangeAttackComplete();

		void AnimationBuffStart();
		void AnimationBuffComplete();

		void AnimationSuperAttackStart();
		void AnimationSuperAttackComplete();

		void AnimationDieStart();
		void AnimationDieComplete();
#pragma endregion




	private:
		void setAnimationEvent();
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

