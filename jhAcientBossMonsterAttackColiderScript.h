#pragma once
#include "jhScript.h"
#include "jhMath.h"
#include "jhMonsterManager.h"

namespace jh
{
	enum class eBossMonsterColliderType
	{
		MELEE_ATTACK,
		RANGE_ATTACK,
		SPIN_ATTACK,
		SUPER_ATTACK,
		COUNT
	};


	class Transform;
	class Collider2D;
	class AcientBossMonsterScript;
	class Animator;
	class PlayerScript;
	class AcientBossMonsterAttackColiderScript : public Script
	{
	public:
		AcientBossMonsterAttackColiderScript(Collider2D* pCollider, Transform* pMonsterTransform, AcientBossMonsterScript* pMonsterScript, Animator* pAnimator, const eBossMonsterColliderType eCollderType);
		virtual ~AcientBossMonsterAttackColiderScript() = default;


		void Initialize() override;
		void Update() override;


		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

	private:
		void setPosByMonsterLookDirectionAndMonsterState();
		void damageToPlayer(PlayerScript* pPlayerScript, const UINT damage);

	private:
		Collider2D*					mpCollider;
		Transform*					mpTransform;
		Transform*					mpMonsterTransform;
		AcientBossMonsterScript*	mpMonsterScript;
		Animator*					mpAnimator;
		eObjectLookDirection		meLookDir;
		float						mDistanceFormHitCollider;
		float						mTracingStateColliderYPos;
		eBossMonsterColliderType	meAttackType;
	};
}

