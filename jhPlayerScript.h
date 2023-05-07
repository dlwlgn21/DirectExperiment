#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"

static constexpr const CHAR		INITIAL_HP = 10;
static constexpr const CHAR		INITIAL_STAMINA = 5;
static constexpr const CHAR		INITIAL_ATTACK_DAMAGE = 1;

static constexpr const CHAR		ATTACK_STAMINA_COST = 1;
static constexpr const CHAR		DASH_STAMINA_COST = 1;

static constexpr const float 	STAMINA_RECOVER_SECOND = 2.0f;
static constexpr const CHAR 	STAMINA_RECOVER_AMOUNT = 1;

namespace jh
{
	enum class ePlayerState
	{
		IDLE,
		MOVING,
		ATTACKING,
		DASH,
		HITTED,
		DEAD,
		COUNT
	};

	enum class eAttackType
	{
		NORMAL,
		PUSH,
		COUNT
	};

	enum class eComboAttackType
	{
		ONE,
		TWO,
		THREE,
		COUNT
	};

	class Animator;
	class Transform;
	class Collider2D;
	class PlayerDustEffectScript;
	class PlayerScript final : public Script
	{
	public:
		struct PlayerStat
		{
			CHAR MaxHP;
			CHAR MaxStamina;
			CHAR CurrentHP;
			CHAR CurrentStamina;
			CHAR AttackDamage;
			PlayerStat()
				: MaxHP(INITIAL_HP)
				, MaxStamina(INITIAL_STAMINA)
				, CurrentHP(INITIAL_HP)
				, CurrentStamina(INITIAL_STAMINA)
				, AttackDamage(INITIAL_ATTACK_DAMAGE)
			{
			}
		};

		PlayerScript();
		virtual ~PlayerScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void AttackOneAnimationStart();
		void AttackOneAnimationComplete();
		
		void AttackTwoAnimationStart();
		void AttackTwoAnimationComplete();

		void AttackThreeAnimationStart();
		void AttackThreeAnimationComplete();


		void PushAttackAnimationStart();
		void PushAttackAnimationComplete();

		void DashAnimationStart();
		void DashAnimationComplete();
		void HitAnimationComplete();

		eObjectLookDirection GetPlayerLookDirection() const			{ return meLookDir; }
		const ePlayerState GetPlayerState() const					{ return meState; }
		const eComboAttackType GetComboAttackType() const			{ return meComboType; }
		const PlayerStat& GetPlayerStat()	const					{ return mStat; }
		eAttackType GetAttackType() const							{ return meAttackType; }
		const bool IsHitPowerAttack() const							{ return mbIsHitPowerAttack; }

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

		void EnemyAttackHiited(UINT damage);


		void SetPlayerDustEffectScript(PlayerDustEffectScript* pPlayerDustEffectScript) { assert(pPlayerDustEffectScript != nullptr); mpPlayerDustEffetScript = pPlayerDustEffectScript; }
		void SetIsHitPowerAttack(const bool bIsHit)										{ mbIsHitPowerAttack = bIsHit; }
	
	private:
		void setAnimationEvent();
		void setState(const ePlayerState eState);
		void setAttackType(const eAttackType eType);
		void setComboType(const eComboAttackType eType);
		void setStateByInput(jh::math::Vector3& pos);
		void setAnimationFlip();
		void setAnimatorByState();
		void recoverStamina();
		void decreaseStamina(CHAR amount);
		void decreaseHP(CHAR amount);
		bool checkIsNormalAttackKeyPressed();
		void setIsContinueAttacking();

	private:
		Transform*						mpTranform;
		Animator*						mpAnimator;
		float							mSpeed;
		const std::wstring				mAnimIdleKey;
		const std::wstring				mAnimMoveKey;
		const std::wstring				mAnimNormalAttack1Key;
		const std::wstring				mAnimNormalAttack2Key;
		const std::wstring				mAnimNormalAttack3Key;
		const std::wstring				mAnimPushAttackKey;
		const std::wstring				mAnimDashKey;
		const std::wstring				mAnimHittedKey;
		eObjectLookDirection			meLookDir;
		ePlayerState					meState;
		eAttackType						meAttackType;
		eComboAttackType				meComboType;
		PlayerStat						mStat;
		float							mStaminaTimer;
		PlayerDustEffectScript*			mpPlayerDustEffetScript;
		bool							mbIsContiueAttacking;
		bool							mbIsHitPowerAttack;
		float							mDashIntervalTimer;
		float							mDashIntervalTime;
	};
}

