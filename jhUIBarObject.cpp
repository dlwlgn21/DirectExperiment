#include "jhUIBarObject.h"
#include "jhResourceMaker.h"
#include "jhSpriteRenderer.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhMath.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"
#include "jhUIBarScript.h"

using namespace jh::math;

static constexpr const float BORDER_Z_VALUE = 1.0f;
static constexpr const float BAR_Z_VALUE = 2.0f;
static constexpr const float HEALTH_BORDER_Y_VALUE = -3.1f;
static constexpr const float STAMINA_BORDER_Y_VALUE = -3.5f;

namespace jh
{
	UIBarObject::UIBarObject(const eUIBarType eType, PlayerScript* pPlayerScript)
		: GameObject(eLayerType::UI)
		, meType(eType)
	{
		assert(pPlayerScript != nullptr);
		switch (meType)
		{
		case eUIBarType::HEALTH_BORDER:
			GetTransform()->SetPosition(Vector3(0.0f, HEALTH_BORDER_Y_VALUE, BORDER_Z_VALUE));
			break;
		case eUIBarType::STAMINAR_BORDER:
			GetTransform()->SetPosition(Vector3(0.0f, STAMINA_BORDER_Y_VALUE, BAR_Z_VALUE));
			break;
		case eUIBarType::HEALTH_BAR:
			GetTransform()->SetPosition(Vector3(0.0f, HEALTH_BORDER_Y_VALUE, BORDER_Z_VALUE));
			setScript(pPlayerScript);
			break;
		case eUIBarType::STAMINA_BAR:
			GetTransform()->SetPosition(Vector3(0.0f, STAMINA_BORDER_Y_VALUE, BAR_Z_VALUE));
			setScript(pPlayerScript);
			break;
		default:
			assert(false);
			break;
		}
		GetTransform()->SetScale(Vector3(1.2f, 0.6f, 1.0f));
		setRenderer();
	}

	void UIBarObject::Initialize()
	{
		GameObject::Initialize();
	}
	void UIBarObject::Update()
	{
		GameObject::Update();
	}
	void UIBarObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void UIBarObject::Render()
	{
		GameObject::Render();
	}
	void UIBarObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = nullptr;
		switch (meType)
		{
		case eUIBarType::HEALTH_BORDER:
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_HP_BORDER_MATERIAL_KEY);
			break;
		case eUIBarType::STAMINAR_BORDER:
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_HP_BORDER_MATERIAL_KEY);
			break;
		case eUIBarType::HEALTH_BAR:
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_HP_BAR_MATERIAL_KEY);
			break;
		case eUIBarType::STAMINA_BAR:
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_STAMINA_BAR_MATERIAL_KEY);
			break;
		default:
			assert(false);
			break;
		}

		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void UIBarObject::setScript(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		UIBarScript* pScript = new UIBarScript(meType, pPlayerScript);
		this->AddScript(pScript);
	}
}