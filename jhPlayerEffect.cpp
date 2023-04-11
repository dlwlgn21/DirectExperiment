#include "jhPlayerEffect.h"
#include "jhResourceMaker.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhOnceAnimator.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"
#include "jhEffectScript.h"
#include "jhPlayerScript.h"
#include "jhAnimation.h"

using namespace jh::math;

namespace jh
{
	PlayerEffect::PlayerEffect()
		: AnimatedGameObject()
		, mpPlayerScript(nullptr)
	{
		setAnimator();
		setRenderer();
	}

	void PlayerEffect::Initialize()
	{
		AnimatedGameObject::Initialize();
	}
	void PlayerEffect::Update()
	{
		AnimatedGameObject::Update();
	}
	void PlayerEffect::FixedUpdate()
	{
		AnimatedGameObject::FixedUpdate();
	}
	void PlayerEffect::Render()
	{
		AnimatedGameObject::Render();
	}

	void PlayerEffect::SetScript(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		mpPlayerScript = pPlayerScript;
		setScript();
	}

	void PlayerEffect::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::EFFECT_SWORD_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 109.0f;
		const float HEIGHT = 38.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		Animation* pAnimation = pAnimator->Create(
			L"SwordSwingEffect",
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
	void PlayerEffect::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::EFFECT_SWORD_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);

	}
	void PlayerEffect::setScript()
	{
		assert(mpPlayerScript != nullptr);
		EffectScript* pScript = new EffectScript(mpPlayerScript);
		this->AddScript(pScript);
	}
}