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

	void Scene::AddGameObject(GameObject* pGameObject, const eLayerType eType)
	{
		assert(pGameObject != nullptr);
		mLayers[static_cast<UINT>(eType)]->AddGameObject(pGameObject, eType);
	}

}