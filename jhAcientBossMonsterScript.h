#pragma once
#include "jhMonsterScript.h"

namespace jh
{
	enum class eBossMonsterState
	{
		IDLE,
		TRACING,
		MELLE_ATTACKING,
		SPIN_ATTACKING,
		RANGE_ATTACKING,
		BUFF,
		SUPER_ATTACKING,
		DEATH,
		COUNT
	};

	enum class eBossMonsterPhase
	{
		LV_1_PHASE,
		LV_2_PHASE,
		LV_3_PHASE,
		COUNT
	};
	class AcientBossMonsterScript final : public MonsterScript
	{
	public:
		AcientBossMonsterScript(PlayerScript* pPlayerScript);
		virtual ~AcientBossMonsterScript() = default;

		void Initialize() override;
		void Update() override;

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

		const eBossMonsterState	   GetState()			const { return meState; }
	public:
		static const std::wstring ACIENT_BOSS_IDLE_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_MOVING_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_MELLE_ATTACK_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_SPIN_ATTACK_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_RANGE_ATTACK_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_BUFF_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_SUPER_ATTACK_ANIM_KEY;
		static const std::wstring ACIENT_BOSS_DIE_ANIM_KEY;


#pragma region ANIMATION_EVENT
		void AnimationIdleStart();

		void AnimationMovingStart();
		void AnimationMovingComplete();


		void AnimationMelleAttackStart();
		void AnimationMelleAttackComplete();

		void AnimationSpinAttackStart();
		void AnimationSpinAttackComplete();

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
		void setState(const eBossMonsterState eState) { meState = eState; }
		void setPhaseState(const eBossMonsterPhase ePhase) { mePhase = ePhase; }
		void setAnimationEvent();
		void setAnimaionFlip();

		void playAnimation();
		void flipLookDirection();
		void playAttackingSFX();
	private:
		void decreaseHP(const int amount) override;

	private:
		eBossMonsterState				meState;
		eBossMonsterPhase				mePhase;
		float							mInvincibilityTimer;
		bool							mbIsCountingInvincibilityTime;
		bool							mbIsHittted;
		float							mAttackSFXTimer;
	};

}

