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
		setAnimator();
		setRenderer();
		setScript();
		Vector3 prePos = GetTransform()->GetPosition();
		//GetTransform()->SetPosition(Vector3(prePos.x, 3.0f, 4.0f));
		GetTransform()->SetScale(Vector3(8.0f, 8.0f, 1.0f));
	}

	void PortalEffectObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::GREEN_PORTAL_EFFECT_TEXTURE_ATLAS_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 64.0f;
		const float HEIGHT = 64.0f;
		const float BASIC_DURATION = 0.1f;
		const float MAG = 120.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		pAnimator->Create(
			L"GreenPortalStayKey",
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			8,
			BASIC_DURATION,
			MAG
		);

		Animation* pCurrAnim = pAnimator->Create(
			L"GreenPortalOpenKey",
			pAtlas,
			Vector2(0.0f, HEIGHT * 1),
			animSize,
			offset,
			8,
			BASIC_DURATION,
			MAG
		);

		pAnimator->Create(
			L"GreenPortalCloseKey",
			pAtlas,
			Vector2(0.0f, HEIGHT * 2),
			animSize,
			offset,
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
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::GREEN_PORTAL_EFFECT_MATERIAL_KEY);
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