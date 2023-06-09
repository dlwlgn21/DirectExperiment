#include "jhAcientBossMonsterAttackColiderObject.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhMonsterAttackColiderScript.h"
#include "jhAcientBossMonsterScript.h"

static const jh::math::Vector2 MELLE_ATTACK_SIZE(1.0f, 0.3f);
static const jh::math::Vector2 SPIN_ATTACK_SIZE(4.0f, 0.5f);
static const jh::math::Vector2 RANGE_ATTACK_SIZE(3.0f, 0.3f);
static const jh::math::Vector2 SUPER_ATTACK_SIZE(3.5f, 1.0f);

namespace jh
{
	AcientBossMonsterAttackColiderObject::AcientBossMonsterAttackColiderObject(const eBossMonsterColliderType eAttackColliderType)
		: GameObject(eLayerType::MONSTER)
		, meAttackColliderType(eAttackColliderType)
	{
		Collider2D* pCollider = new Collider2D(eColliderLayerType::MONSTER_WEAPON);
		AddComponent(pCollider);
		jh::math::Vector2 size;
		switch (meAttackColliderType)
		{
		case eBossMonsterColliderType::MELEE_ATTACK:
		{
			size = MELLE_ATTACK_SIZE;
			break;
		}
		case eBossMonsterColliderType::RANGE_ATTACK:
		{
			size = RANGE_ATTACK_SIZE;
			break;
		}
		case eBossMonsterColliderType::SPIN_ATTACK:
		{
			size = SPIN_ATTACK_SIZE;
			break;
		}
		case eBossMonsterColliderType::SUPER_ATTACK:
		{
			size = SUPER_ATTACK_SIZE;
			break;
		}
		default:
			assert(false);
			break;
		}

		pCollider->SetSize(size);
	}

	void AcientBossMonsterAttackColiderObject::SetMonsterTransformAndScriptAndAnimator(Transform* pMonsterTransform, AcientBossMonsterScript* pAcientBossMonsterScript, Animator* pAnimator)
	{
		assert(pMonsterTransform != nullptr && pAcientBossMonsterScript != nullptr && pAnimator != nullptr);
		AcientBossMonsterAttackColiderScript* pScript = new AcientBossMonsterAttackColiderScript(static_cast<Collider2D*>(GetComponentOrNull(eComponentType::COLLIDER)), pMonsterTransform, pAcientBossMonsterScript, pAnimator, meAttackColliderType);
		this->AddScript(pScript);
	}
}