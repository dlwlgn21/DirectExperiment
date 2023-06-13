#include "jhUILevelUPBorderObject.h"
#include "jhUILevelUpBorderScript.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"
#include "jhResourcesManager.h"
#include "jhResourceMaker.h"
#include "jhTransform.h"
#include "jhLayerZValue.h"

using namespace jh::math;


static constexpr const float WAIT_Y_POS = 10.0f;

namespace jh
{
	UILevelUpBorderObject::UILevelUpBorderObject()
		: GameObject()
	{
		setRenderer();
		setScript();
		setTransform();
	}

	void UILevelUpBorderObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_MATERIAL_LEVEL_UP_BORDER_KEY);
		assert(pMesh != nullptr && pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void UILevelUpBorderObject::setScript()
	{
		Script* pScript = new UILevelUpBorderScript();
		this->AddScript(pScript);
	}

	void UILevelUpBorderObject::setTransform()
	{
		GetTransform()->SetPosition(Vector3(0.0f, WAIT_Y_POS, LEVEL_UP_UI_Z_VALUE));
		GetTransform()->SetOnlyXYScale(8.0f);
	}


}
