#include "jhGameStateManager.h"
#include "jhSceneManager.h"
#include "jhPlayScene.h"
#include "jhGameObject.h"
#include "jhPlayer.h"
#include "jhPlayerScript.h"
#include "jhMenuButtonObejct.h"
#include "jhGameOberMenuSelectBoxScript.h"
#include "jhGameCompleteObject.h"

namespace jh
{
	void GameStateManager::Initialize()
	{
		mpPlayerScript = static_cast<PlayScene*>(SceneManager::GetInstance().GetCurrentScene())->GetPlayerScript();
		assert(mpPlayerScript != nullptr);
	}

	void GameStateManager::OnPlayerDeadOrCrystalDestroyed()
	{
		mpRestartButtonObject = new MenuButtonObejct(eMenuButtonType::RESTART);
		mpQuitButtonObject = new MenuButtonObejct(eMenuButtonType::QUIT);
		mpSelectBoxObject = new MenuButtonObejct(eMenuButtonType::GAME_OVER_SELECT_BOX);
		mpRestartButtonObject->Initialize();
		mpQuitButtonObject->Initialize();
		mpSelectBoxObject->Initialize();
		static_cast<GameOberMenuSelectBoxScript*>(mpSelectBoxObject->GetScriptOrNull())->SetTopButtonObject(mpRestartButtonObject);
		static_cast<GameOberMenuSelectBoxScript*>(mpSelectBoxObject->GetScriptOrNull())->SetBottomButtonObject(mpQuitButtonObject);
		PlayScene* pScene = static_cast<PlayScene*>(SceneManager::GetInstance().GetCurrentScene());
		pScene->AddGameObject(mpRestartButtonObject, eLayerType::UI);
		pScene->AddGameObject(mpQuitButtonObject, eLayerType::UI);
		pScene->AddGameObject(mpSelectBoxObject, eLayerType::UI);
		static_cast<Player*>(mpPlayerScript->GetOwner())->Inactive();

	}
	void GameStateManager::OnKillBossMonster()
	{
		GameCompleteObject* pGameComplteObject = new GameCompleteObject();
		pGameComplteObject->Initialize();
		PlayScene* pScene = static_cast<PlayScene*>(SceneManager::GetInstance().GetCurrentScene());
		pScene->AddGameObject(pGameComplteObject, eLayerType::UI);

		std::vector<GameObject*>& pUIObjects = pScene->GetUIObjects();

		for (auto* pObject : pUIObjects)
		{
			pObject->SetState(GameObject::eGameObjectState::INACTIVE);
		}

	}

}