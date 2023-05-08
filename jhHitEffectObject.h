#pragma once
#include "jhAnimatedGameObject.h"


namespace jh
{
	class Texture;
	class MonsterScript;
	class PlayerScript;
	class HitEffectObject : public AnimatedGameObject
	{
	public:
		HitEffectObject();
		virtual ~HitEffectObject() = default;

		void AddEffectScript(Script* pFollwingScript, PlayerScript* pPlayerScript);

	protected:
		void setRenderer() override;
		void setAnimator() override;
	};
}

