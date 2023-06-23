#include "jhGameCompleteObject.h"
#include "jhSpriteRendererIncludeFiles.h"
#include "jhTransform.h"
#include "jhGameCompleteScript.h"
using namespace jh::math;

namespace jh
{
	GameCompleteObject::GameCompleteObject()
		: GameObject()
	{
		setRenderer();
		setScript();
		setTransform();
	}

	void GameCompleteObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_MATERIAL_GAME_COMPLETE_KEY);
		assert(pMesh != nullptr && pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void GameCompleteObject::setTransform()
	{
		GetTransform()->SetPosition(Vector3(0.0f, 1.0f, 1.0f));
		GetTransform()->SetOnlyXYScale(7.0f);
	}

	void GameCompleteObject::setScript()
	{
		GameCompleteScript* pScript = new GameCompleteScript();
		this->AddScript(pScript);
	}
}