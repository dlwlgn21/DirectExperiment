#pragma once
#include "jhGameObject.h"


namespace jh
{
	class EffectScript;
	class Transform;
	class Player;
	class PlayerWeaponColliderObject : public GameObject
	{
	public:
		PlayerWeaponColliderObject();
		virtual ~PlayerWeaponColliderObject() = default;

		void SetPlayerTransform(Transform* pPlayerTransform);
	private:
		void setScript();
	private:
		Transform*			mpPlayerTransform;
	};
}

