#pragma once
#include "jhUILevelUpScript.h"
#include "jhUISkillIconObject.h"


namespace jh
{
	class Transform;
	class UISkillIconScript : public UILevelUpScript
	{
	public:
		UISkillIconScript(const eSkillIconType eType);
		virtual ~UISkillIconScript() = default;

	private:
		void SetWaitingPosition() override;
		void SetStayingXYPosition() override;
		void SetEnteringYPostion(const float yPos) override;

	private:
		eSkillIconType		meSkillIconType;
	};
}

