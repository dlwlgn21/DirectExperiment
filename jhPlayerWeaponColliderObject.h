#pragma once
#include "jhGameObject.h"


namespace jh
{
	class EffectScript;
	class Transform;
	class Player;
	class PlayerScript;
	class PlayerWeaponColliderObject : public GameObject
	{
	public:
		PlayerWeaponColliderObject();
		virtual ~PlayerWeaponColliderObject() = default;

		void SetPlayerTransformAndScript(Transform* pPlayerTransform, PlayerScript* pPlayerScript);
	};
}

