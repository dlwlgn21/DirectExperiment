#include "jhBossMonster.h"
#include "jhSpriteRenderer.h"
#include "jhMath.h"
#include "jhResourcesManager.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhResourceMaker.h"
#include "jhCollider2D.h"
#include "jhHitEffectObject.h"
#include "jhHitEffectScript.h"
#include "jhTransform.h"
#include "jhUIBarObject.h"
#include "jhAcientBossMonsterScript.h"
#include "jhAcientBossMonsterAttackColiderObject.h"
#include "jhAcientBossMonsterAttackColiderScript.h"

namespace jh
{

	BossMonster::BossMonster(AcientBossMonsterInfo& monsterInfo)
		: Monster()
		, mBossMonsterInfo(monsterInfo)
	{
		this->AddComponent(monsterInfo.pAnimator);
		this->AddComponent(new SpriteRenderer(monsterInfo.pMesh, monsterInfo.pMaterial));
		this->AddScript(new AcientBossMonsterScript(monsterInfo.pPlayerScript));

		for (UINT i = 0; i < static_cast<UINT>(eBossMonsterColliderType::COUNT); ++i)
		{
			assert(mBossMonsterInfo.pMonsterAttackColiderObject[i] != nullptr);
		}

		monsterInfo.pMonsterAttackColiderObject[static_cast<UINT>(eBossMonsterColliderType::MELEE_ATTACK)]->AddScript(
			new AcientBossMonsterAttackColiderScript(
				static_cast<Collider2D*>(this->GetComponentOrNull(eComponentType::COLLIDER)), 
				this->GetTransform(), 
				static_cast<AcientBossMonsterScript*>(this->GetScriptOrNull()), 
				monsterInfo.pAnimator,
				eBossMonsterColliderType::MELEE_ATTACK)
		);

		monsterInfo.pMonsterAttackColiderObject[static_cast<UINT>(eBossMonsterColliderType::SPIN_ATTACK)]->AddScript(
			new AcientBossMonsterAttackColiderScript(
				static_cast<Collider2D*>(this->GetComponentOrNull(eComponentType::COLLIDER)),
				this->GetTransform(),
				static_cast<AcientBossMonsterScript*>(this->GetScriptOrNull()),
				monsterInfo.pAnimator,
				eBossMonsterColliderType::SPIN_ATTACK)
		);

		monsterInfo.pMonsterAttackColiderObject[static_cast<UINT>(eBossMonsterColliderType::RANGE_ATTACK)]->AddScript(
			new AcientBossMonsterAttackColiderScript(
				static_cast<Collider2D*>(this->GetComponentOrNull(eComponentType::COLLIDER)),
				this->GetTransform(),
				static_cast<AcientBossMonsterScript*>(this->GetScriptOrNull()),
				monsterInfo.pAnimator,
				eBossMonsterColliderType::RANGE_ATTACK)
		);

		monsterInfo.pMonsterAttackColiderObject[static_cast<UINT>(eBossMonsterColliderType::SUPER_ATTACK)]->AddScript(
			new AcientBossMonsterAttackColiderScript(
				static_cast<Collider2D*>(this->GetComponentOrNull(eComponentType::COLLIDER)),
				this->GetTransform(),
				static_cast<AcientBossMonsterScript*>(this->GetScriptOrNull()),
				monsterInfo.pAnimator,
				eBossMonsterColliderType::SUPER_ATTACK)
		);

	}
	void BossMonster::SetHitEffectObject(HitEffectObject* pHitEffectObject)
	{
		mBossMonsterInfo.pHitEffectObject = pHitEffectObject;
	}
	void BossMonster::SetBossUIHpBarObject(UIBarObject* pUIBarObejct)
	{
		assert(pUIBarObejct != nullptr);
		mBossMonsterInfo.pUIBarObejct = pUIBarObejct;
	}
	void BossMonster::SetInactive()
	{
		assert(mBossMonsterInfo.pHitEffectObject != nullptr);
		this->SetState(eGameObjectState::INACTIVE);
		mBossMonsterInfo.pHitEffectObject->SetState(eGameObjectState::INACTIVE);
		for (UINT i = 0; i < static_cast<UINT>(eBossMonsterColliderType::COUNT); ++i)
		{
			mBossMonsterInfo.pMonsterAttackColiderObject[i]->SetState(eGameObjectState::INACTIVE);
		}
		mBossMonsterInfo.pUIBarObejct->SetState(eGameObjectState::INACTIVE);
	}
}