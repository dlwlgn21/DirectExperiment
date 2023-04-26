#include "jhBGMoonObject.h"
#include "jhResourceMaker.h"
#include "jhMaterial.h"
#include "jhMesh.h"
#include "jhSpriteRenderer.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
using namespace jh::math;

namespace jh
{
	BGMoonObject::BGMoonObject()
		: AnimatedGameObject()
	{
		setAnimator();
		setRenderer();
		setScript();
	}

	void BGMoonObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_MOON_ATLAS_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 48.0;
		const float HEIGHT = 48.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		Animator* pAnimator = new Animator();
		pAnimator->Create(
			L"MoonSpinAnimKey",
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			60,
			0.2f,
			120
		);
		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(L"MoonSpinAnimKey", true);
	}
	void BGMoonObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_MOON_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void BGMoonObject::setScript()
	{

	}
}