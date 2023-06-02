#include "jhBGForegroundObject.h"
#include "jhSpriteRenderer.h"
#include "jhResourceMaker.h"
#include "jhResourcesManager.h"
#include "jhMaterial.h"
#include "jhMesh.h"

namespace jh
{
	BGForegroundObject::BGForegroundObject()
		: GameObject(eLayerType::BACKGROUND)
	{
		setRenderer();
	}
	void BGForegroundObject::Initialize()
	{
		GameObject::Initialize();
	}
	void BGForegroundObject::Update()
	{
		GameObject::Update();
	}
	void BGForegroundObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void BGForegroundObject::Render()
	{
		GameObject::Render();
	}
	void BGForegroundObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_NORMAL_MAP_MESH_KEY);
		assert(pMesh != nullptr);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_FOREGROUND_NORMALMAP_MATERIAL_KEY);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
}