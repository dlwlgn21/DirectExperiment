#pragma once
#include "jhMonster.h"

namespace jh
{
	struct AcientBossMonsterInfo
	{
		HitEffectObject*						pHitEffectObject;
		PlayerScript*							pPlayerScript;
		Mesh*									pMesh;
		Material*								pMaterial;
		Animator*								pAnimator;
		AcientBossMonsterAttackColiderObject*	pMonsterAttackColiderObject[4];
		eMonsterType							eMonType;
		UIBarObject*							pUIBarObejct;
	};

	class BossMonster final : public Monster
	{
	public:
		BossMonster(AcientBossMonsterInfo& monsterInfo);
		virtual ~BossMonster() = default;

		void SetInactive() override;
		void SetHitEffectObject(HitEffectObject* pHitEffectObject) override;
		void SetBossUIHpBarObject(UIBarObject* pUIBarObejct);
	private:
		AcientBossMonsterInfo mBossMonsterInfo;
	};
}