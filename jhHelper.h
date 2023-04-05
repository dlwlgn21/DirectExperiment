#pragma once
#include "jhScene.h"
#include "jhSceneManager.h"
namespace jh
{
	template<typename T>
	static T* Instantiate(const eLayerType eType)
	{
		Scene* pCurrScene = SceneManager::GetInstance().GetCurrentScene();
		assert(pCurrScene);
		T* pGameObejct = new T();
		pCurrScene->AddGameObject(pGameObejct, eType);
		return pGameObejct;
	}
}
