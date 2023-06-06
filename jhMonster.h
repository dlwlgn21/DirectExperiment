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
		virtual ~Monster() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetHitEffectObject(HitEffectObject* pHitEffectObject);
		void SetInactive();
		void SetActive();
		void SetMonsterAttackCollider(MonsterAttackColiderObject* pAttackColider) { assert(pAttackColider != nullptr); mMonsterInfo.pMonsterAttackColiderObject = pAttackColider; };
	private:
		void setAnimator();
		void setRenderer();
		void setHitColliderCenterPos(Collider2D* pCollider, const float xAdjustPos = 0.0f, const float yAdjustPos = 0.0f);
		void setHitCollider();
		
		void setScript();


	private:
		MonsterInfo				mMonsterInfo;
	};
}

