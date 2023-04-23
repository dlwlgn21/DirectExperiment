#include "jhUIObject.h"
#include "jhResourceMaker.h"
#include "jhSpriteRenderer.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhMath.h"
#include "jhTransform.h"

using namespace jh::math;

namespace jh
{
	UIObject::UIObject()
		: GameObject(eLayerType::UI)
	{
		setRenderer();
	}

	void UIObject::Initialize()
	{
		GetTransform()->SetPosition(Vector3(0.0f, -2.0f, 1.0f));
		GetTransform()->SetScale(Vector3(3.0f, 1.0f, 1.0f));
		GameObject::Initialize();
	}
	void UIObject::Update()
	{
		GameObject::Update();
	}
	void UIObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void UIObject::Render()
	{
		GameObject::Render();
	}
	void UIObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_HP_BORDER_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
}