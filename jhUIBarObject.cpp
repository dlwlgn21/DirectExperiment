#define _CRT_SECURE_NO_WARNINGS
#include "jhUIBarObject.h"
#include "jhGraphics.h"
#include "jhResourceMaker.h"
#include "jhSpriteRenderer.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhMath.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"
#include "jhUIBarScript.h"
#include "jhMonsterUIScript.h"
#include "jhMonsterScript.h"
#include "jhMonsterUIMesh.h"
#include "jhMonsterHPSpriteRenderer.h"
#include "jhAnimator.h"


using namespace jh::math;

static constexpr const float Y_DISTANCE_FROM_EACH_BAR = 0.4f;
static constexpr const float HEALTH_BAR_Y_POSITION = -3.1f;

static constexpr const float BORDER_Z_VALUE = 1.0f;
static constexpr const float BAR_Z_VALUE = 2.0f;

static constexpr const float HEALTH_BORDER_Y_VALUE = HEALTH_BAR_Y_POSITION;
static constexpr const float STAMINA_BORDER_Y_VALUE = HEALTH_BORDER_Y_VALUE - Y_DISTANCE_FROM_EACH_BAR;
static constexpr const float EXP_BORDER_Y_VALUE = STAMINA_BORDER_Y_VALUE - Y_DISTANCE_FROM_EACH_BAR;

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
		{
			GetTransform()->SetPosition(Vector3(0.0f, HEALTH_BORDER_Y_VALUE, BORDER_Z_VALUE));
			break;
		}
		case eUIBarType::STAMINAR_BORDER:
		{
			GetTransform()->SetPosition(Vector3(0.0f, STAMINA_BORDER_Y_VALUE, BAR_Z_VALUE));
			break;
		}
		case eUIBarType::EXP_BORDER:
		{
			GetTransform()->SetPosition(Vector3(0.0f, EXP_BORDER_Y_VALUE, BAR_Z_VALUE));
			break;
		}
		case eUIBarType::HEALTH_BAR:
		{
			GetTransform()->SetPosition(Vector3(0.0f, HEALTH_BORDER_Y_VALUE, BORDER_Z_VALUE));
			setScript(pPlayerScript);
			break;
		}
		case eUIBarType::STAMINA_BAR:
		{
			GetTransform()->SetPosition(Vector3(0.0f, STAMINA_BORDER_Y_VALUE, BAR_Z_VALUE));
			setScript(pPlayerScript);
			break;
		}
		case eUIBarType::EXP_BAR:
		{
			GetTransform()->SetPosition(Vector3(0.0f, EXP_BORDER_Y_VALUE, BAR_Z_VALUE));
			setScript(pPlayerScript);
			break;
		}
		default:
			assert(false);
			break;
		}
		GetTransform()->SetScale(Vector3(1.2f, 0.6f, 1.0f));
		setRenderer();
	}

	UIBarObject::UIBarObject(MonsterScript* pMonsterScript)
		: GameObject(eLayerType::MONSTER_UI)
		, meType(eUIBarType::MONSTER_HP_BAR)
	{
		assert(pMonsterScript != nullptr);
		setMonsterUI(pMonsterScript);
	}

	void UIBarObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = nullptr;
		switch (meType)
		{
		case eUIBarType::HEALTH_BORDER:
		case eUIBarType::STAMINAR_BORDER:
		case eUIBarType::EXP_BORDER:
		/* INTENTIONAL FALL THROGH */
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_HP_BORDER_MATERIAL_KEY);
			break;
		}


		case eUIBarType::HEALTH_BAR:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_HP_BAR_MATERIAL_KEY);
			break;
		}
		case eUIBarType::STAMINA_BAR:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_STAMINA_BAR_MATERIAL_KEY);
			break;
		}
		case eUIBarType::EXP_BAR:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_EXP_BAR_MATERIAL_KEY);
			break;
		}

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
	void UIBarObject::setRenderer(MonsterScript* pMonsterScript)
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_MONSTER_HP_BAR_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		Renderer* pHPRenderer = new MonsterHPRenderer(pMesh, pMaterial);
		this->AddComponent(pHPRenderer);
	}
	void UIBarObject::setMonsterUI(MonsterScript* pMonsterScript)
	{
		assert(pMonsterScript != nullptr);
		setRenderer(pMonsterScript);
		if (pMonsterScript->GetMonsterType() == eMonsterType::LV_1_ACIENT_BOSS)
		{
			GetTransform()->SetOnlyXScale(3.0f);
		}
		else
		{
			GetTransform()->SetOnlyXScale(1.5f);
			GetTransform()->SetOnlyYScale(0.5f);
		}
		MonsterUIScript* pScript = new MonsterUIScript(pMonsterScript);
		this->AddScript(pScript);
		pScript->SetMounsterUIType(meType);
	}

	void UIBarObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::UI_MONSTER_HP_CIRCLE_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float MAGNIFICATION = 100.0f;
		const float WIDTH = 64.0f;
		const float HEIGHT = 64.0f;
		const float BASIC_ANIM_DURATION = 0.15f;
		const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(Vector2::Zero);
		Animator* pAnimator = new Animator();
		pAnimator->Create(
			L"HPAinmation",
			pAtlas,
			Vector2(0.0f, HEIGHT * 6),
			ANIM_SIZE,
			OFFSET,
			8,
			BASIC_ANIM_DURATION,
			MAGNIFICATION
		);
		pAnimator->PlayAnimation(L"HPAinmation", true);
		this->AddComponent(pAnimator);
	}
}