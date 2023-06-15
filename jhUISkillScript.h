#pragma once
#include "jhUILevelUpScript.h"

namespace jh
{
	class Transform;
	class UISkillScript : public UILevelUpScript
	{
	public:
		UISkillScript();
		virtual ~UISkillScript() = default;
		virtual void SetStayingXYPosition() = 0;
		void SetUILevelUpBorderScript(UILevelUpScript* pScript) { assert(pScript != nullptr); mpBorderScript = pScript;}
		
	protected:
		void SetEnteringYPostion(const float yPos) override;
	
	protected:
		UILevelUpScript*		mpBorderScript;
	};
}