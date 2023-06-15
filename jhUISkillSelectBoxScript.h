#pragma once
#include "jhUISkillScript.h"

namespace jh
{
	class Transform;
	class UISkillSelectBoxScript: public UISkillScript
	{
	public:
		UISkillSelectBoxScript();
		virtual ~UISkillSelectBoxScript() = default;

	private:
		void SetStayingXYPosition() override;
		void setSelectBoxPositionByInput();
	};
}
