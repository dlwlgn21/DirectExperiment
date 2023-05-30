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
		//setScript();
	}


	void PlayerDustEffectObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::EFFECT_PLAYER_DASH_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 59.0f;
		const float HEIGHT = 42.0f;
		const UINT EMPTY_SPACE = 1;
		const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		Animation* pAnimation = pAnimator->Create(
			L"PlayerDashAnimKey",
			pAtlas,
			Vector2::Zero,
			ANIM_SIZE,
			OFFSET,
			7 + EMPTY_SPACE,
			0.1f,
			120
		);
		this->AddComponent(pAnimator);
		pAnimator->SetCurrentAnimation(pAnimation);
	}
	void PlayerDustEffectObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::EFFECT_PLAYER_DASH_MATERIAL_KEY);
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