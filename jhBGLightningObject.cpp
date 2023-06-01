#include "jhBGLightningObject.h"
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
	const float BGLightningObject::BG_LARGE_LIGHTNING_Y_VALUE = -2.0f;
	const float BGLightningObject::BG_SAMLL_LIGHTNING_Y_VALUE = -2.0f;

	BGLightningObject::BGLightningObject(const eBGLightningType eLightningType)
		: AnimatedGameObject()
		, meType(eLightningType)
	{
		const float BG_LARGE_LIGHTNING_SCALE_VALUE = 10.0f;
		const float BG_SMALL_LIGHTNING_SCALE_VALUE = 10.0f;
		setAnimator();
		setRenderer();
		
		switch (meType)
		{
		case eBGLightningType::LARGE:
		{
			GetTransform()->SetOnlyXYScale(BG_LARGE_LIGHTNING_SCALE_VALUE);
			break;
		}
		case eBGLightningType::SMALL:
		{
			GetTransform()->SetOnlyXYScale(BG_SMALL_LIGHTNING_SCALE_VALUE);
			break;
		}
		default:
			assert(false);
			break;
		}
	}
	void BGLightningObject::setAnimator()
	{
		Texture* pAtlas;
		Animator* pAnimator = new Animator();

		switch (meType)
		{
		case eBGLightningType::LARGE:
		{
			pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_LARGE_LIGHTNING_TEXTURE_KEY);
			assert(pAtlas != nullptr);
			const float WIDTH = 64.0f;
			const float HEIGHT = 48.0f;
			const float MAG = 200.0f;
			const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
			const Vector2 OFFSET(Vector2::Zero);
			const UINT SPLIT_ANIM_COUNT = static_cast<UINT>(pAtlas->GetHeight() / HEIGHT);
			pAnimator->CreateVertical(
				L"LightningAnimKey",
				pAtlas,
				Vector2::Zero,
				ANIM_SIZE,
				OFFSET,
				SPLIT_ANIM_COUNT,
				0.1f,
				MAG
			);
			break;
		}
		case eBGLightningType::SMALL:
		{
			pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_SMALL_LIGHTNING_TEXTURE_KEY);
			assert(pAtlas != nullptr);
			const float WIDTH = 32.0f;
			const float HEIGHT = 32.0f;
			const float MAG = 200.0f;
			const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
			const Vector2 OFFSET(Vector2::Zero);
			const UINT SPLIT_ANIM_COUNT = static_cast<UINT>(pAtlas->GetHeight() / HEIGHT);
			pAnimator->CreateVertical(
				L"LightningAnimKey",
				pAtlas,
				Vector2::Zero,
				ANIM_SIZE,
				OFFSET,
				SPLIT_ANIM_COUNT,
				0.1f,
				MAG
			);
			break;
		}
		default:
			assert(false);
			break;
		}

		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(L"LightningAnimKey", true);
	}
	void BGLightningObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_NORMAL_MAP_MESH_KEY);
		Material* pMaterial = nullptr;
		switch (meType)
		{
		case eBGLightningType::LARGE:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_LARGE_LIGHTNING_NORMAL_MAP_MATERIAL_KEY);
			break;
		}
		case eBGLightningType::SMALL:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_SMALL_LIGHTNING_NORMAL_MAP_MATERIAL_KEY);
			break;
		}
		default:
			assert(false);
			break;
		}

		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void BGLightningObject::SetPosition(const float xPos)
	{
		switch (meType)
		{
		case eBGLightningType::LARGE:
		{
			GetTransform()->SetPosition(Vector3(xPos, BG_LARGE_LIGHTNING_Y_VALUE, BG_LARGE_LIGHTNING__Z_VALUE));
			break;
		}
		case eBGLightningType::SMALL:
		{
			GetTransform()->SetPosition(Vector3(xPos, BG_SAMLL_LIGHTNING_Y_VALUE, BG_LARGE_LIGHTNING__Z_VALUE));
			break;
		}
		default:
			assert(false);
			break;
		}
	}

}