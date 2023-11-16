#include "jhBGTreeObject.h"
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
	BGTreeObject::BGTreeObject(const eTreeShapeType eShapeType, const eTreeAnimType eAnimType)
		: AnimatedGameObject()
		, meTreeShapeType(eShapeType)
		, meTreeAnimType(eAnimType)
	{
		const float SCALE_VALUE = 10.0f;
		setAnimator();
		setRenderer();
		switch (meTreeShapeType)
		{
		case eTreeShapeType::HIGH:
		{
			GetTransform()->SetPosition(Vector3(-5.0f, 0.45f, BG_TREE_Z_VALUE));
			break;
		}
		case eTreeShapeType::WIDE:
		{
			GetTransform()->SetPosition(Vector3(-5.0f, -0.35f, BG_TREE_Z_VALUE));
			break;
		}
		default:
			assert(false);
			break;
		}
		GetTransform()->SetOnlyXYScale(SCALE_VALUE, SCALE_VALUE);
	}
	void BGTreeObject::setAnimator()
	{
		const float MAG = 200.0f;
		const float ANIM_DURATION = 0.15f;
		Animator* pAnimator = new Animator();
		switch (meTreeShapeType)
		{
		case eTreeShapeType::HIGH:
		{
			Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_TREE_1_TEXTURE_KEY);
			const float WIDTH = 112.0f;
			const float HEIGHT = 128.0f;
			const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
			const Vector2 OFFSET(Vector2::Zero);
			switch (meTreeAnimType)
			{
			case eTreeAnimType::BLOOD:
			{
				makeAnimation(pAnimator, pAtlas, Vector2::Zero, ANIM_SIZE, OFFSET, 8, ANIM_DURATION, MAG);
				break;
			}
			case eTreeAnimType::MARKINGS:
			{
				makeAnimation(pAnimator, pAtlas, Vector2(0.0f, HEIGHT), ANIM_SIZE, OFFSET, 13, ANIM_DURATION, MAG);
				break;
			}
			case eTreeAnimType::BLINK:
			{
				makeAnimation(pAnimator, pAtlas, Vector2(0.0f, HEIGHT * 2), ANIM_SIZE, OFFSET, 8, ANIM_DURATION, MAG);
				break;
			}
			case eTreeAnimType::OVER_GROWN:
			{
				makeAnimation(pAnimator, pAtlas, Vector2(0.0f, HEIGHT * 3), ANIM_SIZE, OFFSET, 16, ANIM_DURATION, MAG);
				break;
			}
			default:
				assert(false);
				break;
			}
		}
		break;
		case eTreeShapeType::WIDE:
		{
			Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_TREE_2_TEXTURE_KEY);
			const float WIDTH = 128.0f;
			const float HEIGHT = 96.0f;
			const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
			const Vector2 OFFSET(Vector2::Zero);
			switch (meTreeAnimType)
			{
			case eTreeAnimType::BLOOD:
			{
				makeAnimation(pAnimator, pAtlas, Vector2::Zero, ANIM_SIZE, OFFSET, 8, ANIM_DURATION, MAG);
				break;
			}
			case eTreeAnimType::MARKINGS:
			{
				makeAnimation(pAnimator, pAtlas, Vector2(0.0f, HEIGHT), ANIM_SIZE, OFFSET, 15, ANIM_DURATION, MAG);
				break;
			}
			case eTreeAnimType::BLINK:
			{
				makeAnimation(pAnimator, pAtlas, Vector2(0.0f, HEIGHT * 2), ANIM_SIZE, OFFSET, 8, ANIM_DURATION, MAG);
				break;
			}
			case eTreeAnimType::OVER_GROWN:
			{
				makeAnimation(pAnimator, pAtlas, Vector2(0.0f, HEIGHT * 3), ANIM_SIZE, OFFSET, 16, ANIM_DURATION, MAG);
				break;
			}
			default:
				assert(false);
				break;
			}
		}
		break;
		default:
			assert(false);
			break;
		}
		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(L"TreeAnimKey", true);
	}
	void BGTreeObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = nullptr;
		switch (meTreeShapeType)
		{
		case eTreeShapeType::HIGH:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_TREE_1_MATERIAL_KEY);
			break;
		}
		case eTreeShapeType::WIDE:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_TREE_2_MATERIAL_KEY);
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


	void BGTreeObject::makeAnimation(Animator* pAnimator, Texture* pAtalsImage, const jh::math::Vector2 leftTop, const jh::math::Vector2 seperatingSize, const jh::math::Vector2 offset, const UINT spriteCount, const float duration, const float magnification)
	{
		assert(pAnimator != nullptr && pAtalsImage != nullptr);
		pAnimator->Create(
			L"TreeAnimKey",
			pAtalsImage,
			leftTop,
			seperatingSize,
			offset,
			spriteCount,
			duration,
			magnification
		);
	}
}