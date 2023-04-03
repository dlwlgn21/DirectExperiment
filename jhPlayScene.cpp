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
			GameObject* pCameraObject = Intantiate<GameObject>(eLayerType::CAMERA);
			pCameraObject->SetName(L"MainCamera");
			Camera* pCameraComponent = new Camera();
			pCameraComponent->SetProjectionMode(eProjectionMode::ORTHOGRAPHIC_MODE);
			pCameraObject->AddComponent(pCameraComponent);
			CameraManager::GetInstance().SetCamera(pCameraComponent);
			CameraScript* pCameraScript = new CameraScript();
			pCameraObject->AddComponent(pCameraScript);
		}


		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::LOGO_MATERIAL_KEY);

		// PLAYER
		{
			GameObject* pPlayer = Intantiate<GameObject>(eLayerType::PLAYER);
			pPlayer->SetName(L"PlayerObject");
			pPlayer->GetTransform()->SetPosition(jh::math::Vector3(-1.0f, 0.0f, 1.0f));
			assert(pMesh != nullptr);
			assert(pMaterial != nullptr);
			SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
			pPlayer->AddComponent(pSpriteRenderer);
			PlayerScript* pScript = new PlayerScript();
			pPlayer->AddScript(pScript);
		}


		// MONSTER
		{
			GameObject* pMonster = Intantiate<GameObject>(eLayerType::MONSTER);
			pMonster->SetName(L"MonsterObject");
			pMonster->GetTransform()->SetPosition(jh::math::Vector3(1.0f, 0.0f, 2.0f));

			SpriteRenderer* pMonsterSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
			pMonster->AddComponent(pMonsterSpriteRenderer);

			MonsterScript* pMonsterScript = new MonsterScript();
			pMonster->AddScript(pMonsterScript);
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
