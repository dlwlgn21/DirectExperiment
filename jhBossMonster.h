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
	};

	class BossMonster final : public Monster
	{
	public:
		BossMonster(AcientBossMonsterInfo& monsterInfo);
		virtual ~BossMonster() = default;

	private:
		AcientBossMonsterInfo mBossMonsterInfo;
	};
}