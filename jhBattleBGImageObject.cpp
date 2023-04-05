#include "jhBattleBGImageObject.h"
#include "jhSpriteRenderer.h"
#include "jhResourceMaker.h"
#include "jhResourcesManager.h"
#include "jhMaterial.h"
#include "jhMesh.h"
#include "jhBattleBGScript.h"

namespace jh
{
	BattleBGImageObject::BattleBGImageObject()
		: GameObject()
	{
		setRenderer();
		setScript();
	}
	void BattleBGImageObject::Initialize()
	{
		GameObject::Initialize();
	}
	void BattleBGImageObject::Update()
	{
		GameObject::Update();
	}
	void BattleBGImageObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void BattleBGImageObject::Render()
	{
		GameObject::Render();
	}
	void BattleBGImageObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::BATTLE_BG_MESH_KEY);
		assert(pMesh != nullptr);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BATTLE_BG_MATERIAL_KEY);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void BattleBGImageObject::setScript()
	{
		BattleBGScript* pScript = new BattleBGScript();
		this->AddScript(pScript);
	}
}