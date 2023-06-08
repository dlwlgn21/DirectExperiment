#include "jhAcientBossMonsterAttackColiderObject.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhMonsterAttackColiderScript.h"
#include "jhAcientBossMonsterScript.h"

static const jh::math::Vector2 DEFULAT_SIZE(2.0f, 1.0f);

namespace jh
{
	AcientBossMonsterAttackColiderObject::AcientBossMonsterAttackColiderObject(const eBossMonsterColliderType eAttackColliderType)
		: GameObject(eLayerType::MONSTER)
		, meAttackColliderType(eAttackColliderType)
	{
		Collider2D* pCollider = new Collider2D(eColliderLayerType::MONSTER_WEAPON);
		AddComponent(pCollider);
		pCollider->SetSize(DEFULAT_SIZE);
	}

	void AcientBossMonsterAttackColiderObject::SetMonsterTransformAndScriptAndAnimator(Transform* pMonsterTransform, AcientBossMonsterScript* pAcientBossMonsterScript, Animator* pAnimator)
	{
		assert(pMonsterTransform != nullptr && pAcientBossMonsterScript != nullptr && pAnimator != nullptr);
		AcientBossMonsterAttackColiderScript* pScript = new AcientBossMonsterAttackColiderScript(static_cast<Collider2D*>(GetComponentOrNull(eComponentType::COLLIDER)), pMonsterTransform, pAcientBossMonsterScript, pAnimator, meAttackColliderType);
		this->AddScript(pScript);
	}
}