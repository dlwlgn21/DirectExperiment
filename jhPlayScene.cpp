#include "jhPlayScene.h"
#include "jhResourcesManager.h"
#include "jhResourceMaker.h"
#include "jhGameObject.h"
#include "jhHelper.h"
#include "jhSpriteRenderer.h"
#include "jhPlayerScript.h"
#include "jhMonsterScript.h"


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
		GameObject* pPlayer = Intantiate<GameObject>(eLayerType::PLAYER);
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		assert(pMesh != nullptr);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::LOGO_MATERIAL_KEY);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		pPlayer->AddComponent(pSpriteRenderer);

		PlayerScript* pScript = new PlayerScript();
		pPlayer->AddScript(pScript);



		GameObject* pMonster = Intantiate<GameObject>(eLayerType::MONSTER);
		SpriteRenderer* pMonsterSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		pMonster->AddComponent(pMonsterSpriteRenderer);

		MonsterScript* pMonsterScript = new MonsterScript();
		pMonster->AddScript(pMonsterScript);

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

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::Release()
	{
		Scene::Release();
	}
}
