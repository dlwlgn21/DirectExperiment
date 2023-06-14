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
	class UISkillObject : public GameObject
	{
	public:
		UISkillObject();
		virtual ~UISkillObject() = default;

	protected:
		virtual void setRenderer() = 0;
		virtual void setScript() = 0;
		virtual void setTransform() = 0;
		virtual void setAnimator();


	};
}