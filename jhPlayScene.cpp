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
#include "jhCollider2D.h"
#include "jhCollisionManager.h"
#include "jhPlayerWeaponColliderObject.h"
#include "jhEffectScript.h"
#include "jhHitEffectObject.h"

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
		const float WIDTH_RATIO = 4;
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
		pPlayer->GetTransform()->SetPosition(Vector3(0.0f, -2.2f, 3.0f));
		pPlayer->GetTransform()->SetScale(Vector3(6.0f, 6.0f, 1.0f));

		// Effect
		//WeaponEffectObject* pEffect = Instantiate<WeaponEffectObject>(eLayerType::PLAYER);
		//pEffect->SetScript(static_cast<PlayerScript*>(pPlayer->GetScriptOrNull()));
		//pEffect->GetTransform()->SetParent(pPlayer);
		//pEffect->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, -2.0f));
		//pEffect->GetTransform()->SetScale(Vector3(0.5f, 0.5f, 1.0f));

		PlayerWeaponColliderObject* pPlayerWeaponColliderObject = Instantiate<PlayerWeaponColliderObject>(eLayerType::PLAYER);
		pPlayerWeaponColliderObject->GetTransform()->SetPosition(Vector3(0.0f, -2.2f, 3.0f));
		pPlayerWeaponColliderObject->SetPlayerTransform(pPlayer->GetTransform());
		//pPlayerWeaponColliderObject->SetEffectScript(static_cast<EffectScript*>(pEffect->GetScriptOrNull()));

		// Monster
		{
			Monster* pMonster = Instantiate<Monster>(eLayerType::MONSTER, new HitEffectObject());
			pMonster->GetTransform()->SetPosition(Vector3(4.0f, -2.0f, 4.0f));
			pMonster->GetTransform()->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		}

		// Parrarell
		{
			//BattleParrarellImageObject* pBGPObject = Instantiate<BattleParrarellImageObject>(eLayerType::BACKGROUND);
			//pBGPObject->SetName(L"BGParrarelObject");
			//pBGPObject->GetTransform()->SetPosition(Vector3(0.0f, 5.0f, 11.0f));
			//pBGPObject->GetTransform()->SetScale(Vector3(36.0f, 9.0f, 9.0f));
		}
		// BattleBG
		{
			BattleBGImageObject* pBGObject = Instantiate<BattleBGImageObject>(eLayerType::BACKGROUND);
			pBGObject->SetName(L"BGObject");
			pBGObject->GetTransform()->SetScale(Vector3(9 * WIDTH_RATIO, 3 * WIDTH_RATIO, 1.0f));
			pBGObject->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		}


		// Sword
		{
			//Sword* pSword = Instantiate<Sword>(eLayerType::PLAYER);
			//pSword->SetScript(static_cast<PlayerScript*>(pPlayer->GetScriptOrNull()));
			//pSword->GetTransform()->SetParent(pPlayer);
			//pSword->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, -1.0f));
			//pSword->GetTransform()->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			//Collider2D* pSwordCollider = new Collider2D();
			//pSword->AddComponent(pSwordCollider);
		}



		CollisionManager::GetInstance().SetCollisionLayerCheck(eLayerType::PLAYER, eLayerType::MONSTER);
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
