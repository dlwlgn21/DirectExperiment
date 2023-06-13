#include "jhUISkillIconScript.h"
#include "jhTransform.h"
#include "jhTime.h"

static constexpr const float TOP_BOX_Y_POSITON		= 2.0f;
static constexpr const float CENTER_BOX_Y_POSITON	= 0.0f;
static constexpr const float BOTTOM_BOX_Y_POSITON	= -2.0f;

static constexpr const float X_DSITANCE_FROM_CAMERA_CENTER_POSITION = 2.0f;

static constexpr const float DESCENT_SPEED = 4.0f;

namespace jh
{
	UISkillIconScript::UISkillIconScript(const eSkillIconType eType)
		: UILevelUpScript()
		, meSkillIconType(eType)
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
		const float xPos = mpCameraTransform->GetOnlyXPosition() - X_DSITANCE_FROM_CAMERA_CENTER_POSITION;
		switch (meSkillIconType)
		{
		case jh::eSkillIconType::ELECTRIC_BEAM:
		{
			mpTransform->SetOnlyXYPosition(xPos, CENTER_BOX_Y_POSITON);
			break;
		}
		case jh::eSkillIconType::ELECTRIC_STRIKE:
		{
			mpTransform->SetOnlyXYPosition(xPos, TOP_BOX_Y_POSITON);
			break;
		}
		case jh::eSkillIconType::ELECTRIC_TORNADO:
		{
			mpTransform->SetOnlyXYPosition(xPos, BOTTOM_BOX_Y_POSITON);
			break;
		}
		case jh::eSkillIconType::MELLE_ATTACK_DAMAGE:
		{
			mpTransform->SetOnlyXYPosition(xPos, BOTTOM_BOX_Y_POSITON);
			break;
		}
		case jh::eSkillIconType::SPEED:
		{
			mpTransform->SetOnlyXYPosition(xPos, CENTER_BOX_Y_POSITON);
			break;
		}
		case jh::eSkillIconType::HEALTH:
		{
			mpTransform->SetOnlyXYPosition(xPos, TOP_BOX_Y_POSITON);
			break;
		}
		default:
			assert(false);
			break;
		}

	}
}