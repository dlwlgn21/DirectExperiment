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
			pCameraComponent->SetProjectionMode(eProjectionMode::PERSPECTIVE_MODE);
			pCameraObject->AddComponent(pCameraComponent);
			CameraManager::GetInstance().SetCamera(pCameraComponent);
			CameraScript* pCameraScript = new CameraScript();
			pCameraObject->AddComponent(pCameraScript);
		}

		// Player
		{
			Player* pPlayer = Instantiate<Player>(eLayerType::PLAYER);
			pPlayer->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, 3.0f));
			pPlayer->GetTransform()->SetScale(Vector3(5.0f, 5.0f, 3.0f));
		}

		// Monster
		{
			Monster* pMonster = Instantiate<Monster>(eLayerType::MONSTER);
			pMonster->GetTransform()->SetPosition(Vector3(1.0f, 0.0f, 4.0f));
			pMonster->GetTransform()->SetScale(Vector3(3.0f, 3.0f, 4.0f));
		}

		// BattleBG
		{
			//BattleBGImageObject* pBGObject = Instantiate<BattleBGImageObject>(eLayerType::BACKGROUND);
			//pBGObject->SetName(L"BGObject");
			//pBGObject->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
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
