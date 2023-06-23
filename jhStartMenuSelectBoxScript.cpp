#include "jhStartMenuSelectBoxScript.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTransform.h"
#include "jhSFXManager.h"
#include "jhSceneManager.h"
#include "jhPlayScene.h"

namespace jh
{
	StartMenuSelectBoxScrip::StartMenuSelectBoxScrip()
		: MenuSelectBoxScript(eMenuSelectBoxType::START_MENU)
	{
	}

	void StartMenuSelectBoxScrip::OnSelected(const float currYPos, const float prevYPos)
	{
		SFXManager::GetInstance().Play(eSFXType::UI_LEVEL_UP_CHOICE);
		assert(mpTopButton != nullptr && mpBottomButton != nullptr);
		if (currYPos >= START_BUTTON_Y_POS)
		{
			mpTopButton->SetState(GameObject::eGameObjectState::INACTIVE);
			mpBottomButton->SetState(GameObject::eGameObjectState::INACTIVE);
			GetOwner()->SetState(GameObject::eGameObjectState::INACTIVE);
			PlayScene* pScene = static_cast<PlayScene*>(SceneManager::GetInstance().GetCurrentScene());
			pScene->SetIsStartGameTrue();
			pScene->InstantiateUIObject();
			pScene->ChangeCrystalState();
		}
		else
		{
			PostQuitMessage(0);
		}
	}




}