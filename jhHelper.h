#pragma once
#include "jhScene.h"
#include "jhSceneManager.h"
#include "jhHitEffectObject.h"
#include "jhPlayerScript.h"

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
	static T* Instantiate(const eLayerType eType, const float zValue)
	{
		Scene* pCurrScene = SceneManager::GetInstance().GetCurrentScene();
		assert(pCurrScene != nullptr);
		T* pGameObejct = new T(zValue);
		pCurrScene->AddGameObject(pGameObejct, eType);
		return pGameObejct;
	}


	template<typename T>
	static T* InstantiateMonster(const eLayerType eType, HitEffectObject* pHitEffectObject, PlayerScript* pPlayerScript)
	{
		Scene* pCurrScene = SceneManager::GetInstance().GetCurrentScene();
		assert(pCurrScene != nullptr);
		assert(pHitEffectObject != nullptr);
		T* pGameObejct = new T(pHitEffectObject, pPlayerScript);
		pCurrScene->AddGameObject(pGameObejct, eType);
		pCurrScene->AddGameObject(pHitEffectObject, eLayerType::EFFECT);
		return pGameObejct;
	}



}
