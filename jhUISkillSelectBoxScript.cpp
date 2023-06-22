#include "jhUISkillSelectBoxScript.h"
#include "jhTransform.h"
#include "jhTime.h"
#include "jhInput.h"
#include "jhUISKillLevepUPConstantValues.h"
#include "jhPlayerLevelManager.h"
#include "jhSFXManager.h"

using namespace jh::math;

static constexpr const float Y_MOVEMENT_DISTANCE = 2.0f;

namespace jh
{
	UISkillSelectBoxScript::UISkillSelectBoxScript()
		: UISkillScript()
	{
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
			SFXManager::GetInstance().Play(eSFXType::UI_LEVEL_UP_MOVING);
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
			SFXManager::GetInstance().Play(eSFXType::UI_LEVEL_UP_MOVING);
			return;
		}

		if (Input::GetKeyState(eKeyCode::ENTER) == eKeyState::UP)
		{
			SFXManager::GetInstance().Play(eSFXType::UI_LEVEL_UP_CHOICE);
			if (currYPos > CENTER_BOX_Y_POSITON)
			{
				// if Top selected
				PlayerLevelManager::GetInstance().OnPlayerSelected(eSkillPosition::TOP);
				return;
			}
			else if (currYPos < CENTER_BOX_Y_POSITON)
			{
				// if Bottom selected
				PlayerLevelManager::GetInstance().OnPlayerSelected(eSkillPosition::BOTTOM);
				return;
			}
			else
			{
				// if Center selected
				PlayerLevelManager::GetInstance().OnPlayerSelected(eSkillPosition::CENTER);
				return;
			}
		}

		// There is NO input 
		mpTransform->SetOnlyXYPosition(xPos, currYPos);
	}

	void UISkillSelectBoxScript::SetStayingXYPosition()
	{
		assert(meState != eUILevelUpState::WAIT);
		setSelectBoxPositionByInput();
	}

}