#pragma once
#include "jhGameObject.h"

namespace jh
{
	enum class eUIBarType
	{
		HEALTH_BORDER,
		STAMINAR_BORDER,
		HEALTH_BAR,
		STAMINA_BAR,
		MONSTER_HP_BAR,
		COUNT
	};
	class PlayerScript;
	class UIBarScript;
	class MonsterScript;
	class UIBarObject : public GameObject
	{
	public:
		UIBarObject(const eUIBarType eType, PlayerScript* pPlayerScript);
		UIBarObject(MonsterScript* pMonsterScript);
		virtual ~UIBarObject() = default;

	private:
		void setRenderer();
		void setScript(PlayerScript* pPlayerScript);
	private:
		const eUIBarType meType;
	};
}