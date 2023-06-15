#pragma once
#include "jhUILevelUpScript.h"

namespace jh
{
	class Transform;
	class UISkillSelectBoxScript: public UILevelUpScript
	{
	public:
		UISkillSelectBoxScript();
		virtual ~UISkillSelectBoxScript() = default;

	private:
		void SetWaitingPosition() override;
		void SetStayingXYPosition() override;
		void SetEnteringYPostion(const float yPos) override;
		void setSelectBoxPositionByInput();
	};
}
