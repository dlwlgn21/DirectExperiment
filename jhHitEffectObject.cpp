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
#include "jhPlayer.h"
#include "jhPlayerHitEffectScript.h"

using namespace jh::math;

namespace jh
{
	HitEffectObject::HitEffectObject(const eHitEffectType eEffectType, MonsterScript* pMonsterScript, PlayerScript* pPlayerScript)
		: AnimatedGameObject()
		, meHitEffectType(eEffectType)
	{
		assert(pMonsterScript != nullptr && pPlayerScript != nullptr);
		setRenderer();
		setAnimator();
		setMonsterHitScript(pMonsterScript, pPlayerScript);

	}

	HitEffectObject::HitEffectObject(const eHitEffectType eEffectType, PlayerScript* pPlayerScript)
		: AnimatedGameObject()
		, meHitEffectType(eEffectType)
	{
		assert(pPlayerScript != nullptr);
		setRenderer();
		setAnimator();
		setPlayerHitScript(pPlayerScript);
	}

	void HitEffectObject::setMonsterHitScript(MonsterScript* pMonsterScript, PlayerScript* pPlayerScript)
	{
		assert(pMonsterScript != nullptr && pPlayerScript != nullptr);
		HitEffectScript* pScript = new HitEffectScript(pMonsterScript, pPlayerScript);
		this->AddScript(pScript);
	}

	void HitEffectObject::setPlayerHitScript(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		PlayerHitEffectScript* pScript = new PlayerHitEffectScript(pPlayerScript);
		this->AddScript(pScript);
	}

	void HitEffectObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::EFFECT_HIT_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void HitEffectObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::EFFECT_HIT_TEXTURE_ATLAS_KEY);
		assert(pAtlas != nullptr);
		const float MAGNIFICATION = 100.0f;
		const float WIDTH = 82.0f;
		const float HEIGHT = 65.0f;
		const float BASIC_ANIM_DURATION = 0.05f;
		const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		Animation* pAnimation = nullptr;
		switch (meHitEffectType)
		{
		case eHitEffectType::ELECTRIC:
		{
			pAnimation = pAnimator->Create(
				MonsterManager::HIT_COMBO_1_ELECTRIC_EFFECT_ANIM_KEY,
				pAtlas,
				Vector2(0.0f, HEIGHT * 6),
				ANIM_SIZE,
				OFFSET,
				6,
				BASIC_ANIM_DURATION,
				MAGNIFICATION
			);
			pAnimator->Create(
				MonsterManager::HIT_COMBO_2_ELECTRIC_EFFECT_ANIM_KEY,
				pAtlas,
				Vector2(0.0f, HEIGHT * 7),
				ANIM_SIZE,
				OFFSET,
				8,
				BASIC_ANIM_DURATION,
				MAGNIFICATION
			);

			pAnimator->Create(
				MonsterManager::HIT_COMBO_3_ELECTRIC_EFFECT_ANIM_KEY,
				pAtlas,
				Vector2(0.0f, HEIGHT * 9),
				ANIM_SIZE,
				OFFSET,
				9,
				BASIC_ANIM_DURATION,
				MAGNIFICATION
			);
			pAnimator->SetCurrentAnimation(pAnimation);
			break;
		}
		case eHitEffectType::BLOOD:
		{
			pAnimation = pAnimator->Create(
				Player::HIT_1_ANIM_KEY,
				pAtlas,
				Vector2(0.0f, HEIGHT * 10),
				ANIM_SIZE,
				OFFSET,
				5,
				BASIC_ANIM_DURATION,
				MAGNIFICATION
			);
			pAnimator->Create(
				Player::HIT_2_ANIM_KEY,
				pAtlas,
				Vector2(0.0f, HEIGHT * 11),
				ANIM_SIZE,
				OFFSET,
				4,
				BASIC_ANIM_DURATION,
				MAGNIFICATION
			);

			pAnimator->Create(
				Player::HIT_3_ANIM_KEY,
				pAtlas,
				Vector2(0.0f, HEIGHT * 12),
				ANIM_SIZE,
				OFFSET,
				8,
				BASIC_ANIM_DURATION,
				MAGNIFICATION
			);
			break;
		}
		default:
			break;
		}
		assert(pAnimation != nullptr);
		pAnimator->SetCurrentAnimation(pAnimation);
		this->AddComponent(pAnimator);
	}
}