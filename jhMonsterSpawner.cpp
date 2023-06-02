#include "jhMonsterSpawner.h"
#include "jhTime.h"
#include "jhSceneManager.h"
#include "jhPlayScene.h"
#include "jhMonsterObjectPool.h"
#include "jhTransform.h"
#include "jhPortalEffectScript.h"
#include "jhMonsterScript.h"
#include "jhLayerZValue.h"

using namespace jh::math;

namespace jh
{
	const float MonsterSpawner::ZOMBIE_RESPAWN_TIME = 5.0f;
	const float MonsterSpawner::WARDEN_RESPAWN_TIME = 10.0f;
	const float MonsterSpawner::SWEEPER_RESPAWN_TIME = 15.0f;
	const float MonsterSpawner::CAGED_SHOKER_RESPAWN_TIME = 20.0f;

	const jh::math::Vector3 MonsterSpawner::CAGED_SHOKER_SPAWN_POSITON = Vector3(6.0f, -1.7f, MONSTER_Z_VALUE);
	const jh::math::Vector3 MonsterSpawner::SWEEPER_SPAWN_POSITON = Vector3(3.0f, -1.8f, MONSTER_Z_VALUE);
	const jh::math::Vector3 MonsterSpawner::WARDEN_SPAWN_POSITON = Vector3(1.0f, -2.0f, MONSTER_Z_VALUE);
	const jh::math::Vector3 MonsterSpawner::ZOMBIE_SPAWN_POSITION = Vector3(1.0f, -1.9f, MONSTER_Z_VALUE);

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
		setPortalEffectPosition();
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
	}

	void MonsterSpawner::spawnMonster(const eMonsterType eMonType)
	{
		switch (eMonType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			MonsterPackage monPack = MonsterObjectPool::GetInstance().Get(eMonType, mpPlayerScript, CAGED_SHOKER_SPAWN_POSITON);
			mpScene->AddMonster(monPack);
			resetTimer(eMonType);
			setPortalEffectPosition(eMonType, CAGED_SHOKER_SPAWN_POSITON);
			playPortalEffectAnimation(eMonType, static_cast<MonsterScript*>(monPack.pMonster->GetScriptOrNull()));
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			MonsterPackage monPack = MonsterObjectPool::GetInstance().Get(eMonType, mpPlayerScript, SWEEPER_SPAWN_POSITON);
			mpScene->AddMonster(monPack);
			resetTimer(eMonType);
			setPortalEffectPosition(eMonType, SWEEPER_SPAWN_POSITON);
			playPortalEffectAnimation(eMonType, static_cast<MonsterScript*>(monPack.pMonster->GetScriptOrNull()));
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			MonsterPackage monPack = MonsterObjectPool::GetInstance().Get(eMonType, mpPlayerScript, WARDEN_SPAWN_POSITON);
			mpScene->AddMonster(monPack);
			resetTimer(eMonType);
			setPortalEffectPosition(eMonType, WARDEN_SPAWN_POSITON);
			playPortalEffectAnimation(eMonType, static_cast<MonsterScript*>(monPack.pMonster->GetScriptOrNull()));
			break;
		}

		case eMonsterType::LV_1_ZOMBIE:
		{
			MonsterPackage monPack = MonsterObjectPool::GetInstance().Get(eMonType, mpPlayerScript, ZOMBIE_SPAWN_POSITION);
			mpScene->AddMonster(monPack);
			resetTimer(eMonType);
			//setPortalEffectPosition(eMonType, WARDEN_SPAWN_POSITON);
			//playPortalEffectAnimation(eMonType, static_cast<MonsterScript*>(monPack.pMonster->GetScriptOrNull()));
			break;
		}
		default:
			assert(false);
			break;
		}
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
		default:
			assert(false);
			break;
		}
	}

	void MonsterSpawner::setPortalEffectPosition()
	{
		mPortalEffectObjects[static_cast<UINT>(eMonsterType::LV_1_CAGED_SHOKER)]->GetTransform()->SetPosition(Vector3(CAGED_SHOKER_SPAWN_POSITON.x, CAGED_SHOKER_SPAWN_POSITON.y, BG_PORTAL_Z_VALUE));
		mPortalEffectObjects[static_cast<UINT>(eMonsterType::LV_1_SWEEPER)]->GetTransform()->SetPosition(Vector3(SWEEPER_SPAWN_POSITON.x, SWEEPER_SPAWN_POSITON.y, BG_PORTAL_Z_VALUE));
		mPortalEffectObjects[static_cast<UINT>(eMonsterType::LV_1_WARDEN)]->GetTransform()->SetPosition(Vector3(WARDEN_SPAWN_POSITON.x, WARDEN_SPAWN_POSITON.x, BG_PORTAL_Z_VALUE));
		//mPortalEffectObjects[static_cast<UINT>(eMonsterType::LV_1_ZOMBIE)]->GetTransform()->SetPosition(Vector3(ZOMBIE_SPAWN_POSITION.x, ZOMBIE_SPAWN_POSITION.x, BG_PORTAL_Z_VALUE));
	}
	void MonsterSpawner::setPortalEffectPosition(const eMonsterType eMonType, const jh::math::Vector3& pos)
	{
		mPortalEffectObjects[static_cast<UINT>(eMonType)]->GetTransform()->SetPosition(Vector3(pos.x, pos.y, BG_PORTAL_Z_VALUE));
	}
	void MonsterSpawner::playPortalEffectAnimation(const eMonsterType eMonType, const MonsterScript* pMonsterScript)
	{
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