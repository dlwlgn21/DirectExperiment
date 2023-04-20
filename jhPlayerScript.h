#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"

static constexpr const UCHAR INITIAL_HP = 10;
static constexpr const UCHAR INITIAL_STAMINA = 5;

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
			UCHAR HP;
			UCHAR Stamina;
			PlayerStat()
				: HP(INITIAL_HP)
				, Stamina(INITIAL_STAMINA)
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

		void AttackAnimationComplete();
		void DashAnimationComplete();
		void HitAnimationComplete();

		eObjectLookDirection GetPlayerLookDirection() const { return meLookDir; }


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
	private:
		Transform*						mpTranform;
		Animator*						mpAnimator;
		float							mSpeed;
		const std::wstring				mAnimIdleKey;
		const std::wstring				mAnimMoveKey;
		const std::wstring				mAnimAttackKey;
		const std::wstring				mAnimDashKey;
		const std::wstring				mAnimHittedKey;
		eObjectLookDirection			meLookDir;
		ePlayerState					meState;

		PlayerStat						mStat;
	};
}

