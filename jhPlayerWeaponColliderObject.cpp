#include "jhPlayerWeaponColliderObject.h"
#include "jhCollider2D.h"
#include "jhWeaponColliderScript.h"

namespace jh
{
	PlayerWeaponColliderObject::PlayerWeaponColliderObject()
		: GameObject(eLayerType::PLAYER)
		, mpPlayerTransform(nullptr)
	{
		Collider2D* pCollider = new Collider2D();
		AddComponent(pCollider);
		pCollider->SetSize({2.0f, 1.0f});
	}
	void PlayerWeaponColliderObject::SetPlayerTransform(Transform* pPlayerTransform)
	{
		assert(pPlayerTransform != nullptr); 
		mpPlayerTransform = pPlayerTransform; 
		setScript();
	}
	void PlayerWeaponColliderObject::setScript()
	{
		WeaponColliderScript* pScript = new WeaponColliderScript(static_cast<Collider2D*>(GetComponentOrNull(eComponentType::COLLIDER)), mpPlayerTransform);
		AddScript(pScript);
	}
}