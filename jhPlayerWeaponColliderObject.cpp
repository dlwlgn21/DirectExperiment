#include "jhPlayerWeaponColliderObject.h"
#include "jhCollider2D.h"
#include "jhWeaponColliderScript.h"

namespace jh
{
	PlayerWeaponColliderObject::PlayerWeaponColliderObject()
		: GameObject(eLayerType::PLAYER)
	{
		Collider2D* pCollider = new Collider2D(eColliderLayerType::PLAYER_WEAPON);
		AddComponent(pCollider);
		pCollider->SetSize({2.0f, 1.0f});
	}
	void PlayerWeaponColliderObject::SetPlayerTransformAndScript(Transform* pPlayerTransform, PlayerScript* pPlayerScript)
	{
		assert(pPlayerTransform != nullptr && pPlayerScript != nullptr); 
		WeaponColliderScript* pScript = new WeaponColliderScript(static_cast<Collider2D*>(GetComponentOrNull(eComponentType::COLLIDER)), pPlayerTransform, pPlayerScript);
		AddScript(pScript);
	}
}