#include "jhBGMoonObject.h"
#include "jhResourceMaker.h"
#include "jhMaterial.h"
#include "jhMesh.h"
#include "jhSpriteRenderer.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhParallaxScript.h"
#include "jhTransform.h"


using namespace jh::math;

namespace jh
{
	BGMoonObject::BGMoonObject()
		: AnimatedGameObject()
	{
		const float MOON_SCALE_VALUE = 8.0f;
		setAnimator();
		setRenderer();
		setScript();
		Vector3 prePos = GetTransform()->GetPosition();
		GetTransform()->SetPosition(Vector3(prePos.x, 3.0f, prePos.z));
		GetTransform()->SetOnlyXYScale(MOON_SCALE_VALUE);
	}

	void BGMoonObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::BG_MOON_ATLAS_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 48.0f;
		const float HEIGHT = 48.0f;
		const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(Vector2::Zero);
		Animator* pAnimator = new Animator();
		pAnimator->Create(
			L"MoonSpinAnimKey",
			pAtlas,
			Vector2::Zero,
			ANIM_SIZE,
			OFFSET,
			60,
			0.2f,
			120
		);
		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(L"MoonSpinAnimKey", true);
	}
	void BGMoonObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::BG_MOON_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void BGMoonObject::setScript()
	{
		ParallaxScript* pScript;
		float parallaxFactor = 0.85f;
		pScript = new ParallaxScript(95.0f, parallaxFactor);
		this->AddScript(pScript);
	}
}