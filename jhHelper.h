#pragma once
#include "jhScene.h"
#include "jhSceneManager.h"
#include "jhHitEffectObject.h"

namespace jh
{
	template<typename T>
	static T* Instantiate(const eLayerType eType)
	{
		Scene* pCurrScene = SceneManager::GetInstance().GetCurrentScene();
		assert(pCurrScene != nullptr);
		T* pGameObejct = new T();
		pCurrScene->AddGameObject(pGameObejct, eType);
		return pGameObejct;
	}

	template<typename T>
	static T* Instantiate(const eLayerType eType, HitEffectObject* pHitEffectObject)
	{
		Scene* pCurrScene = SceneManager::GetInstance().GetCurrentScene();
		assert(pCurrScene != nullptr);
		assert(pHitEffectObject != nullptr);
		T* pGameObejct = new T(pHitEffectObject);
		pCurrScene->AddGameObject(pGameObejct, eType);
		pCurrScene->AddGameObject(pHitEffectObject, eType);
		return pGameObejct;
	}



}
