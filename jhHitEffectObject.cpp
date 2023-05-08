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
#include "jhTransform.h"
#include "jhMonsterManager.h"
using namespace jh::math;

namespace jh
{
	HitEffectObject::HitEffectObject()
		: AnimatedGameObject()
	{
		setRenderer();
		setAnimator();
	}


	void HitEffectObject::AddEffectScript(Script* pFollwingScript, PlayerScript* pPlayerScript)
	{
		HitEffectScript* pHitEffectScript = new HitEffectScript(pFollwingScript, pPlayerScript);
		this->AddScript(pHitEffectScript);
	}

	void HitEffectObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::HIT_EFFECT_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void HitEffectObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::HIT_EFFECT_TEXTURE_ATLAS_KEY);
		assert(pAtlas != nullptr);
		const float MAGNIFICATION = 100.0f;
		const float WIDTH = 82.0f;
		const float HEIGHT = 65.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		Animation* pAnimation = pAnimator->Create(
			MonsterManager::HIT_COMBO_1_ELECTRIC_EFFECT_ANIM_KEY,
			pAtlas,
			Vector2(0.0f, HEIGHT * 6),
			animSize,
			offset,
			6,
			0.1f,
			MAGNIFICATION
		);
		pAnimator->Create(
			MonsterManager::HIT_COMBO_2_ELECTRIC_EFFECT_ANIM_KEY,
			pAtlas,
			Vector2(0.0f, HEIGHT * 7),
			animSize,
			offset,
			8,
			0.1f,
			MAGNIFICATION
		);

		pAnimator->Create(
			MonsterManager::HIT_COMBO_3_ELECTRIC_EFFECT_ANIM_KEY,
			pAtlas,
			Vector2(0.0f, HEIGHT * 9),
			animSize,
			offset,
			9,
			0.1f,
			MAGNIFICATION
		);

		this->AddComponent(pAnimator);
		pAnimator->SetCurrentAnimation(pAnimation);
	}
}