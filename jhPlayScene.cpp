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
#include "jhHitEffectScript.h"
#include "jhHitEffectObject.h"
#include "jhPlayerScript.h"
#include "jhParallaxObject.h"
#include "jhUIBarObject.h"
#include "jhMonsterAttackColiderObject.h"
#include "jhMonsterAttackColiderScript.h"
#include "jhMonsterScript.h"
#include "jhAnimator.h"
#include "jhBGMoonObject.h"
#include "jhPlayerDustEffectObject.h"
#include "jhTexture.h"
#include "jhMonsterManager.h"

using namespace jh::math;

static constexpr const float PARALLAX_1_DEPTH = 100.0f;
static constexpr const float PARALLAX_2_DEPTH = 90.0f;
static constexpr const float PARALLAX_3_DEPTH = 80.0f;
static constexpr const float PARALLAX_4_DEPTH = 70.0f;
static constexpr const float PARALLAX_5_DEPTH = 60.0f;
static constexpr const float PARALLAX_6_DEPTH = 50.0f;

static constexpr const float SCENE_COLLIDER_Z_VALUE = 3.0f;

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
		PlayerScript* pPlayerScript = instantiateCameraAndPlayer();
		assert(pPlayerScript != nullptr);
		instantiateMonsters(pPlayerScript);
		instantiateParallaxObjects();
		instantiateEnvObject();
		instantiateUIObject(pPlayerScript);
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
	PlayerScript* PlayScene::instantiateCameraAndPlayer()
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
		PlayerDustEffectObject* pPlayerDustEffectObject = Instantiate<PlayerDustEffectObject>(eLayerType::EFFECT);
		pPlayer->SetEffectToPlayerScript(pPlayerDustEffectObject);
		pCameraScript->SetPlayerTransform(pPlayer->GetTransform());

		PlayerWeaponColliderObject* pPlayerWeaponColliderObject = Instantiate<PlayerWeaponColliderObject>(eLayerType::PLAYER);
		pPlayerWeaponColliderObject->GetTransform()->SetPosition(Vector3(0.0f, -2.2f, SCENE_COLLIDER_Z_VALUE));
		pPlayerWeaponColliderObject->SetPlayerTransformAndScript(pPlayer->GetTransform(), static_cast<PlayerScript*>(pPlayer->GetScriptOrNull()));
	
		return static_cast<PlayerScript*>(pPlayer->GetScriptOrNull());
	}

	void PlayScene::instantiateMonsters(PlayerScript* pPlayerScript)
	{	
		assert(pPlayerScript);
		MonstePackage monPack = MonsterManager::GetInstance().MakeMonster(eMonsterType::LV_1_CAGED_SHOKER, pPlayerScript);

		this->AddGameObject(monPack.pMonster, eLayerType::MONSTER);
		this->AddGameObject(monPack.pHitEffectObejct, eLayerType::EFFECT);
		this->AddGameObject(monPack.pMonsterAttackColliderObject, eLayerType::MONSTER);
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

	void PlayScene::instantiateEnvObject()
	{
		BGMoonObject* pBGMoon = Instantiate<BGMoonObject>(eLayerType::BACKGROUND);
		pBGMoon->GetTransform()->SetScale(Vector3(6.0f, 6.0f, 1.0f));
	}
	void PlayScene::instantiateUIObject(PlayerScript* pPlayerScript)
	{
		UIBarObject* pHealthBorderOject = new UIBarObject(eUIBarType::HEALTH_BORDER, pPlayerScript);
		this->AddGameObject(pHealthBorderOject, eLayerType::UI);

		UIBarObject* pHpBarOject = new UIBarObject(eUIBarType::HEALTH_BAR, pPlayerScript);
		this->AddGameObject(pHpBarOject, eLayerType::UI);

		UIBarObject* pStaminaBorderOject = new UIBarObject(eUIBarType::STAMINAR_BORDER, pPlayerScript);
		this->AddGameObject(pStaminaBorderOject, eLayerType::UI);

		UIBarObject* pStaminarBarOject = new UIBarObject(eUIBarType::STAMINA_BAR, pPlayerScript);
		this->AddGameObject(pStaminarBarOject, eLayerType::UI);
	}

	void PlayScene::instantiateOtherObjects()
	{
	}
}
