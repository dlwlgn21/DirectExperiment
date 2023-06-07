#include "jhMonsterAttackColiderObject.h"
#include "jhTransform.h"
#include "jhMonsterScript.h"
#include "jhCollider2D.h"
#include "jhMonsterAttackColiderScript.h"

static const jh::math::Vector2 DEFULAT_SIZE(2.0f, 1.0f);

namespace jh
{
	MonsterAttackColiderObject::MonsterAttackColiderObject()
		: GameObject(eLayerType::MONSTER)
	{
		Collider2D* pCollider = new Collider2D(eColliderLayerType::MONSTER_WEAPON);
		AddComponent(pCollider);
		pCollider->SetSize(DEFULAT_SIZE);
	}

	void MonsterAttackColiderObject::SetMonsterTransformAndScriptAndAnimator(Transform* pMonsterTransform, MonsterScript* pMonsterScript, Animator* pAnimator)
	{
		assert(pMonsterTransform != nullptr && pMonsterScript != nullptr && pAnimator != nullptr);
		MonsterAttackColiderScript* pScript = new MonsterAttackColiderScript(static_cast<Collider2D*>(GetComponentOrNull(eComponentType::COLLIDER)), pMonsterTransform, pMonsterScript, pAnimator);
		AddScript(pScript);
	}
}
