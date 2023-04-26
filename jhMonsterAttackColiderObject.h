#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Transform;
	class MonsterScript;
	class Animator;
	class PlayerScript;
	class MonsterAttackColiderObject : public GameObject
	{
	public:
		MonsterAttackColiderObject();
		virtual ~MonsterAttackColiderObject() = default;

		void SetMonsterTransformAndScriptAndAnimator(Transform* pMonsterTransform, MonsterScript* pMonsterScript, Animator* pAnimator);
	};
}
