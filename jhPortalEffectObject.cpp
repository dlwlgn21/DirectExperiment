#include "jhPortalEffectObject.h"
#include "jhTexture.h"
#include "jhMesh.h"
#include "jhTransform.h"
#include "jhMaterial.h"
#include "jhResourcesManager.h"
#include "jhResourceMaker.h"
#include "jhOnceAnimator.h"
#include "jhSpriteRenderer.h"
#include "jhPortalEffectScript.h"

using namespace jh::math;

namespace jh
{
	PortalEffectObject::PortalEffectObject()
		: AnimatedGameObject()
	{
		const float PORTACL_SCALE_VALUE = 8.0f;
		setAnimator();
		setRenderer();
		setScript();
		GetTransform()->SetOnlyXYScale(PORTACL_SCALE_VALUE);
	}

	void PortalEffectObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::EFFECT_GREEN_PORTAL_TEXTURE_ATLAS_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 64.0f;
		const float HEIGHT = 64.0f;
		const float BASIC_DURATION = 0.1f;
		const float MAG = 120.0f;
		const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		pAnimator->Create(
			L"GreenPortalStayKey",
			pAtlas,
			Vector2::Zero,
			ANIM_SIZE,
			OFFSET,
			8,
			BASIC_DURATION,
			MAG
		);

		Animation* pCurrAnim = pAnimator->Create(
			L"GreenPortalOpenKey",
			pAtlas,
			Vector2(0.0f, HEIGHT * 1),
			ANIM_SIZE,
			OFFSET,
			8,
			BASIC_DURATION,
			MAG
		);

		pAnimator->Create(
			L"GreenPortalCloseKey",
			pAtlas,
			Vector2(0.0f, HEIGHT * 2),
			ANIM_SIZE,
			OFFSET,
			7,
			BASIC_DURATION,
			MAG
		);

		pAnimator->SetCurrentAnimation(pCurrAnim);
		this->AddComponent(pAnimator);
	}


	void PortalEffectObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::EFFECT_GREEN_PORTAL_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void PortalEffectObject::setScript()
	{
		PortalEffectScript* pScript = new PortalEffectScript();
		this->AddScript(pScript);
	}
}