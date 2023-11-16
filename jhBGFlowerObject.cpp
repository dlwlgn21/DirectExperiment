#include "jhBGFlowerObject.h"
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
	const float BGFlowerObject::BG_FLOWER_Y_VALUE = -2.4f;

	BGFlowerObject::BGFlowerObject()
		: AnimatedGameObject()
	{
		const float BG_FLOWER_SCALE_VALUE = 10.0f;
		setAnimator();
		setRenderer();
		GetTransform()->SetOnlyXYScale(BG_FLOWER_SCALE_VALUE);
	}
	void BGFlowerObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_FLOWER_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		// FLYING
		const float WIDTH = 16.0f;
		const float HEIGHT = 16.0f;
		const float MAG = 200.0f;
		const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(Vector2::Zero);
		const UINT SPLIT_ANIM_COUNT = static_cast<UINT>(pAtlas->GetWidth() / WIDTH);
		Animator* pAnimator = new Animator();
		pAnimator->Create(
			L"FlowerAnimKey",
			pAtlas,
			Vector2::Zero,
			ANIM_SIZE,
			OFFSET,
			SPLIT_ANIM_COUNT,
			0.1f,
			MAG
		);
		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(L"FlowerAnimKey", true);
	}
	void BGFlowerObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_FLOWER_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void BGFlowerObject::SetPosition(const float xPos)
	{
		GetTransform()->SetPosition(Vector3(xPos, BG_FLOWER_Y_VALUE, BG_FLOWER_Z_VALUE));
	}

}