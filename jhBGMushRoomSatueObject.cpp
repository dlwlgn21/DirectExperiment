#include "jhBGMushRoomSatueObject.h"
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
	const float BGMushRoomStatueObject::BG_MUSHROOM_STATUE_Y_VALUE = -0.1f;

	BGMushRoomStatueObject::BGMushRoomStatueObject()
		: AnimatedGameObject()
	{
		const float BG_MUSHROOM_STATUE_SCALE_VALUE = 10.0f;
		setAnimator();
		setRenderer();
		GetTransform()->SetOnlyXYScale(BG_MUSHROOM_STATUE_SCALE_VALUE);
	}
	void BGMushRoomStatueObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_MUSHROOM_STATUE_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		// FLYING
		const float WIDTH = 192.0f;
		const float HEIGHT = 192.0f;
		const float MAG = 200.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		const UINT SPLIT_ANIM_COUNT = static_cast<UINT>(pAtlas->GetWidth() / WIDTH);
		Animator* pAnimator = new Animator();
		pAnimator->Create(
			L"MushRoomAnimKey",
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			SPLIT_ANIM_COUNT,
			0.1f,
			MAG
		);
		this->AddComponent(pAnimator);
		Animation* pAnim = pAnimator->FindAnimationOrNull(L"MushRoomAnimKey");
		assert(pAnim != nullptr);
		pAnim->SetHorizontalFlip(true);
		pAnimator->PlayAnimation(L"MushRoomAnimKey", true);
	}
	void BGMushRoomStatueObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_MUSHROOM_STATUE_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void BGMushRoomStatueObject::SetPosition(const float xPos)
	{
		GetTransform()->SetPosition(Vector3(xPos, BG_MUSHROOM_STATUE_Y_VALUE, BG_MUSHROOM_STATUE_Z_VALUE));
	}

}