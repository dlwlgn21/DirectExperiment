#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"
#include "jhPlayerLevelManager.h"

static constexpr const int		INITIAL_HP = 10;
static constexpr const int		INITIAL_STAMINA = 5;
static constexpr const int		INITIAL_ATTACK_DAMAGE = 3;

static constexpr const int		ATTACK_STAMINA_COST = 1;
static constexpr const int		DASH_STAMINA_COST = 1;

static constexpr const int 		STAMINA_RECOVER_AMOUNT = 1;
static constexpr const float 	STAMINA_RECOVER_SECOND = 2.0f;

namespace jh
{
	enum class ePlayerState
	{
		IDLE,
		MOVING,
		ATTACKING,
		ROLLING,
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
	class PlayerHitEffectScript;
	class PlayerScript final : public Script
	{
	public:
		friend class PlayerLevelManager;

		struct PlayerStat
		{
			int MaxHP;
			int MaxStamina;
			int CurrentHP;
			int CurrentStamina;
			UINT CurrEXP;
			UINT CurrLevel;
			int AttackDamage;
			PlayerStat()
				: MaxHP(INITIAL_HP)
				, MaxStamina(INITIAL_STAMINA)
				, CurrentHP(INITIAL_HP)
				, CurrentStamina(INITIAL_STAMINA)
				, AttackDamage(INITIAL_ATTACK_DAMAGE)
				, CurrEXP(0)
			    , CurrLevel(1)
			{
			}
		};
		struct ElectricBeam
		{
			bool bIsSpawnBeam;
			UINT CurrElectricBeamDamageLevel;
			UINT CurrElectricBeamSpawnSpeedLevel;
		};
		struct ElectricStrike
		{
			bool bIsSpawnStrike;
			UINT CurrElectricStrikeDamageLevel;
			UINT CurrElectricStrikeSpawnSpeedLevel;
		};
		struct ElectricTornado
		{
			bool bIsSpawnTornado;
			UINT CurrElectricTornadoSpawnSpeedLevel;
		};

		struct PlayerSkillStat
		{
			ElectricBeam ElectricBeamLevel;
			ElectricStrike ElectricStrikeLevel;
			ElectricTornado ElectricTornadoLevel;
			UINT CurrSwordLevel;
			UINT CurrMovementSpeedLevel;
			PlayerSkillStat()
				: ElectricBeamLevel{ 0, }
				, ElectricStrikeLevel{ 0, }
				, ElectricTornadoLevel{ 0, }
				, CurrSwordLevel(0)
				, CurrMovementSpeedLevel(0)
			{
			}
		};

		PlayerScript();
		~PlayerScript() = default;

		void Initialize() override;
		void Update() override;

#pragma region ANIMATION_EVENT
		void IdleAnimStart();

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

		void RollingAnimationStart();
		void RollingAnimationComplete();

		void HitAnimationComplete();
#pragma endregion
#pragma region COLLISION_TRIGGER
		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;
#pragma endregion

		eObjectLookDirection GetPlayerLookDirection() const			{ return meLookDir; }
		const ePlayerState GetPlayerState() const					{ return meState; }
		const eComboAttackType GetComboAttackType() const			{ return meComboType; }
		const PlayerStat& GetPlayerStat()	const					{ return mStat; }
		const PlayerSkillStat& GetPlayerSkillStat() const			{ return mSkillStat; }
		eAttackType GetAttackType() const							{ return meAttackType; }
		const bool IsHitAttack() const								{ return mbIsHitAttack; }
		const bool IsHitSkillAtack() const							{ return mbIsHitSkillAtack; }
		
		

		void IncreaseEXP(const UINT exp);
		void EnemyAttackHiited(UINT damage);
		void SetPlayerDustEffectScript(PlayerDustEffectScript* pPlayerDustEffectScript) { assert(pPlayerDustEffectScript != nullptr); mpPlayerDustEffetScript = pPlayerDustEffectScript; }
		void SetPlayerHitEffectScript(PlayerHitEffectScript* pPlayerHitEffectScript) { assert(pPlayerHitEffectScript != nullptr); mpPlayerHitEffectScript = pPlayerHitEffectScript; }
		void SetIsHitAttack(const bool bIsHit)										{ mbIsHitAttack = bIsHit; }
		void SetIsHitSkillAttack(const bool bIsHit)									{ mbIsHitSkillAtack = bIsHit; }
	
	private:
		void setXPosByComboAttackType(float& xPos);
		void setPosByLookDirection(float& xPos, const float xDistance);
		void processIfDash(float& xPos);
		void processIfRolling(float& xPos);

		void setStateByInput(float& xPos);
		void setAnimationEvent();
		void setState(const ePlayerState eState);
		void setAttackType(const eAttackType eType);
		void setComboType(const eComboAttackType eType);
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
		const std::wstring				mAnimRollingKey;
		eObjectLookDirection			meLookDir;
		ePlayerState					meState;
		eAttackType						meAttackType;
		eComboAttackType				meComboType;
		PlayerStat						mStat;
		PlayerSkillStat					mSkillStat;
		float							mStaminaTimer;
		PlayerDustEffectScript*			mpPlayerDustEffetScript;
		PlayerHitEffectScript*			mpPlayerHitEffectScript;
		bool							mbIsContiueAttacking;
		bool							mbIsHitAttack;
		bool							mbIsHitSkillAtack;
		bool							mbIsStartCountingDashTimer;
		bool							mbIsStartCountingRollingTimer;

		float							mDashIntervalTimer;
		float							mDashIntervalTime;

		float							mRollingIntervalTimer;
		float							mRollingIntervalTime;

		UINT							mCurrentLevelExpToLevelUP;
	};
}

