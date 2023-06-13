#pragma once
#include "jhEngine.h"

namespace jh
{
	class PlayerLevelManager final
	{
	public:
		static PlayerLevelManager& GetInstance()
		{
			static PlayerLevelManager instance;
			return instance;
		}
		PlayerLevelManager(const PlayerLevelManager& other) = delete;
		PlayerLevelManager& operator=(const PlayerLevelManager& other) = delete;

		void OnPlayerLevelUP();


	private:
		PlayerLevelManager() = default;
		~PlayerLevelManager() = default;
	};
}

