#include "jhProtectCrystalObject.h"
#include "jhSpriteRendererIncludeFiles.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhCollider2D.h"
#include "jhLayerZValue.h"
#include "jhProtectingCrystalScript.h"

using namespace jh::math;

namespace jh
{
	ProtectingCrystalObject::ProtectingCrystalObject()
		: AnimatedGameObject()
	{
		setAnimator();
		setRenderer();
		setScript();
		setCollider();
		GetTransform()->SetOnlyXYScale(3.0f);
		GetTransform()->SetPosition(Vector3(-2.0f, 5.0f, PROTECTING_CRYSTAL_Z_VALUE));
	}
	void ProtectingCrystalObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::PROTECT_CRYSTAL_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 64.0f;
		const float HEIGHT = 64.0f;
		const float MAG = 100.0f;
		const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(Vector2::Zero);
		Animator* pAnimator = new Animator();
		pAnimator->Create(
			L"CrystalKey",
			pAtlas,
			Vector2::Zero,
			ANIM_SIZE,
			OFFSET,
			24,
			0.15f,
			MAG
		);
		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(L"CrystalKey", true);
	}
	void ProtectingCrystalObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::PROTECT_CRYSTAL_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void ProtectingCrystalObject::setScript()
	{
		ProtectingCrystalScript* pScript = new ProtectingCrystalScript();
		this->AddScript(pScript);
	}

	void ProtectingCrystalObject::setCollider()
	{
		Collider2D* pCollider = new Collider2D(eColliderLayerType::PROTECTING_OBJECT);
		this->AddComponent(pCollider);

		pCollider->SetSize(Vector2(0.25f, 0.5f));
	}

}