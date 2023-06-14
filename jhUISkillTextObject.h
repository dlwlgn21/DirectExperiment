#pragma once
#include "jhUISkillObject.h"

namespace jh
{
	enum class eSkillTextType
	{
		ELECTRIC_BEAM_LV_1,
		ELECTRIC_STRKIE_LV_1,
		ELECTRIC_TORNADO_LV_1,
		ELECTRIC_DAMAGE,
		ELECTRIC_SPAWN_SPEED,
		SWORD_DAMAGE,
		MOVEMENT_SPEED,
		RECORVER_HEALTH,
		COUNT
	};

	class UISKillTextObject final : public UISkillObject
	{
	public:
		UISKillTextObject(const eSkillTextType eType);
		virtual ~UISKillTextObject() = default;
	
	private:
		void setRenderer() override;
		void setScript() override;
		void setTransform() override;
	private:
		eSkillTextType	meSkillTextType;
	};
}

