#include <random>
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
#include "jhBGObeliskObject.h"
#include "jhMonsterObjectPool.h"
#include "jhMonsterSpawner.h"
#include "jhHitEffectObject.h"
#include "jhBGForegroundObject.h"
#include "jhBGFlowerObject.h"
#include "jhBGTorchObject.h"
#include "jhBGMushRoomSatueObject.h"
#include "jhBGLightningObject.h"
#include "jhLight.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhLayerZValue.h"
#include "jhLightingManager.h"
#include "jhAcientBossMonsterAttackColiderObject.h"
#include "jhAcientBossMonsterAttackColiderScript.h"
#include "jhPlayerSkillManager.h"
#include "jhPlayerSkillObject.h"
#include "jhPlayerLevelManager.h"
#include "jhUILevelUPBorderObject.h"
#include "jhUISkillSelectBoxObject.h"
#include "jhUITimeBarObject.h"

#include "jhPlayerLevelUpEffectObject.h"
#include "jhPlayerLevelUpEffectScript.h"

#include "jhProtectCrystalObject.h"
#include "jhProtectingCrystalScript.h"

#include "jhAudioClip.h"
#include "jhAudioListener.h"
#include "jhAudioSource.h"
#include "jhAudioSorceScrpt.h"
#include "jhSFXManager.h"

#include "jhMenuButtonObejct.h"
#include "jhStartMenuSelectBoxScript.h"

#include "jhGameCompleteObject.h"

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
static constexpr const Vector4 AMBIENT(0.1f, 0.1f, 0.1f, 1.0f);

static constexpr const float PLAYER_SPAWN_X_POS = 0.0f;

namespace jh
{
	void instatiateFlowerObejct()
	{
		BGFlowerObject* pBGFlower = nullptr;
		const float INIT_FLOWER_X_POS = -75.0f;
		const int FLOWER_COUNT = 10;
		const int MAX_X_FOREGROUND_DISTANCE = 70;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(-MAX_X_FOREGROUND_DISTANCE, MAX_X_FOREGROUND_DISTANCE);

		for (int i = 1; i <= FLOWER_COUNT; ++i)
		{
			pBGFlower = Instantiate<BGFlowerObject>(eLayerType::BACKGROUND);
			pBGFlower->SetPosition(static_cast<float>(dist(gen)));
		}
	}

	PlayScene::PlayScene()
		: Scene(eSceneType::PLAY_SCENE)
		, mpPlayerScript(nullptr)
		, mpCrystalScript(nullptr)
		, mbIsStartGame(false)
		, mpUIObjects()
	{
		mpUIObjects.reserve(8);
	}

	void PlayScene::Initialize()
	{

		PlayerScript* pPlayerScript = instantiateCameraAndPlayer();
		mpPlayerScript = pPlayerScript;
		assert(pPlayerScript != nullptr);
#pragma region INIT_MANAGERS
		PlayerSkillManager::GetInstance().SetPlayerScript(pPlayerScript);
		PlayerLevelManager::GetInstance().SetPlayerScript(pPlayerScript);
		MonsterSpawner::GetInstance().Initialize(pPlayerScript);
#pragma endregion

#pragma region INSTANTIATE_OBJECTS
		instantiateLight(pPlayerScript);
		instantiateParallaxObjects();
		instantiateEnvObject();
#pragma endregion

#pragma region COLLISION_CHECK
		CollisionManager::GetInstance().SetCollisionLayerCheck(eLayerType::PLAYER, eLayerType::MONSTER_ATTACK_COLLIDER);
		CollisionManager::GetInstance().SetCollisionLayerCheck(eLayerType::PROTECTING_OBJECT, eLayerType::MONSTER_ATTACK_COLLIDER);
		CollisionManager::GetInstance().SetCollisionLayerCheck(eLayerType::PLAYER, eLayerType::MONSTER);
		CollisionManager::GetInstance().SetCollisionLayerCheck(eLayerType::PLAYER_SKILL, eLayerType::MONSTER);
#pragma endregion

#pragma region LEVEL_UP_UI
		this->AddGameObject(PlayerLevelManager::GetInstance().GetUIBorder(), eLayerType::LEVEL_UP_UI);
		auto& skillIcons = PlayerLevelManager::GetInstance().GetUISkillIcons();
		auto& skillTexts = PlayerLevelManager::GetInstance().GetUISkillTexts();
		for (UINT i = 0; i < static_cast<UINT>(eSkillIconType::COUNT); ++i)
		{
			this->AddGameObject(skillIcons[i], eLayerType::LEVEL_UP_UI);
		}

		for (UINT i = 0; i < static_cast<UINT>(eSkillTextType::COUNT); ++i)
		{
			this->AddGameObject(skillTexts[i], eLayerType::LEVEL_UP_UI);
		}
		this->AddGameObject(PlayerLevelManager::GetInstance().GetSkillSelectBox(), eLayerType::LEVEL_UP_UI);
#pragma endregion
		
#pragma region PROTECTING_CRYSTAL
		ProtectingCrystalObject* pCrystal = new ProtectingCrystalObject();
		mpCrystalScript = static_cast<ProtectingCrystalScript*>(pCrystal->GetScriptOrNull());
		assert(mpCrystalScript != nullptr);
		mpCrystalScript->SetPlayerScript(pPlayerScript);
		this->AddGameObject(pCrystal, eLayerType::PROTECTING_OBJECT);
#pragma endregion

#pragma region START_MENU_BUTTON
		MenuButtonObejct* pStartButton = new MenuButtonObejct(eMenuButtonType::START);
		MenuButtonObejct* pQuitButton = new MenuButtonObejct(eMenuButtonType::QUIT);
		MenuButtonObejct* pSelectButton = new MenuButtonObejct(eMenuButtonType::START_SELECT_BOX);
		static_cast<StartMenuSelectBoxScrip*>(pSelectButton->GetScriptOrNull())->SetTopButtonObject(pStartButton);
		static_cast<StartMenuSelectBoxScrip*>(pSelectButton->GetScriptOrNull())->SetBottomButtonObject(pQuitButton);
		this->AddGameObject(pStartButton, eLayerType::UI);
		this->AddGameObject(pQuitButton, eLayerType::UI);
		this->AddGameObject(pSelectButton, eLayerType::UI);

#pragma endregion
		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		if (!PlayerLevelManager::GetInstance().IsProcessingLevelUp() && mbIsStartGame) 
		{
			MonsterSpawner::GetInstance().Update();
		}
		Scene::Update();
	}
	void PlayScene::InstantiateUIObject()
	{
		assert(mpPlayerScript != nullptr);
		UIBarObject* pHealthBorderOject = new UIBarObject(eUIBarType::HEALTH_BORDER, mpPlayerScript);
		this->AddGameObject(pHealthBorderOject, eLayerType::UI);
		pHealthBorderOject->Initialize();
		mpUIObjects.push_back(pHealthBorderOject);

		UIBarObject* pHpBarOject = new UIBarObject(eUIBarType::HEALTH_BAR, mpPlayerScript);
		this->AddGameObject(pHpBarOject, eLayerType::UI);
		pHpBarOject->Initialize();
		mpUIObjects.push_back(pHpBarOject);

		UIBarObject* pStaminaBorderOject = new UIBarObject(eUIBarType::STAMINAR_BORDER, mpPlayerScript);
		this->AddGameObject(pStaminaBorderOject, eLayerType::UI);
		pStaminaBorderOject->Initialize();
		mpUIObjects.push_back(pStaminaBorderOject);


		UIBarObject* pStaminarBarOject = new UIBarObject(eUIBarType::STAMINA_BAR, mpPlayerScript);
		this->AddGameObject(pStaminarBarOject, eLayerType::UI);
		pStaminarBarOject->Initialize();
		mpUIObjects.push_back(pStaminarBarOject);

		UIBarObject* pExpBorderOject = new UIBarObject(eUIBarType::EXP_BORDER, mpPlayerScript);
		this->AddGameObject(pExpBorderOject, eLayerType::UI);
		pExpBorderOject->Initialize();
		mpUIObjects.push_back(pExpBorderOject);

		UIBarObject* pExpBarOject = new UIBarObject(eUIBarType::EXP_BAR, mpPlayerScript);
		this->AddGameObject(pExpBarOject, eLayerType::UI);
		pExpBarOject->Initialize();
		mpUIObjects.push_back(pExpBarOject);

		UITimeBarObject* pTimeBarOject = new UITimeBarObject();
		this->AddGameObject(pTimeBarOject, eLayerType::UI);
		pTimeBarOject->Initialize();
		mpUIObjects.push_back(pTimeBarOject);
	}
	void PlayScene::ChangeCrystalState()
	{
		assert(mpCrystalScript != nullptr);
		mpCrystalScript->SetState(eCrystalState::ENTERING);
	}
#pragma region INSTANTIATE
#pragma region PLAYER_AND_CAMERA
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
		//AudioSource* pBGMSource = new AudioSource(ResourceMaker::GetInstance().GetAudioClipOrNull(eSFXType::BGM));
		//pCameraObject->AddComponent(pBGMSource);
		//pBGMSource->Play();
		AudioListener* pAudioListener = new AudioListener();
		pCameraObject->AddComponent(pAudioListener);
		PlayerLevelManager::GetInstance().SetCameraTransform(pCameraObject->GetTransform());

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
		pPlayer->GetTransform()->SetPosition(Vector3(PLAYER_SPAWN_X_POS, -2.0f, PLAYER_Z_VALUE));
		pPlayer->GetTransform()->SetScale(Vector3(6.0f, 6.0f, 1.0f));
		//AudioListener* pAudioListener = new AudioListener();
		//pPlayer->AddComponent(pAudioListener);

		PlayerDustEffectObject* pPlayerDustEffectObject = Instantiate<PlayerDustEffectObject>(eLayerType::EFFECT);
		pPlayer->SetDustEffectToPlayerScript(pPlayerDustEffectObject);
		pCameraScript->SetPlayerTransform(pPlayer->GetTransform());

		PlayerWeaponColliderObject* pPlayerWeaponColliderObject = Instantiate<PlayerWeaponColliderObject>(eLayerType::PLAYER);
		pPlayerWeaponColliderObject->GetTransform()->SetPosition(Vector3(0.0f, -2.2f, SCENE_COLLIDER_Z_VALUE));
		pPlayerWeaponColliderObject->SetPlayerTransformAndScript(pPlayer->GetTransform(), static_cast<PlayerScript*>(pPlayer->GetScriptOrNull()));

		HitEffectObject* pHitEffectObejct = new HitEffectObject(eHitEffectType::BLOOD, static_cast<PlayerScript*>(pPlayer->GetScriptOrNull()));
		pPlayer->SetHitEffectToPlayerScript(pHitEffectObejct);
		AddGameObject(pHitEffectObejct, eLayerType::EFFECT);


		PlayerScript* pPlayerScript = static_cast<PlayerScript*>(pPlayer->GetScriptOrNull());
		assert(pPlayerScript != nullptr);
		PlayerLevelUpEffectObject* pLevelUpEffectObject = new PlayerLevelUpEffectObject(pPlayerScript);
		AddGameObject(pLevelUpEffectObject, eLayerType::EFFECT);
		pPlayerScript->SetPlayerLevelUpEffectScript(static_cast<PlayerLevelUpEffectScript*>(pLevelUpEffectObject->GetScriptOrNull()));

		const float INDENCITY_VALUE = 4.0f;
		const float RADIUS = 10.0f;
		instantiateLightObject(LightingManager::makeLightAttribute(eLightType::POINT, Vector4(INDENCITY_VALUE, INDENCITY_VALUE, INDENCITY_VALUE, 1.0f), RADIUS), pPlayer->GetTransform());

		return pPlayerScript;
	}
#pragma endregion



#pragma region FG_AND_PARALLAX
	void PlayScene::instantiateParallaxObjects()
	{
		// ForeGround
		const float ASPECT_RATIO = 18.0f;
		const float MAG = 10.0f;
		const float FORE_GOROUND_MAG = 8.0f;
		const Vector3 FORE_GROUND_SCLAE_VECTOR(ASPECT_RATIO * FORE_GOROUND_MAG, FORE_GOROUND_MAG, 1.0f);


		const float PARALLAX_MAG = 6.0f;
		const float PARALLAX_ASPECT_RATIO = 12.8f;
		const Vector3 PARALLAX_BG_SCLAE_VECTOR(PARALLAX_ASPECT_RATIO * PARALLAX_MAG, PARALLAX_MAG, 1.0f);

		{
			BGForegroundObject* pForeGroundObject = Instantiate<BGForegroundObject>(eLayerType::BACKGROUND);
			pForeGroundObject->GetTransform()->SetScale(FORE_GROUND_SCLAE_VECTOR);
			pForeGroundObject->GetTransform()->SetPosition(Vector3(0.0f, -4.75f, BG_FOREGROUND_Z_VALUE));
		}

		{
			ParallaxObject* pParallaxOne = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_1_DEPTH);
			pParallaxOne->SetRenderer(ResourceMaker::BG_PARALLAX_MATERIAL_1_KEY);
			pParallaxOne->GetTransform()->SetScale(Vector3(30.0f, 30.0f, 1.0f));
			pParallaxOne->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, PARALLAX_1_DEPTH));

			ParallaxObject* pParallaxTwo = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_2_DEPTH);
			pParallaxTwo->SetRenderer(ResourceMaker::BG_PARALLAX_MATERIAL_2_KEY);
			pParallaxTwo->GetTransform()->SetScale(PARALLAX_BG_SCLAE_VECTOR);
			pParallaxTwo->GetTransform()->SetOnlyYPosition(-3.3f);

			ParallaxObject* pParallaxThree = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_3_DEPTH);
			pParallaxThree->SetRenderer(ResourceMaker::BG_PARALLAX_MATERIAL_3_KEY);
			pParallaxThree->GetTransform()->SetScale(PARALLAX_BG_SCLAE_VECTOR);
			pParallaxThree->GetTransform()->SetOnlyYPosition(-2.5f);

			ParallaxObject* pParallaxFour = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_4_DEPTH);
			pParallaxFour->SetRenderer(ResourceMaker::BG_PARALLAX_MATERIAL_4_KEY);
			pParallaxFour->GetTransform()->SetScale(PARALLAX_BG_SCLAE_VECTOR);
			pParallaxFour->GetTransform()->SetOnlyYPosition(-2.0f);

			//ParallaxObject* pParallaxFive = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_5_DEPTH);
			//pParallaxFive->SetRenderer(ResourceMaker::BG_PARALLAX_MATERIAL_5_KEY);
			//pParallaxFive->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));
			//pParallaxFive->GetTransform()->SetPosition(Vector3(0.0f, 1.1f, PARALLAX_5_DEPTH));

			//ParallaxObject* pParallaxSix = Instantiate<ParallaxObject>(eLayerType::BACKGROUND, PARALLAX_6_DEPTH);
			//pParallaxSix->SetRenderer(ResourceMaker::BG_PARALLAX_MATERIAL_6_KEY);
			//pParallaxSix->GetTransform()->SetScale(Vector3(ASPECT_RATIO * MAG, MAG, 1.0f));
			//pParallaxSix->GetTransform()->SetPosition(Vector3(0.0f, 0.6f, PARALLAX_6_DEPTH));
		}
	}
#pragma endregion
#pragma region ENV
	void PlayScene::instantiateEnvObject()
	{
		BGMoonObject* pBGMoon = Instantiate<BGMoonObject>(eLayerType::BACKGROUND);
		BGMushRoomStatueObject* pBGMushroomStatue = Instantiate<BGMushRoomStatueObject>(eLayerType::BACKGROUND);
		pBGMushroomStatue->SetPosition(-15.0f);


		instatiateLightningObejct();
		instatiateFlowerObejct();
		instatiateTreeObejct();
	}
	void PlayScene::instatiateTreeObejct()
	{
		const float X_DIFF_POS = 7.0f;
		instantiateEnvTreeObject(3.0f, eTreeShapeType::HIGH, eTreeAnimType::BLINK);
		instantiateEnvTreeObject(X_DIFF_POS, eTreeShapeType::WIDE, eTreeAnimType::MARKINGS);
		instantiateEnvTreeObject(X_DIFF_POS * 3, eTreeShapeType::HIGH, eTreeAnimType::BLOOD);
		instantiateEnvTreeObject(X_DIFF_POS * 4, eTreeShapeType::WIDE, eTreeAnimType::OVER_GROWN);


		instantiateEnvTreeObject(-5.0f, eTreeShapeType::WIDE, eTreeAnimType::BLOOD);
		instantiateEnvTreeObject(-X_DIFF_POS - 3.0f, eTreeShapeType::HIGH, eTreeAnimType::MARKINGS);
		instantiateEnvTreeObject(-(X_DIFF_POS * 3), eTreeShapeType::WIDE, eTreeAnimType::BLINK);
		instantiateEnvTreeObject(-(X_DIFF_POS * 4), eTreeShapeType::WIDE, eTreeAnimType::BLOOD);
		instantiateEnvTreeObject(-(X_DIFF_POS * 5), eTreeShapeType::HIGH, eTreeAnimType::OVER_GROWN);
	}
	void PlayScene::instantiateEnvTreeObject(const float xPos, const eTreeShapeType eTreeType, const eTreeAnimType eAnimType)
	{
		BGTreeObject* pBGTreeObject = new BGTreeObject(eTreeType, eAnimType);
		pBGTreeObject->GetTransform()->SetOnlyXPosition(xPos);
		this->AddGameObject(pBGTreeObject, eLayerType::BACKGROUND);
		BGTorchObject* pBGTorch = Instantiate<BGTorchObject>(eLayerType::BACKGROUND);
		pBGTorch->SetPosition(xPos);
	}
#pragma endregion
#pragma region LIGHTING
	void PlayScene::instatiateLightningObejct()
	{
		const Vector4 DIFFUSE(1.0f, 1.0f, 1.0f, 1.0f);
		const float RADIUS = 2.0f;
		BGLightningObject* pBGLargeLightning = new BGLightningObject(eBGLightningType::LARGE);
		pBGLargeLightning->SetPosition(15.7f);
		this->AddGameObject(pBGLargeLightning, eLayerType::BACKGROUND);
		instantiateLightObject(LightingManager::makeLightAttribute(eLightType::POINT, DIFFUSE, RADIUS), pBGLargeLightning->GetTransform());

		pBGLargeLightning = new BGLightningObject(eBGLightningType::LARGE);
		pBGLargeLightning->SetPosition(-56.1f);
		this->AddGameObject(pBGLargeLightning, eLayerType::BACKGROUND);
		instantiateLightObject(LightingManager::makeLightAttribute(eLightType::POINT, DIFFUSE, RADIUS), pBGLargeLightning->GetTransform());


		BGLightningObject* pBGSmallLightning = new BGLightningObject(eBGLightningType::SMALL);
		pBGSmallLightning->SetPosition(34.0f);
		this->AddGameObject(pBGSmallLightning, eLayerType::BACKGROUND);
		instantiateLightObject(LightingManager::makeLightAttribute(eLightType::POINT, DIFFUSE, RADIUS), pBGSmallLightning->GetTransform());

		pBGSmallLightning = new BGLightningObject(eBGLightningType::SMALL);
		pBGSmallLightning->SetPosition(-15.0f);
		this->AddGameObject(pBGSmallLightning, eLayerType::BACKGROUND);
		instantiateLightObject(LightingManager::makeLightAttribute(eLightType::POINT, DIFFUSE, RADIUS), pBGSmallLightning->GetTransform());

	}
	void PlayScene::instantiateLightObject(const LightAttribute& lightAttribute, const jh::math::Vector2& pos)
	{
		GameObject* pLightObject = Instantiate<GameObject>(eLayerType::PARTICLE);
		if (lightAttribute.ELightType == eLightType::DIRECTIONAL)
		{
			pLightObject->GetTransform()->SetPosition(Vector3(pos.x, pos.y, -10.0f));
		}
		else
		{
			pLightObject->GetTransform()->SetPosition(Vector3(pos.x, pos.y, BG_LIGHT_Z_VALUE));
		}
		Light* pLightComponent = new Light(lightAttribute);
		pLightObject->AddComponent(pLightComponent);
	}
	void PlayScene::instantiateLightObject(const LightAttribute& lightAttribute, Transform* pTransform)
	{
		assert(pTransform != nullptr);
		GameObject* pLightObject = Instantiate<GameObject>(eLayerType::PARTICLE);
		pLightObject->GetTransform()->SetPosition(Vector3(0.0f, 0.0f, BG_LIGHT_Z_VALUE));
		Light* pLightComponent = new Light(lightAttribute);
		pLightObject->AddComponent(pLightComponent);
		pLightComponent->SetFollowingTransform(pTransform);
	}
	void PlayScene::instantiateLight(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		// Directional Light
		{
			//instantiateLightObject(LightingManager::makeLightAttribute(eLightType::DIRECTIONAL, Vector4(4.0f, 4.0f, 4.0f, 1.0f), 0.0f), Vector2(0.0f, -5.0f));
		}
		// Point Light
		{
			//LightAttribute lightAttribute;
			//ZeroMemory(&lightAttribute, sizeof(LightAttribute));
			//lightAttribute.ELightType = eLightType::POINT;
			//lightAttribute.Diffuse = WHITE_COLOR;
			//lightAttribute.Radius = 15.0f;
			//instantiateLightObject(lightAttribute, Vector2(0.0f, 0.0f));
		}
	}

#pragma endregion

#pragma endregion
#pragma region ADD_GAME_OBECJT
	void PlayScene::AddMonster(const MonsterPackage& monPack)
	{
		assert(monPack.pMonster != nullptr && monPack.pHitEffectObejct != nullptr && monPack.pMonsterAttackColliderObject != nullptr && monPack.pUIHpBarObject != nullptr);
		this->AddGameObject(monPack.pMonster, eLayerType::MONSTER);
		this->AddGameObject(monPack.pHitEffectObejct, eLayerType::MONSTER_EFFECT);
		this->AddGameObject(monPack.pMonsterAttackColliderObject, eLayerType::MONSTER_ATTACK_COLLIDER);
		this->AddGameObject(monPack.pUIHpBarObject, eLayerType::MONSTER_UI);
	}

	void PlayScene::AddBossMonster(AcientBossMonsterPackage& monPack)
	{
		assert(monPack.pMonster != nullptr && monPack.pHitEffectObejct != nullptr);
		for (UINT i = 0; i < static_cast<UINT>(eBossMonsterColliderType::COUNT); ++i)
		{
			assert(monPack.pColliderObject[i] != nullptr);
		}
		this->AddGameObject(monPack.pMonster, eLayerType::MONSTER);
		this->AddGameObject(monPack.pHitEffectObejct, eLayerType::MONSTER_EFFECT);
		this->AddGameObject(monPack.pUIHpBarObject, eLayerType::MONSTER_UI);
		for (UINT i = 0; i < static_cast<UINT>(eBossMonsterColliderType::COUNT); ++i)
		{
			this->AddGameObject(monPack.pColliderObject[i], eLayerType::MONSTER_ATTACK_COLLIDER);
		}
	}

	void PlayScene::AddSkillObejct(GameObject* pGameObject)
	{
		assert(pGameObject != nullptr);
		this->AddGameObject(pGameObject, eLayerType::PLAYER_SKILL);
	}

	void PlayScene::AddSFXObject(const eSFXType eType)
	{
		GameObject* pAuidoObject = new GameObject();
		//pAuidoObject->GetTransform()->SetParent(mpPlayerScript->GetOwner());

		AudioSource* pAudioSource = new AudioSource(ResourceMaker::GetInstance().GetAudioClipOrNull(eType));
		pAuidoObject->AddComponent(pAudioSource);

		AudioSorceScript* pScript = new AudioSorceScript(mpPlayerScript->GetOwner()->GetTransform());
		pAuidoObject->AddScript(pScript);

		this->AddGameObject(pAuidoObject, eLayerType::SFX);
		SFXManager::GetInstance().SetAudioSource(eType, pAudioSource);
	}
#pragma endregion
}
