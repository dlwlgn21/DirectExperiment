#include "jhScene.h"


namespace jh
{
	Scene::Scene(const eSceneType eType)
		: meSceneType(eType)
	{
		mLayers.reserve(static_cast<UINT>(eLayerType::COUNT));

		for (int i = 0; i < static_cast<UINT>(eLayerType::COUNT); ++i)
		{
			mLayers.push_back(std::make_unique<Layer>());
		}
	}
	Scene::~Scene()
	{
		mLayers.clear();
	}

	Layer* Scene::GetLayer(const eLayerType eLayer)
	{
		return mLayers[static_cast<UINT>(eLayer)].get();
	}

	void Scene::AddGameObject(GameObject* pGameObject, const eLayerType eType)
	{
		assert(pGameObject != nullptr);
		mLayers[static_cast<UINT>(eType)]->AddGameObject(pGameObject);
	}


	void Scene::Initialize()
	{
		for (int i = 0; i < static_cast<UINT>(eLayerType::COUNT); ++i)
		{
			mLayers[i]->Initalize();
		}
	}
	void Scene::Update()
	{
		for (int i = 0; i < static_cast<UINT>(eLayerType::COUNT); ++i)
		{
			mLayers[i]->Update();
		}
	}
	void Scene::FixedUpdate()
	{
		for (int i = 0; i < static_cast<UINT>(eLayerType::COUNT); ++i)
		{
			mLayers[i]->FixedUpdate();
		}
	}

	void Scene::Release()
	{

	}
}