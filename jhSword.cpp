#include "jhSword.h"
#include "jhResourceMaker.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhOnceAnimator.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"
#include "jhWeaponScript.h"
#include "jhPlayerScript.h"
#include "jhAnimation.h"
using namespace jh::math;

namespace jh
{
	Sword::Sword()
		: AnimatedGameObject()
		, mpPlayerScript(nullptr)
	{
		setAnimator();
		setRenderer();
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

	void Sword::SetScript(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		mpPlayerScript = pPlayerScript;
		setScript();
	}

	void Sword::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::WEAPON_SWORD_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 64.0f;
		const float HEIGHT = 85.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		Animation* pAnimation = pAnimator->Create(
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
		pAnimator->SetCurrentAnimation(pAnimation);
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
		assert(mpPlayerScript != nullptr);
		WeaponScript* pScript = new WeaponScript(mpPlayerScript);
		this->AddScript(pScript);
	}
}