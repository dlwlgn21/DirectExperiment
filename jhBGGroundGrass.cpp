#include "jhBGGroundGrass.h"
#include "jhMath.h"
#include "jhTransform.h"
#include "jhTexture.h"
#include "jhResourceMaker.h"
#include "jhResourcesManager.h"
#include "jhAnimator.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"
#include "jhLayerZValue.h"


using namespace jh::math;

namespace jh
{
	const float BGGroundGrassObject::BG_FOREGROUND_GRASS_Y_VALUE = -2.75f;

	BGGroundGrassObject::BGGroundGrassObject()
		: AnimatedGameObject()
	{
		const float BG_GRASS_SCALE_VALUE = 8.0f;
		setAnimator();
		setRenderer();
		GetTransform()->SetOnlyXYScale(BG_GRASS_SCALE_VALUE);
	}
	void BGGroundGrassObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_FOREGROUND_GRASS_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		// FLYING
		const float WIDTH = 212.0f;
		const float HEIGHT = 11.0f;
		const float MAG = 400.0f;
		const Vector2 ANIN_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(Vector2::Zero);
		const UINT SPLIT_ANIM_COUNT = static_cast<UINT>(pAtlas->GetWidth() / WIDTH);
		Animator* pAnimator = new Animator();
		pAnimator->Create(
			L"GrassAnimKey",
			pAtlas,
			Vector2::Zero,
			ANIN_SIZE,
			OFFSET,
			SPLIT_ANIM_COUNT,
			0.1f,
			MAG
		);
		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(L"GrassAnimKey", true);
	}
	void BGGroundGrassObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_TORCH_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void BGGroundGrassObject::SetPosition(const float xPos)
	{
		GetTransform()->SetPosition(Vector3(xPos, BG_FOREGROUND_GRASS_Y_VALUE, BG_FOREGROUND_GRASS_Z_VALUE));
	}
}