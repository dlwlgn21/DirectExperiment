#include "jhMonsterSpawner.h"
#include "jhTime.h"
#include "jhSceneManager.h"
#include "jhPlayScene.h"
#include "jhMonsterObjectPool.h"
#include "jhTransform.h"
#include "jhPortalEffectScript.h"
#include "jhMonsterScript.h"
#include "jhLayerZValue.h"
#include "jhPlayerScript.h"

using namespace jh::math;

namespace jh
{
	const float MonsterSpawner::ZOMBIE_RESPAWN_TIME = 2.0f;
	const float MonsterSpawner::WARDEN_RESPAWN_TIME = 2.0f;
	const float MonsterSpawner::SWEEPER_RESPAWN_TIME = 2.0f;
	const float MonsterSpawner::CAGED_SHOKER_RESPAWN_TIME = 2.0f;
	const float MonsterSpawner::HEABY_SLICER_RESPAWN_TIME = 2.0f;
	const float MonsterSpawner::LIGHT_SLICER_RESPAWN_TIME = 2.0f;
	const float MonsterSpawner::DAGGER_RESPAWN_TIME = 2.0f;
	const float MonsterSpawner::ARCHER_RESPAWN_TIME = 3.0f;
	const float MonsterSpawner::BLASTER_RESPAWN_TIME = 2.0f;
	const float MonsterSpawner::ACIENT_BOSS_RESPAWN_TIME = 2.0f;

	static constexpr const float CAGED_SHOKER_Y_POS = -1.7f;
	static constexpr const float SWEEPER_Y_POS = -1.8f;
	static constexpr const float WARDEN_Y_POS = -2.0f;
	static constexpr const float ZOMBIE_Y_POS = -1.9f;
	static constexpr const float HEABY_SLICER_Y_POS = -1.0f;
	static constexpr const float LIGHT_SLICER_Y_POS = -1.0f;
	static constexpr const float DAGGER_Y_POS = -1.8f;
	static constexpr const float ARCHER_Y_POS = -2.3f;
	static constexpr const float BLASTER_Y_POS = -2.0f;
	static constexpr const float ACIENT_BOSS_Y_POS = -0.3f;

	void MonsterSpawner::Initialize(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		mpScene = static_cast<PlayScene*>(SceneManager::GetInstance().GetCurrentScene());
		mpPlayerScript = pPlayerScript;

		for (int i = 0; i < static_cast<UINT>(eMonsterType::COUNT); ++i)
		{
			if (i == static_cast<UINT>(eMonsterType::LV_1_ZOMBIE))
				{continue;}
			mpScene->AddGameObject(static_cast<GameObject*>(mPortalEffectObjects[i]), eLayerType::EFFECT);
			mPortalEffectObjects[i]->Initialize();
		}
	}

	void MonsterSpawner::Update()
	{
		assert(mpScene != nullptr && mpPlayerScript != nullptr);

		mCagedShokerRespawnTimer -= Time::DeltaTime();
		if (mCagedShokerRespawnTimer <= 0.0f)
			{spawnMonster(eMonsterType::LV_1_CAGED_SHOKER);}

		mSweeperRespawnTimer -= Time::DeltaTime();
		if (mSweeperRespawnTimer <= 0.0f)
			{spawnMonster(eMonsterType::LV_1_SWEEPER);}

		mWardenRespawnTimer -= Time::DeltaTime();
		if (mWardenRespawnTimer <= 0.0f)
			{spawnMonster(eMonsterType::LV_1_WARDEN);}

		mZombieRespawnTimer -= Time::DeltaTime();
		if (mZombieRespawnTimer <= 0.0f)
			{spawnMonster(eMonsterType::LV_1_ZOMBIE);}

		mHeabySlicerRespawnTimer -= Time::DeltaTime();
		if (mHeabySlicerRespawnTimer <= 0.0f)
			{spawnMonster(eMonsterType::LV_1_HEABY_SLICER);}

		mLightSlicerRespawnTimer -= Time::DeltaTime();
		if (mLightSlicerRespawnTimer <= 0.0f)
			{spawnMonster(eMonsterType::LV_1_LIGHT_SLICER);}

		mDaggerRespawnTimer -= Time::DeltaTime();
		if (mDaggerRespawnTimer <= 0.0f)
			{spawnMonster(eMonsterType::LV_1_DAGGER);}

		mArcherRespawnTimer -= Time::DeltaTime();
		if (mArcherRespawnTimer <= 0.0f)
			{spawnMonster(eMonsterType::LV_1_ARCHER);}

		mBlasterRespawnTimer -= Time::DeltaTime();
		if (mBlasterRespawnTimer <= 0.0f)
			{spawnMonster(eMonsterType::LV_1_BLASTER);}

		mAcientBossRespawnTimer -= Time::DeltaTime();
		if (mAcientBossRespawnTimer <= 0.0f)
			{spawnMonster(eMonsterType::LV_1_ACIENT_BOSS);}
	}

	void MonsterSpawner::spawnMonster(const eMonsterType eMonType)
	{
		assert(mpPlayerScript != nullptr);
		static const float DISTANCE_TO_PLAYER_X_POS = 3.5f;
		Vector3 playerPos = mpPlayerScript->GetOwner()->GetTransform()->GetPosition();
		float spawnXPos = playerPos.x + DISTANCE_TO_PLAYER_X_POS;

		switch (eMonType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			Vector3 spawnPos(spawnXPos, CAGED_SHOKER_Y_POS, MONSTER_Z_VALUE);
			addMonsterAtScene(eMonType, spawnPos);
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			Vector3 spawnPos(spawnXPos, SWEEPER_Y_POS, MONSTER_Z_VALUE);
			addMonsterAtScene(eMonType, spawnPos);
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			Vector3 spawnPos(spawnXPos, WARDEN_Y_POS, MONSTER_Z_VALUE);
			addMonsterAtScene(eMonType, spawnPos);
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			MonsterPackage monPack = MonsterObjectPool::GetInstance().Get(eMonType, mpPlayerScript, Vector3(spawnXPos, ZOMBIE_Y_POS, MONSTER_Z_VALUE));
			mpScene->AddMonster(monPack);
			resetTimer(eMonType);
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			Vector3 spawnPos(spawnXPos, HEABY_SLICER_Y_POS, MONSTER_Z_VALUE);
			addMonsterAtScene(eMonType, spawnPos);
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			Vector3 spawnPos(spawnXPos, LIGHT_SLICER_Y_POS, MONSTER_Z_VALUE);
			addMonsterAtScene(eMonType, spawnPos);
			break;
		}
		case eMonsterType::LV_1_DAGGER:
		{
			Vector3 spawnPos(spawnXPos, DAGGER_Y_POS, MONSTER_Z_VALUE);
			addMonsterAtScene(eMonType, spawnPos);
			break;
		}
		case eMonsterType::LV_1_ARCHER:
		{
			Vector3 spawnPos(spawnXPos, ARCHER_Y_POS, MONSTER_Z_VALUE);
			addMonsterAtScene(eMonType, spawnPos);
			break;
		}
		case eMonsterType::LV_1_BLASTER:
		{
			Vector3 spawnPos(spawnXPos, BLASTER_Y_POS, MONSTER_Z_VALUE);
			addMonsterAtScene(eMonType, spawnPos);
			break;
		}

		case eMonsterType::LV_1_ACIENT_BOSS:
		{
			Vector3 spawnPos(spawnXPos, ACIENT_BOSS_Y_POS, MONSTER_Z_VALUE);
			AcientBossMonsterPackage monPack = MonsterManager::GetInstance().MakeAcientBossMonster(mpPlayerScript, spawnPos);
			mpScene->AddBossMonster(monPack);
			//setPortalEffectPosition(eMonType, spawnPos);
			//playPortalEffectAnimation(eMonType, static_cast<AcientBossMonsterScript*>(monPack.pMonster->GetScriptOrNull()));
			resetTimer(eMonType);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void MonsterSpawner::addMonsterAtScene(const eMonsterType eMonType, const jh::math::Vector3& spawnPos)
	{
		MonsterPackage monPack = MonsterObjectPool::GetInstance().Get(eMonType, mpPlayerScript, spawnPos);
		mpScene->AddMonster(monPack);
		setPortalEffectPosition(eMonType, spawnPos);
		playPortalEffectAnimation(eMonType, static_cast<MonsterScript*>(monPack.pMonster->GetScriptOrNull()));
		resetTimer(eMonType);
	}

	void MonsterSpawner::resetTimer(const eMonsterType eMonType)
	{
		static const float WAIT_TIME_FOR_DEBUGING = 1000.0f;
		switch (eMonType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			//mCagedShokerRespawnTimer = CAGED_SHOKER_RESPAWN_TIME;
			mCagedShokerRespawnTimer = WAIT_TIME_FOR_DEBUGING;
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			//mSweeperRespawnTimer = SWEEPER_RESPAWN_TIME;
			mSweeperRespawnTimer = WAIT_TIME_FOR_DEBUGING;
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			//mWardenRespawnTimer = WARDEN_RESPAWN_TIME;
			mWardenRespawnTimer = WAIT_TIME_FOR_DEBUGING;
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			//mZombieRespawnTimer = ZOMBIE_RESPAWN_TIME;
			mZombieRespawnTimer = WAIT_TIME_FOR_DEBUGING;
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			//mHeabySlicerRespawnTimer = HEABY_SLICER_RESPAWN_TIME;
			mHeabySlicerRespawnTimer = WAIT_TIME_FOR_DEBUGING;
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			//mLightSlicerRespawnTimer = LIGHT_SLICER_RESPAWN_TIME;
			mLightSlicerRespawnTimer = WAIT_TIME_FOR_DEBUGING;
			break;
		}
		case eMonsterType::LV_1_DAGGER:
		{
			//mDaggerRespawnTimer = DAGGER_RESPAWN_TIME;
			mDaggerRespawnTimer = WAIT_TIME_FOR_DEBUGING;
			break;
		}
		case eMonsterType::LV_1_ARCHER:
		{
			//mArcherRespawnTimer = ARCHER_RESPAWN_TIME;
			mArcherRespawnTimer = WAIT_TIME_FOR_DEBUGING;
			break;
		}
		case eMonsterType::LV_1_BLASTER:
		{
			//mBlasterRespawnTimer = BLASTER_RESPAWN_TIME;
			mBlasterRespawnTimer = WAIT_TIME_FOR_DEBUGING;
			break;
		}
		case eMonsterType::LV_1_ACIENT_BOSS:
		{
			//mAcientBossRespawnTimer = ACIENT_BOSS_RESPAWN_TIME;
			mAcientBossRespawnTimer = WAIT_TIME_FOR_DEBUGING;
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void MonsterSpawner::setPortalEffectPosition(const eMonsterType eMonType, const jh::math::Vector3& pos)
	{
		assert(eMonType != eMonsterType::LV_1_ZOMBIE);
		mPortalEffectObjects[static_cast<UINT>(eMonType)]->GetTransform()->SetPosition(Vector3(pos.x, pos.y, BG_PORTAL_Z_VALUE));
	}
	void MonsterSpawner::playPortalEffectAnimation(const eMonsterType eMonType, const MonsterScript* pMonsterScript)
	{
		assert(eMonType != eMonsterType::LV_1_ZOMBIE);
		PortalEffectScript* pPortalScript = static_cast<PortalEffectScript*>(mPortalEffectObjects[static_cast<UINT>(eMonType)]->GetScriptOrNull());
		assert(pPortalScript != nullptr);
		const eObjectLookDirection eLookDir = pMonsterScript->GetMonsterLookDirection();
		switch (eLookDir)
		{
		case eObjectLookDirection::LEFT:
		{
			pPortalScript->SetAnimationFlip(false);
			break;
		}
		case eObjectLookDirection::RIGHT:
		{
			pPortalScript->SetAnimationFlip(true);
			break;
		}
		default:
			assert(false);
			break;
		}
		pPortalScript->SetStatePlaying();
	}
}