#include "jhPlayScene.h"
#include "jhResourcesManager.h"
#include "jhResourceMaker.h"
#include "jhGameObject.h"
#include "jhHelper.h"
#include "jhSpriteRenderer.h"
#include "jhPlayerScript.h"
#include "jhMonsterScript.h"
#include "jhCamera.h"
#include "jhCameraManager.h"
#include "jhCameraScript.h"
#include "jhTransform.h"
#include "jhPlayer.h"
#include "jhMonster.h"
#include "jhBattleBGImageObject.h"
#include "jhBattleParrarellImageObject.h"
#include "jhSword.h"

using namespace jh::math;

namespace jh
{
	PlayScene::PlayScene()
		: Scene(eSceneType::PLAY_SCENE)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		// CAMERA
		{
			GameObject* pCameraObject = Instantiate<GameObject>(eLayerType::CAMERA);
			pCameraObject->SetName(L"MainCamera");
			Camera* pCameraComponent = new Camera();
			pCameraComponent->SetProjectionMode(eProjectionMode::ORTHOGRAPHIC_MODE);
			pCameraObject->AddComponent(pCameraComponent);
			CameraManager::GetInstance().SetCamera(pCameraComponent);
			CameraScript* pCameraScript = new CameraScript();
			pCameraObject->AddComponent(pCameraScript);
		}

		// Player
		Player* pPlayer = Instantiate<Player>(eLayerType::PLAYER);
		pPlayer->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, 3.0f));
		pPlayer->GetTransform()->SetScale(Vector3(7.0f, 7.0f, 1.0f));


		// Monster
		{
			Monster* pMonster = Instantiate<Monster>(eLayerType::MONSTER);
			pMonster->GetTransform()->SetPosition(Vector3(1.0f, 0.0f, 4.0f));
			pMonster->GetTransform()->SetScale(Vector3(3.0f, 3.0f, 4.0f));
		}

		// Parrarell
		{
			BattleParrarellImageObject* pBGPObject = Instantiate<BattleParrarellImageObject>(eLayerType::BACKGROUND);
			pBGPObject->SetName(L"BGParrarelObject");
			pBGPObject->GetTransform()->SetScale(Vector3(3.0f, 1.0f, 1.0f));
		}
		// BattleBG
		{
			BattleBGImageObject* pBGObject = Instantiate<BattleBGImageObject>(eLayerType::BACKGROUND);
			pBGObject->SetName(L"BGObject");
			pBGObject->GetTransform()->SetScale(Vector3(2.0f, 1.0f, 1.0f));
			//pBGObject->GetTransform()->SetPosition(Vector3(0.0f, 7.0f, 10.0f));
		}


		// Sword
		{
			Sword* pSword = Instantiate<Sword>(eLayerType::PLAYER);
			pSword->GetTransform()->SetParent(pPlayer);
			pSword->GetTransform()->SetPosition(Vector3(0.1f, 0.0f, -1.0f));
			pSword->GetTransform()->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		}

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}


	void PlayScene::Release()
	{
		Scene::Release();
	}
}
