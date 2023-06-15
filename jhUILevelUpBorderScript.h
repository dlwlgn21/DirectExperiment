#pragma once
#include "jhUILevelUpScript.h"


namespace jh
{
	class Transform;
	class UILevelUpBorderScript : public UILevelUpScript
	{
	public:
		UILevelUpBorderScript();
		virtual ~UILevelUpBorderScript() = default;
		
	private:
		void SetStayingXYPosition() override;
		void SetEnteringYPostion(const float yPos) override;
	};
}

