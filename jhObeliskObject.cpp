#include "jhObeliskObject.h"
#include "jhMath.h"
#include "jhTransform.h"
#include "jhTexture.h"
#include "jhResourceMaker.h"
#include "jhResourcesManager.h"
#include "jhAnimator.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"

using namespace jh::math;

namespace jh
{
	ObeliskObject::ObeliskObject()
		: AnimatedGameObject()
	{
		setAnimator();
		setRenderer();
		Vector3 prePos = GetTransform()->GetPosition();
		GetTransform()->SetPosition(Vector3(-10.0f, 0.45f, 4.0f));
		GetTransform()->SetScale(Vector3(10.0f, 10.0f, 1.0f));
	}
	void ObeliskObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_OBELISK_TEXTURE_ATLAS_KEY);
		assert(pAtlas != nullptr);
		// FLYING
		const float WIDTH = 190.0f;
		const float HEIGHT = 380.0f;
		const float MAG = 500.0f;

		//const float WIDTH = 190.0f;
		//const float HEIGHT = 240.0f;
		//const float MAG = 250.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		Animator* pAnimator = new Animator();
		pAnimator->Create(
			L"ObeliskAnimKey",
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			14,
			0.15f,
			MAG
		);
		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(L"ObeliskAnimKey", true);
	}
	void ObeliskObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_NORMAL_MAP_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_OBELISK_NORMAL_MAP_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
}