#include "jhUILevelUpBorderScript.h"
#include "jhTransform.h"
#include "jhTime.h"

static constexpr const float WAIT_Y_POS = 10.0f;
static constexpr const float DESCENT_SPEED = 4.0f;

namespace jh
{
	UILevelUpBorderScript::UILevelUpBorderScript()
		: UILevelUpScript()
	{
	}


	void UILevelUpBorderScript::SetWaitingPosition()
	{
		SetState(eUILevelUpState::WAIT);
		mpTransform->SetOnlyYPosition(WAIT_Y_POS);
	}

	void UILevelUpBorderScript::SetStayingXYPosition()
	{
		mpTransform->SetOnlyXPosition(mpCameraTransform->GetOnlyXPosition());
	}
	void UILevelUpBorderScript::SetEnteringYPostion(const float yPos)
	{
		mpTransform->SetOnlyXYPosition(mpCameraTransform->GetOnlyXPosition(), yPos - (DESCENT_SPEED * Time::DeltaTime()));
	}

}