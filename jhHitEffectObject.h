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
		HitEffectObject(const eHitEffectType eEffectType, MonsterScript* pMonsterScript, PlayerScript* pPlayerScript);
		HitEffectObject(const eHitEffectType eEffectType, PlayerScript* pPlayerScript);
		virtual ~HitEffectObject() = default;

	private:
		void setMonsterHitScript(MonsterScript* pMonsterScript, PlayerScript* pPlayerScript);
		void setPlayerHitScript(PlayerScript* pPlayerScript);
		void setRenderer() override;
		void setAnimator() override;
	private:
		const eHitEffectType	meHitEffectType;
	};
}

