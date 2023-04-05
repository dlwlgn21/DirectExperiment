#include "jhBattleParrarellImageObject.h"


namespace jh
{
	BattleParrarellImageObject::BattleParrarellImageObject()
		: GameObject()
	{
		setRenderer();
		setScript();
	}
	void BattleParrarellImageObject::Initialize()
	{
		GameObject::Initialize();
	}
	void BattleParrarellImageObject::Update()
	{
		GameObject::Update();
	}
	void BattleParrarellImageObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void BattleParrarellImageObject::Render()
	{
		GameObject::Render();
	}
	void BattleParrarellImageObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::BATTLE_BG_MESH_KEY);
		assert(pMesh != nullptr);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BATTLE_PARRARELL_BG_MATERIAL_KEY);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void BattleParrarellImageObject::setScript()
	{
		BattleBGScript* pScript = new BattleBGScript(eBGType::PARRARELL);
		this->AddScript(pScript);
	}
}