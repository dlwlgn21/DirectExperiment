#include "jhUILevelUpBorderScript.h"
#include "jhTransform.h"
#include "jhTime.h"

static constexpr const float DESCENT_SPEED = 4.0f;

namespace jh
{
	UILevelUpBorderScript::UILevelUpBorderScript()
		: UILevelUpScript()
	{
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