#pragma once
#include "jhScript.h"
#include "jhMath.h"

namespace jh
{
	enum class eWeponCoilderTimerState
	{
		WAITING,
		START_TIME_COUNTING,
		COUNT
	};
	class EffectScript;
	class Transform;
	class Collider2D;
	class PlayerScript;
	class WeaponColliderScript : public Script
	{
	public:
		WeaponColliderScript(Collider2D* pCollider, Transform* pPlayerTransform, PlayerScript* pPlayerScript);
		virtual ~WeaponColliderScript() = default;


		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void Start();
		void Complete();
		void End();

		void OnCollisionEnter(Collider2D* pOtherCollider) override;
		void OnCollisionStay(Collider2D* pOtherCollider) override;
		void OnCollisionExit(Collider2D* pOtherCollider) override;

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;
		
	private:
		void setPosByPlayerLookDirection(jh::math::Vector3& pos);
		void setColliderStateByPlayerState();
		void changeState(const eWeponCoilderTimerState eState) { meState = eState; }

	private:
		Collider2D*					mpCollider;
		float						mColliderStartTimer;
		float						mSpeed;
		eWeponCoilderTimerState		meState;
		Transform*					mpTransform;
		Transform*					mpPlayerTransform;
		PlayerScript*				mpPlayerScript;
		eObjectLookDirection		meLookDir;
	};
}

