#pragma once
#include "jhEngine.h"


namespace jh
{
	class GameObject;
	class Layer final
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Release();
		virtual void Destroy();

		void AddGameObject(GameObject* pGameObj, const eLayerType eType);

		const std::vector<GameObject*>& GetGameObjects() const { return mGameObjects; }
		std::vector<GameObject*> GetDontDestroyGameObjects();
	private:
		std::vector<GameObject*> mGameObjects;
	};
}

