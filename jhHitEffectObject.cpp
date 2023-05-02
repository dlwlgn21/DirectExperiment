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
		//setAnimator();
		setRenderer();
		//setScript();
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
	}
}