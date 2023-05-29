#include "jhParallaxObject.h"
#include "jhSpriteRenderer.h"
#include "jhResourceMaker.h"
#include "jhResourcesManager.h"
#include "jhMaterial.h"
#include "jhMesh.h"
#include "jhBattleBGScript.h"
#include "jhParallaxScript.h"

static constexpr const float PARALLAX_1_DEPTH = 100.0f;
static constexpr const float PARALLAX_2_DEPTH = 90.0f;
static constexpr const float PARALLAX_3_DEPTH = 80.0f;
static constexpr const float PARALLAX_4_DEPTH = 70.0f;
static constexpr const float PARALLAX_5_DEPTH = 60.0f;
static constexpr const float PARALLAX_6_DEPTH = 50.0f;
namespace jh
{
	ParallaxObject::ParallaxObject(const float zValue)
		: GameObject(eLayerType::BACKGROUND)
	{
		setScript(zValue);
	}
	void ParallaxObject::Initialize()
	{
		GameObject::Initialize();
	}
	void ParallaxObject::Update()
	{
		assert(GetComponentOrNull(eComponentType::RENDERER) != nullptr);
		GameObject::Update();
	}
	void ParallaxObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void ParallaxObject::Render()
	{
		GameObject::Render();
	}
	void ParallaxObject::SetRenderer(const std::wstring& materialKey)
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		assert(pMesh != nullptr);
		Material* pMaterial = ResourcesManager::Find<Material>(materialKey);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void ParallaxObject::setScript(const float zValue)
	{
		ParallaxScript* pScript;
		float parallaxFactor = 1.0f;
		if (abs(zValue - PARALLAX_1_DEPTH) <= FLT_EPSILON)
		{
			parallaxFactor = 0.95f;
		}
		else if (abs(zValue - PARALLAX_2_DEPTH) <= FLT_EPSILON)
		{
			parallaxFactor = 0.85f;
		}
		else if (abs(zValue - PARALLAX_3_DEPTH) <= FLT_EPSILON)
		{
			parallaxFactor = 0.6f;
		}
		else if (abs(zValue - PARALLAX_4_DEPTH) <= FLT_EPSILON)
		{
			parallaxFactor = 0.5f;
		}
		else if (abs(zValue - PARALLAX_5_DEPTH) <= FLT_EPSILON)
		{
			parallaxFactor = 0.4f;
		}
		else if (abs(zValue - PARALLAX_6_DEPTH) <= FLT_EPSILON)
		{
			parallaxFactor = 0.3f;
		}

		pScript = new ParallaxScript(zValue, parallaxFactor);
		this->AddScript(pScript);
	}
}