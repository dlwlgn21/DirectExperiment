#include "jhMonsterSpawner.h"
#include "jhTime.h"
#include "jhSceneManager.h"
#include "jhPlayScene.h"
#include "jhMonsterObjectPool.h"
#include "jhTransform.h"
#include "jhPortalEffectScript.h"


using namespace jh::math;

namespace jh
{
	const float MonsterSpawner::CAGED_SHOKER_RESPAWN_TIME = 31.0f;
	const float MonsterSpawner::SWEEPER_RESPAWN_TIME = 11.0f;

	const jh::math::Vector3 MonsterSpawner::CAGED_SHOKER_SPAWN_POSITON = Vector3(6.0f, -1.7f, 4.0f);
	const jh::math::Vector3 MonsterSpawner::SWEEPER_SPAWN_POSITON = Vector3(3.0f, -1.8f, 4.0f);

	void MonsterSpawner::Initialize(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		mpScene = static_cast<PlayScene*>(SceneManager::GetInstance().GetCurrentScene());
		mpPlayerScript = pPlayerScript;

		for (int i = 0; i < static_cast<UINT>(eMonsterType::COUNT); ++i)
		{
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
	}

	void MonsterSpawner::spawnMonster(const eMonsterType eMonType)
	{
		switch (eMonType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			MonsterPackage monPack = MonsterObjectPool::GetInstance().Get(eMonType, mpPlayerScript, CAGED_SHOKER_SPAWN_POSITON);
			mpScene->AddMonster(monPack);
			mCagedShokerRespawnTimer = CAGED_SHOKER_RESPAWN_TIME;
			playPortalEffectAnimation(eMonType);
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			MonsterPackage monPack = MonsterObjectPool::GetInstance().Get(eMonType, mpPlayerScript, SWEEPER_SPAWN_POSITON);
			mpScene->AddMonster(monPack);
			mSweeperRespawnTimer = SWEEPER_RESPAWN_TIME;
			playPortalEffectAnimation(eMonType);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void MonsterSpawner::setPortalEffectPosition()
	{
		mPortalEffectObjects[static_cast<UINT>(eMonsterType::LV_1_CAGED_SHOKER)]->GetTransform()->SetPosition(CAGED_SHOKER_SPAWN_POSITON);
		mPortalEffectObjects[static_cast<UINT>(eMonsterType::LV_1_SWEEPER)]->GetTransform()->SetPosition(SWEEPER_SPAWN_POSITON);
	}

	void MonsterSpawner::playPortalEffectAnimation(const eMonsterType eMonType)
	{
		PortalEffectScript* pPortalScript = static_cast<PortalEffectScript*>(mPortalEffectObjects[static_cast<UINT>(eMonType)]->GetScriptOrNull());
		assert(pPortalScript != nullptr);
		pPortalScript->SetStatePlaying();
	}
}