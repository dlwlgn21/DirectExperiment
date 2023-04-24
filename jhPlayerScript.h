#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"

static constexpr const CHAR		INITIAL_HP = 10;
static constexpr const CHAR		INITIAL_STAMINA = 5;

static constexpr const CHAR		ATTACK_STAMINA_COST = 2;
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


	class Animator;
	class Transform;
	class Collider2D;
	class PlayerScript final : public Script
	{
	public:
		struct PlayerStat
		{
			CHAR MaxHP;
			CHAR MaxStamina;
			CHAR CurrentHP;
			CHAR CurrentStamina;
			PlayerStat()
				: MaxHP(INITIAL_HP)
				, MaxStamina(INITIAL_STAMINA)
				, CurrentHP(INITIAL_HP)
				, CurrentStamina(INITIAL_STAMINA)
			{
			}
		};

		PlayerScript();
		virtual ~PlayerScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void Start();
		void Complete();
		void End();

		void AttackAnimationStart();
		void AttackAnimationComplete();

		void PushAttackAnimationStart();
		void PushAttackAnimationComplete();

		void DashAnimationStart();
		void DashAnimationComplete();
		void HitAnimationComplete();

		const eObjectLookDirection GetPlayerLookDirection() const	{ return meLookDir; }
		const ePlayerState GetPlayerState() const					{ return meState; }
		const PlayerStat& GetPlayerStat()	const					{ return mStat; }

		void OnCollisionEnter(Collider2D* pOtherCollider) override;
		void OnCollisionStay(Collider2D* pOtherCollider) override;
		void OnCollisionExit(Collider2D* pOtherCollider) override;

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;



	private:
		void setAnimationEvent();
		void setState(const ePlayerState eState);
		void setStateByInput(jh::math::Vector3& pos);
		void setAnimationFlip();
		void setAnimatorByState();
		void recoverStamina();
		void decreaseStamina(CHAR amount);

	private:
		Transform*						mpTranform;
		Animator*						mpAnimator;
		float							mSpeed;
		const std::wstring				mAnimIdleKey;
		const std::wstring				mAnimMoveKey;
		const std::wstring				mAnimAttackKey;
		const std::wstring				mAnimPushAttackKey;
		const std::wstring				mAnimDashKey;
		const std::wstring				mAnimHittedKey;
		eObjectLookDirection			meLookDir;
		ePlayerState					meState;

		PlayerStat						mStat;

		float							mStaminaTimer;
	};
}

