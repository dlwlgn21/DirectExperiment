#pragma once
#include "jhEngine.h"
#include "jhLayer.h"

namespace jh
{
	class GameObject;
	class Scene
	{
	public:
		Scene(const eSceneType eType);
		virtual ~Scene();
		
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Release();

		eSceneType GetSceneType() const { return meSceneType; }

		Layer* GetLayer(const eLayerType eLayer);

		void AddGameObject(GameObject* pGameObject, const eLayerType eType);
		const std::vector<GameObject*>& GetAllGameObjectsFromSpecifiedLayer(const eLayerType eType);
	protected:
		std::vector<std::unique_ptr<Layer>>	mLayers;
		eSceneType							meSceneType;
	};
}

