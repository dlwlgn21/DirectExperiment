#include "jhUISkillSelectBoxScript.h"
#include "jhTransform.h"
#include "jhTime.h"
#include "jhInput.h"
#include "jhUISKillLevepUPConstantValues.h"
#include "jhPlayerLevelManager.h"

using namespace jh::math;

static constexpr const float Y_MOVEMENT_DISTANCE = 2.0f;

namespace jh
{
	UISkillSelectBoxScript::UISkillSelectBoxScript()
		: UILevelUpScript()
	{
	}


	void UISkillSelectBoxScript::SetWaitingPosition()
	{
		SetState(eUILevelUpState::WAIT);
		mpTransform->SetOnlyYPosition(WAIT_Y_POS);
	}

	void UISkillSelectBoxScript::setSelectBoxPositionByInput()
	{
		const float xPos = mpCameraTransform->GetOnlyXPosition();
		static float currYPos = CENTER_BOX_Y_POSITON;
		static float prevYpos = currYPos;
		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::DOWN)
		{
			if (prevYpos <= BOTTOM_BOX_Y_POSITON)
			{
				mpTransform->SetOnlyXYPosition(xPos, prevYpos);
				return;
			}
			currYPos -= Y_MOVEMENT_DISTANCE;
			prevYpos = currYPos;
			mpTransform->SetOnlyXYPosition(xPos, currYPos);
			return;
		}
		else if (Input::GetKeyState(eKeyCode::UP) == eKeyState::DOWN)
		{
			if (prevYpos >= TOP_BOX_Y_POSITON)
			{
				mpTransform->SetOnlyXYPosition(xPos, prevYpos);
				return;
			}
			currYPos += Y_MOVEMENT_DISTANCE;
			prevYpos = currYPos;
			mpTransform->SetOnlyXYPosition(xPos, currYPos);
			return;
		}

		if (Input::GetKeyState(eKeyCode::ENTER) == eKeyState::UP)
		{
			if (currYPos > CENTER_BOX_Y_POSITON)
			{
				// if Top selected
				PlayerLevelManager::GetInstance().OnPlayerSelected(eSkillPosition::TOP);
			}
			else if (currYPos < CENTER_BOX_Y_POSITON)
			{
				// if Bottom selected
				PlayerLevelManager::GetInstance().OnPlayerSelected(eSkillPosition::BOTTOM);
			}
			else
			{
				// if Center selected
				PlayerLevelManager::GetInstance().OnPlayerSelected(eSkillPosition::CENTER);
			}
		}
	}

	void UISkillSelectBoxScript::SetStayingXYPosition()
	{
		assert(meState != eUILevelUpState::WAIT);
		setSelectBoxPositionByInput();
	}
	void UISkillSelectBoxScript::SetEnteringYPostion(const float yPos)
	{
		mpTransform->SetOnlyXYPosition(mpCameraTransform->GetOnlyXPosition(), yPos - (DESCENT_SPEED * Time::DeltaTime()));
	}

}