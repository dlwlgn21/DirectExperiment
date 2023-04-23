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
#include "jhPlayerScript.h"
#include "jhParallaxObject.h"
#include "jhUIBarObject.h"

using namespace jh::math;

static constexpr const float PARALLAX_1_DEPTH = 100.0f;
static constexpr const float PARALLAX_2_DEPTH = 90.0f;
static constexpr const float PARALLAX_3_DEPTH = 80.0f;
static constexpr const float PARALLAX_4_DEPTH = 70.0f;
static constexpr const float PARALLAX_5_DEPTH = 60.0f;
static constexpr const float PARALLAX_6_DEPTH = 50.0f;


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
		instantiateCameraAndPlayer();
		//instantiateMonsters();
		instantiateParallaxObjects();
		instantiateUIObject();

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
	void PlayScene::instantiateCameraAndPlayer()
	{
		// MainCamera
		GameObject* pCameraObject = Instantiate<GameObject>(eLayerType::CAMERA);
		pCameraObject->SetName(L"MainCamera");
		Camera* pCameraComponent = new Camera();
		pCameraComponent->SetProjectionMode(eProjectionMode::ORTHOGRAPHIC_MODE);
		pCameraObject->AddComponent(pCameraComponent);
		pCameraComponent->TurnLayerMask(eLayerType::UI, false);
		CameraManager::GetInstance().SetCamera(pCameraComponent);
		CameraScript* pCameraScript = new CameraScript();
		pCameraObject->AddComponent(pCameraScript);

		// UICamera
		GameObject* pUICameraObject = Instantiate<GameObject>(eLayerType::CAMERA);
		pUICameraObject->SetName(L"UICamera");
		Camera* pUICameraComponent = new Camera();
		pUICameraComponent->SetProjectionMode(eProjectionMode::ORTHOGRAPHIC_MODE);
		pUICameraComponent->DisableAllLayerMasks();
		pUICameraComponent->TurnLayerMask(eLayerType::UI, true);

		pUICameraObject->AddComponent(pUICameraComponent);
		CameraManager::GetInstance().SetUICamera(pUICameraComponent);


		// Player
		Player* pPlayer = Instantiate<Player>(eLayerType::PLAYER);
		pPlayer->GetTransform()->SetPosition(Vector3(0.0f, -2.0f, 3.0f));
		pPlayer->GetTransform()->SetScale(Vector3(6.0f, 6.0f, 1.0f));

		pCameraScript->SetPlayerTransform(pPlayer->GetTransform());

		PlayerWeaponColliderObject* pPlayerWeaponColliderObject = Instantiate<PlayerWeaponColliderObject>(eLayerType::PLAYER);
		pPlayerWeaponColliderObject->GetTransform()->SetPosition(Vector3(0.0f, -2.2f, 3.0f));
		pPlayerWeaponColliderObject->SetPlayerTransformAndScript(pPlayer->GetTransform(), static_cast<PlayerScript*>(pPlayer->GetScriptOrNull()));
	}

	void PlayScene::instantiateMonsters()
	{	
		Monster* pMonster = Instantiate<Monster>(eLayerType::MONSTER, new HitEffectObject());
		pMonster->GetTransform()->SetPosition(Vector3(4.0f, -1.7f, 4.0f));
		pMonster->GetTransform()->SetScale(Vector3(5.0f, 5.0f, 1.0f));
	}

	void PlayScene::instantiateParallaxObjects()
	{
		// BattleBG
		const float ASPECT_RATIO = 9.24f;
		const float MAG = 10.0f;
		{
			BattleBGImageObject* pBGObject = Instantiate<BattleBGImageObject>(eLayerType::BACKGROUND);
			pBGObject->SetName(L"BGObject");
			pBGObject->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));
			pBGObject->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		}

		{
			ParallaxObject* pParallaxOne = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_1_DEPTH);
			pParallaxOne->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_1_KEY);
			pParallaxOne->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));

			ParallaxObject* pParallaxTwo = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_2_DEPTH);
			pParallaxTwo->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_2_KEY);
			pParallaxTwo->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));
			pParallaxTwo->GetTransform()->SetPosition(Vector3(0.0f, 1.0f, PARALLAX_2_DEPTH));

			ParallaxObject* pParallaxThree = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_3_DEPTH);
			pParallaxThree->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_3_KEY);
			pParallaxThree->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));
			pParallaxThree->GetTransform()->SetPosition(Vector3(0.0f, 1.0f, PARALLAX_3_DEPTH));

			ParallaxObject* pParallaxFour = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_4_DEPTH);
			pParallaxFour->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_4_KEY);
			pParallaxFour->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));
			pParallaxFour->GetTransform()->SetPosition(Vector3(0.0f, 1.0f, PARALLAX_4_DEPTH));

			ParallaxObject* pParallaxFive = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_5_DEPTH);
			pParallaxFive->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_5_KEY);
			pParallaxFive->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));
			pParallaxFive->GetTransform()->SetPosition(Vector3(0.0f, 1.1f, PARALLAX_5_DEPTH));

			ParallaxObject* pParallaxSix = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_6_DEPTH);
			pParallaxSix->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_6_KEY);
			pParallaxSix->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));
			pParallaxSix->GetTransform()->SetPosition(Vector3(0.0f, 0.6f, PARALLAX_6_DEPTH));
		}
	}

	void PlayScene::instantiateUIObject()
	{
		//UIBarObject* pHealthBorderOject = new UIBarObject(eUIBarType::HEALTH_BORDER);
		//this->AddGameObject(pHealthBorderOject, eLayerType::UI);

		//UIBarObject* pHpBarOject = new UIBarObject(eUIBarType::HEALTH_BAR);
		//this->AddGameObject(pHpBarOject, eLayerType::UI);

		//UIBarObject* pStaminaBorderOject = new UIBarObject(eUIBarType::STAMINAR_BORDER);
		//this->AddGameObject(pStaminaBorderOject, eLayerType::UI);

		//UIBarObject* pStaminarBarOject = new UIBarObject(eUIBarType::STAMINA_BAR);
		//this->AddGameObject(pStaminarBarOject, eLayerType::UI);
	}

	void PlayScene::instantiateOtherObjects()
	{
	}
}
