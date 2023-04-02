#include "jhPlayScene.h"

namespace jh
{
	PlayScene::PlayScene()
		: Scene(eSceneType::PLAY_SCENE)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		for (int i = 0; i < static_cast<UINT>(eLayerType::COUNT); ++i)
		{
			mLayers[i]->Initalize();
		}
	}

	void PlayScene::Update()
	{
		for (int i = 0; i < static_cast<UINT>(eLayerType::COUNT); ++i)
		{
			mLayers[i]->Update();
		}
	}

	void PlayScene::FixedUpdate()
	{
		for (int i = 0; i < static_cast<UINT>(eLayerType::COUNT); ++i)
		{
			mLayers[i]->FixedUpdate();
		}
	}

	void PlayScene::Render()
	{
		for (int i = 0; i < static_cast<UINT>(eLayerType::COUNT); ++i)
		{
			mLayers[i]->Render();
		}
	}

	void PlayScene::Release()
	{
	}
}
