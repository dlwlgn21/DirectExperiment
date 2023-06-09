#pragma once
#include "jhGameObject.h"

namespace jh
{
	class PlayerScript;
	class HitEffectObject;
	class Mesh;
	class Material;
	class Animator;
	class MonsterAttackColiderObject;
	class Collider2D;
	class AcientBossMonsterAttackColiderObject;

	struct MonsterInfo
	{
		HitEffectObject*			pHitEffectObject;
		PlayerScript*				pPlayerScript;
		Mesh*						pMesh;
		Material*					pMaterial;
		Animator*					pAnimator;
		MonsterAttackColiderObject* pMonsterAttackColiderObject;
		eMonsterType				eMonType;
	};

	class Monster : public GameObject
	{
	public:
		Monster(MonsterInfo& monsterInfo);
		Monster();
		virtual ~Monster() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		virtual void SetHitEffectObject(HitEffectObject* pHitEffectObject);
		virtual void SetInactive();

		void SetActive();
		void SetMonsterAttackCollider(MonsterAttackColiderObject* pAttackColider) { assert(pAttackColider != nullptr); mMonsterInfo.pMonsterAttackColiderObject = pAttackColider; };
	
	protected:
		void setRenderer();
		void setHitColliderCenterPos(Collider2D* pCollider, const float xAdjustPos = 0.0f, const float yAdjustPos = 0.0f);
		void setAnimator();
		void setHitCollider();
		void setScript();

	protected:
		MonsterInfo				mMonsterInfo;
	};
}

