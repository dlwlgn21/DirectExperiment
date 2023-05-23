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
#include "jhObeliskObject.h"
#include "jhMonsterObjectPool.h"
#include "jhMonsterSpawner.h"
#include "jhHitEffectObject.h"
#include "jhLight.h"
#include "jhInput.h"
#include "jhTime.h"

using namespace jh::math;

static constexpr const float PARALLAX_1_DEPTH = 100.0f;
static constexpr const float PARALLAX_2_DEPTH = 90.0f;
static constexpr const float PARALLAX_3_DEPTH = 80.0f;
static constexpr const float PARALLAX_4_DEPTH = 70.0f;
static constexpr const float PARALLAX_5_DEPTH = 60.0f;
static constexpr const float PARALLAX_6_DEPTH = 50.0f;

static constexpr const float SCENE_COLLIDER_Z_VALUE = 3.0f;

static constexpr const Vector4 WHITE_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
static constexpr const Vector4 GRAY_COLOR(0.5f, 0.5f, 0.5f, 1.0f);
static constexpr const Vector4 RED_COLOR(1.0f, 0.0f, 0.0f, 1.0f);
static constexpr const Vector4 GREEN_COLOR(0.0f, 1.0f, 0.0f, 1.0f);
static constexpr const Vector4 BLUE_COLOR(0.0f, 0.0f, 1.0f, 1.0f);


namespace jh
{
	Transform* pExperimentTransform;

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
		MonsterSpawner::GetInstance().Initialize(pPlayerScript);
		instantiateLight();
		instantiateParallaxObjects();
		instantiateEnvObject();
		instantiateUIObject(pPlayerScript);
		instantiateOtherObjects();
		CollisionManager::GetInstance().SetCollisionLayerCheck(eLayerType::PLAYER, eLayerType::MONSTER);
		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		//MonsterSpawner::GetInstance().Update();
		assert(pExperimentTransform != nullptr);
		static const float SPEED = 10.0f;
		Vector3 pos = pExperimentTransform->GetPosition();
		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x += (SPEED * Time::DeltaTime());
		}
		else if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x -= (SPEED * Time::DeltaTime());
		}
		else if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			pos.y += (SPEED * Time::DeltaTime());
		}
		else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos.y -= (SPEED * Time::DeltaTime());
		}
		else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			pos.z -= (SPEED * Time::DeltaTime());
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			pos.z += (SPEED * Time::DeltaTime());
		}

		pExperimentTransform->SetPosition(pos);

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

	void PlayScene::instantiateLight()
	{
		// Directional Light
		{
			//GameObject* pDirLightObject = Instantiate<GameObject>(eLayerType::PLAYER);
			//pDirLightObject->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			//LightAttribute lightAttribute;
			//ZeroMemory(&lightAttribute, sizeof(LightAttribute));
			//lightAttribute.ELightType = eLightType::DIRECTIONAL;
			//lightAttribute.Diffuse = WHITE_COLOR;
			//Light* pDirLightComponent = new Light(lightAttribute);
			//pDirLightObject->AddComponent(pDirLightComponent);
		}
		// Point Light
		{
			GameObject* pPointLightObject = Instantiate<GameObject>(eLayerType::PLAYER);
			pPointLightObject->GetTransform()->SetPosition(Vector3(-2.0f, -2.0f, 0.0f));
			LightAttribute lightAttribute;
			ZeroMemory(&lightAttribute, sizeof(LightAttribute));
			lightAttribute.ELightType = eLightType::POINT;
			lightAttribute.Diffuse = WHITE_COLOR;
			lightAttribute.Radius = 10.0f;
			Light* pPointLightComponent = new Light(lightAttribute);
			pPointLightObject->AddComponent(pPointLightComponent);
		}

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
		pPlayer->SetDustEffectToPlayerScript(pPlayerDustEffectObject);
		pCameraScript->SetPlayerTransform(pPlayer->GetTransform());

		PlayerWeaponColliderObject* pPlayerWeaponColliderObject = Instantiate<PlayerWeaponColliderObject>(eLayerType::PLAYER);
		pPlayerWeaponColliderObject->GetTransform()->SetPosition(Vector3(0.0f, -2.2f, SCENE_COLLIDER_Z_VALUE));
		pPlayerWeaponColliderObject->SetPlayerTransformAndScript(pPlayer->GetTransform(), static_cast<PlayerScript*>(pPlayer->GetScriptOrNull()));
	
		HitEffectObject* pHitEffectObejct = new HitEffectObject(eHitEffectType::BLOOD, static_cast<PlayerScript*>(pPlayer->GetScriptOrNull()));
		pPlayer->SetHitEffectToPlayerScript(pHitEffectObejct);
		AddGameObject(pHitEffectObejct, eLayerType::EFFECT);
		return static_cast<PlayerScript*>(pPlayer->GetScriptOrNull());
	}

	void PlayScene::instantiateMonsters(PlayerScript* pPlayerScript)
	{	
		assert(pPlayerScript);
		//MonsterPackage monPack = MonsterManager::GetInstance().MakeMonster();
		MonsterPackage monPack = MonsterObjectPool::GetInstance().Get(eMonsterType::LV_1_CAGED_SHOKER, pPlayerScript, Vector3(6.0f, -1.7f, 4.0f));
		AddMonster(monPack);
		//MonstePackage monPack2 = MonsterManager::GetInstance().MakeMonster(eMonsterType::LV_1_CAGED_SHOKER, pPlayerScript, Vector3(-6.0f, -1.8f, 4.0f), MonsterManager::CAGED_SHOKER_SCALE_VECTOR);
		//addMonster(monPack2);

		MonsterPackage monPack3 = MonsterObjectPool::GetInstance().Get(eMonsterType::LV_1_SWEEPER, pPlayerScript, Vector3(3.0f, -1.8f, 4.0f));
		AddMonster(monPack3);
	}

	void PlayScene::AddMonster(const MonsterPackage& monPack)
	{
		this->AddGameObject(monPack.pMonster, eLayerType::MONSTER);
		this->AddGameObject(monPack.pHitEffectObejct, eLayerType::MONSTER_EFFECT);
		this->AddGameObject(monPack.pMonsterAttackColliderObject, eLayerType::MONSTER);
	}
	void PlayScene::instantiateParallaxObjects()
	{
		// BattleBG
		const float ASPECT_RATIO = 9.24f;
		const float MAG = 10.0f;

		const Vector3 PARALLAX_SCLAE_VECTOR(16 * MAG, MAG, 1.0f);
		const Vector3 PARALLAX_ORIGINAL_SCLAE_VECTOR(ASPECT_RATIO * MAG, MAG, 1.0f);

		{
			BattleBGImageObject* pBGObject = Instantiate<BattleBGImageObject>(eLayerType::BACKGROUND);
			pBGObject->SetName(L"BGObject");
			pBGObject->GetTransform()->SetScale(PARALLAX_ORIGINAL_SCLAE_VECTOR);
			pBGObject->GetTransform()->SetPosition(Vector3(0.0f, -2.6f, 10.0f));
		}

		{
			ParallaxObject* pParallaxOne = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_1_DEPTH);
			pParallaxOne->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_1_KEY);
			pParallaxOne->GetTransform()->SetScale(Vector3(PARALLAX_ORIGINAL_SCLAE_VECTOR));
			pParallaxOne->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, PARALLAX_1_DEPTH));

			ParallaxObject* pParallaxTwo = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_2_DEPTH);
			pParallaxTwo->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_2_KEY);
			pParallaxTwo->GetTransform()->SetScale(PARALLAX_SCLAE_VECTOR);
			pParallaxTwo->GetTransform()->SetPosition(Vector3(0.0f, -0.4f, PARALLAX_2_DEPTH));

			ParallaxObject* pParallaxThree = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_3_DEPTH);
			pParallaxThree->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_3_KEY);
			pParallaxThree->GetTransform()->SetScale(PARALLAX_SCLAE_VECTOR);
			pParallaxThree->GetTransform()->SetPosition(Vector3(0.0f, 0.5f, PARALLAX_3_DEPTH));

			ParallaxObject* pParallaxFour = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_4_DEPTH);
			pParallaxFour->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_4_KEY);
			pParallaxFour->GetTransform()->SetScale(PARALLAX_SCLAE_VECTOR);
			pParallaxFour->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, PARALLAX_4_DEPTH));

			//ParallaxObject* pParallaxFive = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_5_DEPTH);
			//pParallaxFive->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_5_KEY);
			//pParallaxFive->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));
			//pParallaxFive->GetTransform()->SetPosition(Vector3(0.0f, 1.1f, PARALLAX_5_DEPTH));

			//ParallaxObject* pParallaxSix = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_6_DEPTH);
			//pParallaxSix->SetRenderer(ResourceMaker::PARALLAX_BG_MATERIAL_6_KEY);
			//pParallaxSix->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));
			//pParallaxSix->GetTransform()->SetPosition(Vector3(0.0f, 0.6f, PARALLAX_6_DEPTH));
		}
	}

	void PlayScene::instantiateEnvObject()
	{
		BGMoonObject* pBGMoon = Instantiate<BGMoonObject>(eLayerType::BACKGROUND);
		ObeliskObject* pObeliskObject = Instantiate<ObeliskObject>(eLayerType::BACKGROUND);
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
		GameObject* pBrickNormal = Instantiate<GameObject>(eLayerType::PLAYER);
		NormalMapMaterial* pMat = new NormalMapMaterial(
			ResourcesManager::Find<Shader>(ResourceMaker::NORMAL_MAP_SPRITE_SHADER_KEY),
			ResourcesManager::Find<Texture>(ResourceMaker::BRIK_DIFFUSE_TEXTURE_KEY),
			ResourcesManager::Find<Texture>(ResourceMaker::BRIK_NORMAL_MAP_TEXTURE_KEY)
		);

		SpriteRenderer* pSpriteRender = new SpriteRenderer(
			ResourcesManager::Find<Mesh>(ResourceMaker::RECT_NORMAL_MAP_MESH_KEY),
			pMat
		);
		pBrickNormal->AddComponent(pSpriteRender);
		pBrickNormal->GetTransform()->SetPosition(Vector3(0.0f, 1.0f, 2.0f));
		pBrickNormal->GetTransform()->SetScale(Vector3(6.0f, 6.0f, 1.0f));
		pExperimentTransform = pBrickNormal->GetTransform();
	}
}
