#include "jhSceneManager.h"
#include "jhPlayScene.h"

namespace jh
{
	void SceneManager::Initialize()
	{
		for (int i = 0; i < static_cast<UINT>(eSceneType::COUNT); ++i)
		{
			mpScenes[i] = nullptr;
		}
		mpScenes[static_cast<UINT>(eSceneType::PLAY_SCENE)] = new PlayScene();
		mpCurrScene = mpScenes[static_cast<UINT>(eSceneType::PLAY_SCENE)];
		mpCurrScene->Initialize();
	}
	void SceneManager::Update()
	{
		assert(mpCurrScene != nullptr);
		mpCurrScene->Update();
	}
	void SceneManager::FixedUpdate()
	{
		assert(mpCurrScene != nullptr);
		mpCurrScene->FixedUpdate();
	}
	void SceneManager::Render()
	{
		assert(mpCurrScene != nullptr);
		mpCurrScene->Render();
	}
	void SceneManager::Release()
	{
		for (auto* pScene : mpScenes)
		{
			if (pScene != nullptr)
			{
				delete pScene;
			}
		}
	}
}