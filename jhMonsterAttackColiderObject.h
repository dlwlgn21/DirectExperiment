#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class MonsterScript;
	class MonsterAttackColiderObject : public GameObject
	{
	public:
		MonsterAttackColiderObject();
		virtual ~MonsterAttackColiderObject() = default;

		void SetMonsterTransformAndScript(Transform* pMonsterTransform, MonsterScript* pMonsterScript);
	};
}
