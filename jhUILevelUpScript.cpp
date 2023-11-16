#include "jhUILevelUpScript.h"
#include "jhTransform.h"
#include "jhTime.h"
#include "jhUISKillLevepUPConstantValues.h"

namespace jh
{
	UILevelUpScript::UILevelUpScript()
		: Script()
		, mpTransform()
		, mpCameraTransform()
		, meState(eUILevelUpState::WAIT)
	{
	}

	void UILevelUpScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void UILevelUpScript::Update()
	{
		assert(mpCameraTransform != nullptr);
		switch (meState)
		{
		case eUILevelUpState::WAIT:
		{
			SetWaitingPosition();
			break;
		}
		case eUILevelUpState::ENTERING:
		{
			float yPos = mpTransform->GetOnlyYPosition();
			if (yPos < FINAL_Y_POS)
			{
				SetState(eUILevelUpState::STAYING);
				break;
			}
			SetEnteringYPostion(yPos);
			break;
		}
		case eUILevelUpState::STAYING:
		{
			SetStayingXYPosition();
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void UILevelUpScript::InitWaitingStatePosition()
	{
		SetState(eUILevelUpState::WAIT);
		SetWaitingPosition();
	}

	void UILevelUpScript::SetWaitingPosition()
	{
		const float cameraXPos = mpCameraTransform->GetOnlyXPosition();
		mpTransform->SetOnlyXYPosition(cameraXPos, WAIT_Y_POS);
	}
}
