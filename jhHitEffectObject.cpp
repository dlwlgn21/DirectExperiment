#include "jhHitEffectObject.h"
#include "jhResourceMaker.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhOnceAnimator.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"
#include "jhHitEffectScript.h"
#include "jhPlayerScript.h"
#include "jhAnimation.h"
using namespace jh::math;

namespace jh
{
	HitEffectObject::HitEffectObject()
		: AnimatedGameObject()
	{
		setRenderer();
	}


	void HitEffectObject::SetScriptAndAnimKey(Script* pScript, const std::wstring& animKey)
	{
		HitEffectScript* pHitEffectScript = new HitEffectScript(pScript, animKey);
		this->AddScript(pHitEffectScript);
	}

	void HitEffectObject::SetEffectAnimation(Texture* pAtlas, const float width, const float height, const std::wstring& animKey, const UINT spriteCount, const float duration)
	{
		assert(pAtlas != nullptr);
		const float MAGNIFICATION = 100.0f;
		Vector2 animSize(width, height);
		Vector2 offset(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		Animation* pAnimation = pAnimator->Create(
			animKey,
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			spriteCount,
			duration,
			MAGNIFICATION
		);
		this->AddComponent(pAnimator);
		pAnimator->SetCurrentAnimation(pAnimation);
	}

	void HitEffectObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::EFFECT_BLOOD_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
}