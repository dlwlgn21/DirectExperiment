#pragma once
#include "jhEngine.h"
#include "jhMath.h"
#include "jhPortalEffectObject.h"

namespace jh
{
	enum class eStagePhase
	{
		FIRST_WARDEN_SWEEPER_STAGE,
		SECOND_BLASTER_DAGGER_STAGE,
		THIRD_ARCHER_SHOKER_STAGE,
		FORTH_LIGHT_HEABY_SLICER_STAGE,
		FIFTH_BOSS_STAGE,
		COUNT
	};

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
		const eStagePhase GetStagePhase() const { return meStagePhase; }
		float GetStageChangeTimerTime() const	{ return mStageChangeTimer; }

	public:
		static constexpr const float STAGE_CHANGE_TIME = 25.0f;

	private:
		MonsterSpawner()
			: mCagedShokerRespawnTimer(CAGED_SHOKER_RESPAWN_TIME)
			, mSweeperRespawnTimer(SWEEPER_RESPAWN_TIME)
			, mWardenRespawnTimer(WARDEN_RESPAWN_TIME)
			, mZombieRespawnTimer(ZOMBIE_RESPAWN_TIME)
			, mHeabySlicerRespawnTimer(HEABY_SLICER_RESPAWN_TIME)
			, mLightSlicerRespawnTimer(LIGHT_SLICER_RESPAWN_TIME)
			, mDaggerRespawnTimer(DAGGER_RESPAWN_TIME)
			, mArcherRespawnTimer(ARCHER_RESPAWN_TIME)
			, mBlasterRespawnTimer(BLASTER_RESPAWN_TIME)
			, mpScene(nullptr)
			, mpPlayerScript(nullptr)
			, mPlayerPos(jh::math::Vector3::Zero)
			, mTotalTimeTimer(0.0f)
			, meStagePhase(eStagePhase::FIRST_WARDEN_SWEEPER_STAGE)
			, mbIsSpawnAcientBoss(false)
			, mStageChangeTimer(0.0f)
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
		static const float LIGHT_SLICER_RESPAWN_TIME;
		static const float DAGGER_RESPAWN_TIME;
		static const float ARCHER_RESPAWN_TIME;
		static const float BLASTER_RESPAWN_TIME;
		static const float ACIENT_BOSS_RESPAWN_TIME;

	private:
		void resetTimer(const eMonsterType eMonType);
		void setPortalEffectPosition(const eMonsterType eMonType, const jh::math::Vector3& pos);
		void playPortalEffectAnimation(const eMonsterType eMonType, const MonsterScript* pMonsterScript);
		void spawnMonster(const eMonsterType eMonType);
		void addMonsterAtScene(const eMonsterType eMonType, const jh::math::Vector3& spawnPos);
		void changeStagePhase(const eStagePhase ePhase) { meStagePhase = ePhase; }

	private:
		PlayScene*							mpScene;
		PlayerScript*						mpPlayerScript;
		float								mCagedShokerRespawnTimer;
		float								mSweeperRespawnTimer;
		float								mWardenRespawnTimer;
		float								mZombieRespawnTimer;
		float								mHeabySlicerRespawnTimer;
		float								mLightSlicerRespawnTimer;
		float								mDaggerRespawnTimer;
		float								mArcherRespawnTimer;
		float								mBlasterRespawnTimer;
		std::vector<PortalEffectObject*>	mPortalEffectObjects;
		jh::math::Vector3					mPlayerPos;
		eStagePhase							meStagePhase;
		float								mTotalTimeTimer;
		float								mStageChangeTimer;
		bool								mbIsSpawnAcientBoss;
	};
}
