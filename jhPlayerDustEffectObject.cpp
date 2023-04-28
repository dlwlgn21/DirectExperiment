#include "jhPlayerDustEffectObject.h"
#include "jhResourceMaker.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhOnceAnimator.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"
#include "jhPlayerScript.h"
#include "jhAnimation.h"

using namespace jh::math;

namespace jh
{
	PlayerDustEffectObject::PlayerDustEffectObject()
		: AnimatedGameObject()
	{
		setAnimator();
		setRenderer();
		setScript();
	}


	void PlayerDustEffectObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::PLAYER_DASH_EFFECT_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 41.0f;
		const float HEIGHT = 31.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		Animation* pAnimation = pAnimator->Create(
			L"PlayerDashAnimKey",
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			8,
			0.05f,
			100
		);
		this->AddComponent(pAnimator);
		pAnimator->SetCurrentAnimation(pAnimation);
	}
	void PlayerDustEffectObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::PLAYER_DASH_EFFECT_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void PlayerDustEffectObject::setScript()
	{
		//EffectScript* pScript = new EffectScript();
		//this->AddScript(pScript);
	}
}