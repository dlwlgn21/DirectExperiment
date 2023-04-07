#include "jhSword.h"
#include "jhResourceMaker.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhAnimator.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"

using namespace jh::math;

namespace jh
{
	Sword::Sword()
		: AnimatedGameObject()
	{
		setAnimator();
		setRenderer();
		setScript();
	}

	void Sword::Initialize()
	{
		AnimatedGameObject::Initialize();
	}
	void Sword::Update()
	{
		AnimatedGameObject::Update();
	}
	void Sword::FixedUpdate()
	{
		AnimatedGameObject::FixedUpdate();
	}
	void Sword::Render()
	{
		AnimatedGameObject::Render();
	}

	void Sword::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::WEAPON_SWORD_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 64.0f;
		const float HEIGHT = 85.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		Animator* pAnimator = new Animator();
		pAnimator->Create(
			L"SwingTopDown",
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			12,
			0.05f,
			100
		);
		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(L"SwingTopDown", true);
	}
	void Sword::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::WEAPON_SWORD_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void Sword::setScript()
	{
	}
}