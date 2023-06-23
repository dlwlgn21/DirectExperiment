#include "jhGameOberMenuSelectBoxScript.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTransform.h"
#include "jhSFXManager.h"
#include "jhSceneManager.h"
#include "jhPlayScene.h"
#include "jhD3DApp.h"

namespace jh
{
	GameOberMenuSelectBoxScript::GameOberMenuSelectBoxScript()
		: MenuSelectBoxScript(eMenuSelectBoxType::GAME_OVER_MENU)
	{
	}

	void GameOberMenuSelectBoxScript::OnSelected(const float currYPos, const float prevYPos)
	{
		SFXManager::GetInstance().Play(eSFXType::UI_LEVEL_UP_CHOICE);
		assert(mpTopButton != nullptr && mpBottomButton != nullptr);
		if (currYPos >= START_BUTTON_Y_POS)
		{
			mpTopButton->SetState(GameObject::eGameObjectState::INACTIVE);
			mpBottomButton->SetState(GameObject::eGameObjectState::INACTIVE);
			GetOwner()->SetState(GameObject::eGameObjectState::INACTIVE);
			PostQuitMessage(0);
		}
		else
		{
			PostQuitMessage(0);
		}
	}
}