#include "jhUISkillTextScript.h"
#include "jhTransform.h"
#include "jhTime.h"

static constexpr const float TOP_BOX_Y_POSITON = 2.0f;
static constexpr const float CENTER_BOX_Y_POSITON = 0.0f;
static constexpr const float BOTTOM_BOX_Y_POSITON = -2.0f;

static constexpr const float X_DSITANCE_FROM_CAMERA_CENTER_POSITION = 1.0f;

static constexpr const float DESCENT_SPEED = 4.0f;

namespace jh
{
	UISkillTextScript::UISkillTextScript(const eSkillTextType eTextType)
		: UILevelUpScript()
		, meSkillTextType(eTextType)
	{

	}

	void UISkillTextScript::SetWaitingPosition()
	{
		SetState(eUILevelUpState::WAIT);
	}

	void UISkillTextScript::SetEnteringYPostion(const float yPos)
	{
		mpTransform->SetOnlyXYPosition(mpCameraTransform->GetOnlyXPosition(), yPos - (DESCENT_SPEED * Time::DeltaTime()));
	}

	void UISkillTextScript::SetStayingXYPosition()
	{
		const float xPos = mpCameraTransform->GetOnlyXPosition() + X_DSITANCE_FROM_CAMERA_CENTER_POSITION;
		switch (meSkillTextType)
		{
		case eSkillTextType::ELECTRIC_BEAM_LV_1:
		{
			mpTransform->SetOnlyXYPosition(xPos, CENTER_BOX_Y_POSITON);
			break;
		}
		case eSkillTextType::ELECTRIC_STRKIE_LV_1:
		{
			mpTransform->SetOnlyXYPosition(xPos, TOP_BOX_Y_POSITON);
			break;
		}
		case eSkillTextType::ELECTRIC_TORNADO_LV_1:
		{
			mpTransform->SetOnlyXYPosition(xPos, BOTTOM_BOX_Y_POSITON);
			break;
		}
		case eSkillTextType::ELECTRIC_DAMAGE:
		{
			mpTransform->SetOnlyXYPosition(xPos, CENTER_BOX_Y_POSITON);
			break;
		}
		case eSkillTextType::ELECTRIC_SPAWN_SPEED:
		{
			mpTransform->SetOnlyXYPosition(xPos, CENTER_BOX_Y_POSITON);
			break;
		}
		case eSkillTextType::SWORD_DAMAGE:
		{
			mpTransform->SetOnlyXYPosition(xPos, BOTTOM_BOX_Y_POSITON);

			break;
		}
		case eSkillTextType::MOVEMENT_SPEED:
		{
			mpTransform->SetOnlyXYPosition(xPos, CENTER_BOX_Y_POSITON);
			break;
		}
		case eSkillTextType::RECORVER_HEALTH:
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