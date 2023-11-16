#pragma once
#include "jhGameObject.h"

namespace jh
{
	enum class eUIBarType
	{
		HEALTH_BORDER,
		STAMINAR_BORDER,
		EXP_BORDER,
		HEALTH_BAR,
		STAMINA_BAR,
		EXP_BAR,
		MONSTER_HP_BAR,
		MOSNTER_HP_CIRCLE,
		COUNT
	};
	class Mesh;
	class PlayerScript;
	class UIBarScript;
	class MonsterScript;
	class UIBarObject : public GameObject
	{
	public:
		UIBarObject(const eUIBarType eType, PlayerScript* pPlayerScript);
		UIBarObject(MonsterScript* pMonsterScript);
		virtual ~UIBarObject() = default;

		const eUIBarType GetUIType() const { return meType; }

	private:
		void setRenderer();
		void setRenderer(MonsterScript* pMonsterScript);
		void setScript(PlayerScript* pPlayerScript);
		void setMonsterUI(MonsterScript* pMonsterScript);
		void setAnimator();
	private:
		const eUIBarType		meType;
	};
}