#include "jhUISkillIconScript.h"
#include "jhTransform.h"
#include "jhTime.h"
#include "jhUISKillLevepUPConstantValues.h"


static constexpr const float X_DSITANCE_FROM_CAMERA_CENTER_POSITION = 2.0f;


namespace jh
{
	UISkillIconScript::UISkillIconScript(const eSkillIconType eType)
		: UILevelUpScript()
		, meSkillIconType(eType)
		, meSkillPosition(eSkillPosition::NONE)
	{

	}

	void UISkillIconScript::SetWaitingPosition()
	{
		SetState(eUILevelUpState::WAIT);
	}

	void UISkillIconScript::SetEnteringYPostion(const float yPos)
	{
		mpTransform->SetOnlyXYPosition(mpCameraTransform->GetOnlyXPosition(), yPos - (DESCENT_SPEED * Time::DeltaTime()));
	}

	void UISkillIconScript::SetStayingXYPosition()
	{
		assert(meState != eUILevelUpState::WAIT);
		const float xPos = mpCameraTransform->GetOnlyXPosition() - X_DSITANCE_FROM_CAMERA_CENTER_POSITION;
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