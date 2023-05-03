#pragma once
#include "jhScript.h"
#include "jhMath.h"
#include "jhMonsterManager.h"

namespace jh
{

	class Transform;
	class Collider2D;
	class MonsterScript;
	class Animator;
	class PlayerScript;
	class MonsterAttackColiderScript : public Script
	{
	public:
		MonsterAttackColiderScript(Collider2D* pCollider, Transform* pMonsterTransform, MonsterScript* pMonsterScript, Animator* pAnimator);
		virtual ~MonsterAttackColiderScript() = default;


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
		MonsterScript*				mpMonsterScript;
		Animator*					mpAnimator;
		eObjectLookDirection		meLookDir;
		eMonsterType				meMonsterType;
	};
}

