#pragma once
#include "jhGameObject.h"
#include "jhMonsterManager.h"

namespace jh
{
	class PlayerScript;
	class HitEffectObject;
	class Mesh;
	class Material;
	class Animator;
	struct MonsterInfo
	{
		HitEffectObject*	pHitEffectObject;
		PlayerScript*		pPlayerScript;
		Mesh*				pMesh;
		Material*			pMaterial;
		Animator*			pAnimator;
		eMonsterType		eMonType;
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


	private:
		void setAnimator();
		void setRenderer();
		void setHitCollider();
		void setScript();

	private:
		MonsterInfo				mMonsterInfo;
	};
}

