#pragma once
#include "jhScript.h"
#include "jhMath.h"

namespace jh
{
	enum class eWeponCoilderTimerState
	{
		WAITING,
		START_TIME_COUNTING,
		COLIDER_CHECK_TIME_COUNTING,
		COUNT
	};
	class Transform;
	class Collider2D;
	class WeaponColliderScript : public Script
	{
	public:
		WeaponColliderScript(Collider2D* pCollider, Transform* pPlayerTransform);
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
		void changeState(const eWeponCoilderTimerState eState) { meState = eState; }
	private:
		Collider2D*					mpCollider;
		float						mColliderDurationTimer;
		float						mColliderStartTimer;
		float						mSpeed;
		eWeponCoilderTimerState		meState;
		Transform*					mpTransform;
		Transform*					mpPlayerTransform;
		eObjectLookDirection		meLookDir;
	};
}

