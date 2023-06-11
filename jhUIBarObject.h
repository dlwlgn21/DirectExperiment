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
		MONSTER_HP_BORDER,
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
		UIBarObject(const eUIBarType eType, MonsterScript* pMonsterScript);
		virtual ~UIBarObject() = default;

		const eUIBarType GetUIType() const { return meType; }

	private:
		void setRenderer();
		void setScript(PlayerScript* pPlayerScript);
		void setMonsterUI(MonsterScript* pMonsterScript);
	private:
		const eUIBarType meType;
	};
}