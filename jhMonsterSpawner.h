#pragma once
#include "jhEngine.h"
#include "jhMath.h"


namespace jh
{
	class PlayScene;
	class PlayerScript;
	class MonsterSpawner final
	{
	public:
		static MonsterSpawner& GetInstance()
		{
			static MonsterSpawner instance;
			return instance;
		}
		MonsterSpawner(const MonsterSpawner& other) = delete;
		MonsterSpawner& operator=(const MonsterSpawner& other) = delete;
		
		void Initialize(PlayerScript* pPlayerScript);
		void Update();

	private:
		MonsterSpawner()
			: mCagedShokerRespawnTimer(CAGED_SHOKER_RESPAWN_TIME)
			, mSweeperRespawnTimer(SWEEPER_RESPAWN_TIME)
			, mpScene(nullptr)
			, mpPlayerScript(nullptr)
		{

		}
		~MonsterSpawner() = default;

		static const float CAGED_SHOKER_RESPAWN_TIME;
		static const float SWEEPER_RESPAWN_TIME;
		static const jh::math::Vector3 CAGED_SHOKER_SPAWN_POSITON;
		static const jh::math::Vector3 SWEEPER_SPAWN_POSITON;

	private:
		void spawnMonster(const eMonsterType eMonType);

	private:
		PlayScene*			mpScene;
		PlayerScript*		mpPlayerScript;
		float				mCagedShokerRespawnTimer;
		float				mSweeperRespawnTimer;

	};
}
