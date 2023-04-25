#pragma once
#include "jhGameObject.h"

namespace jh
{
	class PlayerScript;
	class HitEffectObject;
	class Monster : public GameObject
	{
	public:
		Monster(HitEffectObject* pHitEffectObject, PlayerScript* pPlayerScript);
		virtual ~Monster() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	private:
		void setAnimator();
		void setRenderer();
		void setScript(PlayerScript* pPlayerScript);
		void setCollider();

	private:
		HitEffectObject*		mpHitEffectObject;
	};
}

