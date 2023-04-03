#pragma once
#include "jhEngine.h"

namespace jh
{
	class Scene;
	class SceneManager final
	{
	public:
		static SceneManager& GetInstance()
		{
			static SceneManager instance;
			return instance;
		}

		SceneManager(const SceneManager& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;

		void Initialize();
		void Update();
		void FixedUpdate();
		void Release();
		

		Scene* GetCurrentScene() const { return mpCurrScene; }
	private:
		SceneManager() = default;
		~SceneManager() = default;

	private:
		Scene* mpCurrScene;
		Scene* mpScenes[static_cast<UINT>(eSceneType::COUNT)];
	};
}

