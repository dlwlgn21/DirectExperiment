#pragma once
#include "jhAnimatedGameObject.h"


namespace jh
{
	enum class eHitEffectType
	{
		ELECTRIC,
		BLOOD,
		GAS,
		COUNT
	};

	class Texture;
	class MonsterScript;
	class PlayerScript;
	class HitEffectObject : public AnimatedGameObject
	{
	public:
		HitEffectObject(MonsterScript* pMonsterScript, PlayerScript* pPlayerScript);
		virtual ~HitEffectObject() = default;

	protected:
		void setScript(MonsterScript* pMonsterScript, PlayerScript* pPlayerScript);
		void setRenderer() override;
		void setAnimator() override;
	};
}

