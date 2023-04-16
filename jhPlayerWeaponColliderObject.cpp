#include "jhPlayerWeaponColliderObject.h"
#include "jhCollider2D.h"
#include "jhWeaponColliderScript.h"
#include "jhEffectScript.h"

namespace jh
{
	PlayerWeaponColliderObject::PlayerWeaponColliderObject()
		: GameObject()
		, mpPlayerTransform(nullptr)
		, mpEffectScript(nullptr)
	{
		Collider2D* pCollider = new Collider2D();
		AddComponent(pCollider);
		pCollider->SetSize({2.0f, 1.0f});
	}
	void PlayerWeaponColliderObject::SetPlayerTransform(Transform* pPlayerTransform)
	{
		assert(pPlayerTransform != nullptr); 
		mpPlayerTransform = pPlayerTransform; 
	}
	void PlayerWeaponColliderObject::SetEffectScript(EffectScript* pEffectScript)
	{
		assert(pEffectScript != nullptr);
		mpEffectScript = pEffectScript;
		setScript();
	}
	void PlayerWeaponColliderObject::setScript()
	{
		WeaponColliderScript* pScript = new WeaponColliderScript(static_cast<Collider2D*>(GetComponentOrNull(eComponentType::COLLIDER)), mpPlayerTransform, mpEffectScript);
		AddScript(pScript);
	}
}