#include "jhUISkillTextScript.h"
#include "jhTransform.h"
#include "jhTime.h"
#include "jhUISKillLevepUPConstantValues.h"

static constexpr const float X_DSITANCE_FROM_CAMERA_CENTER_POSITION = 1.0f;

namespace jh
{
	UISkillTextScript::UISkillTextScript(const eSkillTextType eTextType)
		: UISkillScript()
		, meSkillTextType(eTextType)
		, meSkillPosition(eSkillPosition::NONE)
	{

	}

	void UISkillTextScript::SetStayingXYPosition()
	{
		assert(meState != eUILevelUpState::WAIT);
		const float xPos = mpCameraTransform->GetOnlyXPosition() + X_DSITANCE_FROM_CAMERA_CENTER_POSITION;
		switch (meSkillPosition)
		{
		case eSkillPosition::TOP:
		{
			mpTransform->SetOnlyXYPosition(xPos, TOP_BOX_Y_POSITON);
			break;
		}
		case eSkillPosition::CENTER:
		{
			mpTransform->SetOnlyXYPosition(xPos, CENTER_BOX_Y_POSITON);
			break;
		}
		case eSkillPosition::BOTTOM:
		{
			mpTransform->SetOnlyXYPosition(xPos, BOTTOM_BOX_Y_POSITON);
			break;
		}
		default:
			assert(false);
			break;
		}

	}
}