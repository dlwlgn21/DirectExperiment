#include "jhUISkillSelectBoxObject.h"
#include "jhSpriteRendererIncludeFiles.h"
#include "jhTransform.h"
#include "jhLayerZValue.h"
#include "jhUISkillSelectBoxScript.h"

using namespace jh::math;

static constexpr const float WAIT_Y_POS = 10.0f;

namespace jh
{
	UISkillSelectBoxObject::UISkillSelectBoxObject()
		: GameObject()
	{
		setRenderer();
		setScript();
		setTransform();
	}

	void UISkillSelectBoxObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_SELECT_BOX_MATERIAL_KEY);
		assert(pMesh != nullptr && pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void UISkillSelectBoxObject::setScript()
	{
		Script* pScript = new UISkillSelectBoxScript();
		this->AddScript(pScript);
	}

	void UISkillSelectBoxObject::setTransform()
	{
		GetTransform()->SetPosition(Vector3(0.0f, WAIT_Y_POS, LEVEL_UP_UI_SKILL_SELECT_BOX_Z_VALUE));
		GetTransform()->SetOnlyXYScale(8.0f, 2.0f);
	}
}
