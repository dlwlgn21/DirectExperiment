#include "jhUITimeBarObject.h"
#include "jhSpriteRendererIncludeFiles.h"
#include "jhTransform.h"
#include "jhUITimeBarScript.h"
using namespace jh::math;

namespace jh
{
	UITimeBarObject::UITimeBarObject()
		: GameObject()
	{
		setRenderer();
		setScript();
		setTransform();
	}

	void UITimeBarObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_MATERIAL_TIME_BAR_KEY);
		assert(pMesh != nullptr && pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void UITimeBarObject::setScript()
	{
		UITimeBarScript* pScript = new UITimeBarScript();
		this->AddScript(pScript);
	}

	void UITimeBarObject::setTransform()
	{
		GetTransform()->SetScale(Vector3(10.0f, 0.1f, 1.0f));
		GetTransform()->SetPosition(Vector3(0.0f, 4.0f + 2.0f, 1.0f));
	}
}