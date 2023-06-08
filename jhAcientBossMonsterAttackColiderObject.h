#pragma once
#include "jhGameObject.h"
#include "jhAcientBossMonsterAttackColiderScript.h"

namespace jh
{
	class Transform;
	class AcientBossMonsterScript;
	class Animator;
	class PlayerScript;
	class AcientBossMonsterAttackColiderObject : public GameObject
	{
	public:
		AcientBossMonsterAttackColiderObject(const eBossMonsterColliderType eAttackColliderType);
		virtual ~AcientBossMonsterAttackColiderObject() = default;

		void SetMonsterTransformAndScriptAndAnimator(Transform* pMonsterTransform, AcientBossMonsterScript* pAcientBossMonsterScript, Animator* pAnimator);
	
	private:
		eBossMonsterColliderType meAttackColliderType;
	};
}
