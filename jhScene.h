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
		
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;

		eSceneType GetSceneType() const { return meSceneType; }

		void AddGameObject(GameObject* pGameObject, const eLayerType eType);
	protected:
		std::vector<std::unique_ptr<Layer>>	mLayers;
		eSceneType							meSceneType;
	};
}

