#include "jhBGTorchObject.h"
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
	const float BGTorchObject::BG_TORCH_Y_VALUE = -2.4f;

	BGTorchObject::BGTorchObject()
		: AnimatedGameObject()
	{
		const float BG_TORCH_SCALE_VALUE = 10.0f;
		setAnimator();
		setRenderer();
		GetTransform()->SetOnlyXYScale(BG_TORCH_SCALE_VALUE);
	}
	void BGTorchObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_TORCH_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		// FLYING
		const float WIDTH = 16.0f;
		const float HEIGHT = 16.0f;
		const float MAG = 200.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		const UINT SPLIT_ANIM_COUNT = static_cast<UINT>(pAtlas->GetWidth() / WIDTH);
		Animator* pAnimator = new Animator();
		pAnimator->Create(
			L"TorchAnimKey",
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			SPLIT_ANIM_COUNT,
			0.1f,
			MAG
		);
		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(L"TorchAnimKey", true);
	}
	void BGTorchObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_TORCH_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void BGTorchObject::SetPosition(const float xPos)
	{
		GetTransform()->SetPosition(Vector3(xPos, BG_TORCH_Y_VALUE, BG_TORCH_Z_VALUE));
	}

}