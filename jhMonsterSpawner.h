#pragma once
#include "jhEngine.h"
#include "jhMath.h"
#include "jhPortalEffectObject.h"

namespace jh
{
	class PlayScene;
	class PlayerScript;
	class MonsterScript;
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
			, mWardenRespawnTimer(WARDEN_RESPAWN_TIME)
			, mZombieRespawnTimer(ZOMBIE_RESPAWN_TIME)
			, mHeabySlicerRespawnTimer(HEABY_SLICER_RESPAWN_TIME)
			, mpScene(nullptr)
			, mpPlayerScript(nullptr)
			, mPlayerPos(jh::math::Vector3::Zero)
		{
			mPortalEffectObjects.reserve(static_cast<UINT>(eMonsterType::COUNT));
			mPortalEffectObjects.resize(static_cast<UINT>(eMonsterType::COUNT));
			for (int i = 0; i < static_cast<UINT>(eMonsterType::COUNT); ++i)
			{
				if (i == static_cast<UINT>(eMonsterType::LV_1_ZOMBIE))
					{continue;}
				mPortalEffectObjects[i] = new PortalEffectObject();
			}

		}
		~MonsterSpawner() = default;

		static const float CAGED_SHOKER_RESPAWN_TIME;
		static const float SWEEPER_RESPAWN_TIME;
		static const float WARDEN_RESPAWN_TIME;
		static const float ZOMBIE_RESPAWN_TIME;
		static const float HEABY_SLICER_RESPAWN_TIME;

	private:
		void resetTimer(const eMonsterType eMonType);
		void setPortalEffectPosition(const eMonsterType eMonType, const jh::math::Vector3& pos);
		void playPortalEffectAnimation(const eMonsterType eMonType, const MonsterScript* pMonsterScript);
		void spawnMonster(const eMonsterType eMonType);
		void addMonsterAtScene(const eMonsterType eMonType, const jh::math::Vector3& spawnPos);

	private:
		PlayScene*							mpScene;
		PlayerScript*						mpPlayerScript;
		float								mCagedShokerRespawnTimer;
		float								mSweeperRespawnTimer;
		float								mWardenRespawnTimer;
		float								mZombieRespawnTimer;
		float								mHeabySlicerRespawnTimer;
		std::vector<PortalEffectObject*>	mPortalEffectObjects;
		jh::math::Vector3					mPlayerPos;
	};
}
