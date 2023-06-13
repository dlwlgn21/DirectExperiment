#pragma once
#include "jhGameObject.h"

namespace jh
{
	enum class eSkillIconType
	{
		ELECTRIC_BEAM,
		ELECTRIC_STRIKE,
		ELECTRIC_TORNADO,
		MELLE_ATTACK_DAMAGE,
		SPEED,
		HEALTH,
		COUNT
	};

	class UISkillIconObject : public GameObject
	{
	public:
		UISkillIconObject(const eSkillIconType eIconType);
		virtual ~UISkillIconObject() = default;

	private:
		void setRenderer();
		void setScript();
		void setTransform();
		void setAnimator();

	private:
		eSkillIconType meSkillIconType;
	};
}

