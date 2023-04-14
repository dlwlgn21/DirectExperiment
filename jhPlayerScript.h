#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"

static constexpr const UCHAR INITIAL_HP = 10;
static constexpr const UCHAR INITIAL_STAMINA = 5;

namespace jh
{

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

		eAnimatedObjectLookDirection GetPlayerLookDirection() const { return meLookDir; }


		void OnCollisionEnter(Collider2D* pOtherCollider) override;
		void OnCollisionStay(Collider2D* pOtherCollider) override;
		void OnCollisionExit(Collider2D* pOtherCollider) override;

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

	private:
		Transform*						mpTranform;
		Animator*						mpAnimator;
		float							mSpeed;
		const std::wstring				mAnimIdleKey;
		const std::wstring				mAnimMoveKey;
		const std::wstring				mAnimWeaponSwingKey;
		const std::wstring				mAnimHittedKey;
		bool							mbIsMoving;
		bool							mbIsAttacking;
		eAnimatedObjectLookDirection    meLookDir;

		PlayerStat						mStat;

	};
}

