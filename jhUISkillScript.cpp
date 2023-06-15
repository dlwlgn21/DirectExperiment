#include "jhUISkillScript.h"

namespace jh
{
	UISkillScript::UISkillScript()
		: UILevelUpScript()
		, mpBorderScript(nullptr)
	{

	}

	void UISkillScript::SetEnteringYPostion(const float yPos)
	{
		assert(mpBorderScript != nullptr);

		if (mpBorderScript->GetState() == eUILevelUpState::STAYING)
		{
			SetState(eUILevelUpState::STAYING);
		}
	}

}