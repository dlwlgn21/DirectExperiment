#pragma once
#include "jhEngine.h"

namespace jh
{
	class MenuButtonObejct;
	class PlayerScript;
	class GameStateManager final
	{
	public:
		static GameStateManager& GetInstance()
		{
			static GameStateManager instance;
			return instance;
		}
		GameStateManager(const GameStateManager& other) = delete;
		GameStateManager& operator=(const GameStateManager& other) = delete;

		void Initialize();
		void OnPlayerDeadOrCrystalDestroyed();
		void OnKillBossMonster();
	private:
		GameStateManager()
			: mpPlayerScript(nullptr)
			, mpRestartButtonObject(nullptr)
			, mpQuitButtonObject(nullptr)
			, mpSelectBoxObject(nullptr)
		{
		}

		~GameStateManager() = default;

	private:
		PlayerScript*		mpPlayerScript;
		MenuButtonObejct*	mpRestartButtonObject;
		MenuButtonObejct*	mpQuitButtonObject;
		MenuButtonObejct*	mpSelectBoxObject;

	};
}

