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

		void Initalize();
		void Update();
		void FixedUpdate();
		void Release();
		void Destroy();

		void AddGameObject(GameObject* pGameObj);

		const std::vector<GameObject*>& GetAllGameObjects() const { return mGameObjects; }
		std::vector<GameObject*> GetDontDestroyGameObjects();
	private:
		std::vector<GameObject*> mGameObjects;
	};
}

