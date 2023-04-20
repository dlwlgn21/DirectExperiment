#include "jhHitEffectObject.h"
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
#include "jhEffectScript.h"
using namespace jh::math;

namespace jh
{
	HitEffectObject::HitEffectObject()
		: AnimatedGameObject()
	{
		setAnimator();
		setRenderer();
		setScript();
		
	}

	void HitEffectObject::Initialize()
	{
		AnimatedGameObject::Initialize();
	}
	void HitEffectObject::Update()
	{
		AnimatedGameObject::Update();
	}
	void HitEffectObject::FixedUpdate()
	{
		AnimatedGameObject::FixedUpdate();
	}
	void HitEffectObject::Render()
	{
		AnimatedGameObject::Render();
	}

	void HitEffectObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::EFFECT_SWORD_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 128.0;
		const float HEIGHT = 128.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		Animation* pAnimation = pAnimator->Create(
			L"MonsterHitAnim",
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
	void HitEffectObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::EFFECT_SWORD_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void HitEffectObject::setScript()
	{
		EffectScript* pScript = new EffectScript();
		this->AddScript(pScript);
	}
}