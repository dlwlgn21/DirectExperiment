#include "jhUISkillIconObject.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"
#include "jhResourcesManager.h"
#include "jhResourceMaker.h"
#include "jhTransform.h"
#include "jhLayerZValue.h"
#include "jhUISkillIconScript.h"
#include "jhAnimator.h"

using namespace jh::math;

static constexpr const float WAIT_Y_POS = 10.0f;
static constexpr const float ELECTRIC_BEAM_SCALUE_VALUE = 3.5f;
static constexpr const float ELECTRIC_STRIKE_SCALUE_VALUE = 4.0f;
static constexpr const float ELECTRIC_TORNADO_SCALUE_VALUE = 4.0f;
static constexpr const float MELLE_ATTACK_SCALUE_VALUE = 8.0f;
static constexpr const float SPEED_SCALUE_VALUE = 8.0f;
static constexpr const float HEALTH_SCALUE_VALUE = 8.0f;

namespace jh
{
	UISkillIconObject::UISkillIconObject(const eSkillIconType eIconType)
		: GameObject()
		, meSkillIconType(eIconType)
		
	{
		setRenderer();
		setScript();
		setTransform();
		setAnimator();
	}

	void UISkillIconObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = nullptr; 
		switch (meSkillIconType)
		{
		case eSkillIconType::ELECTRIC_BEAM:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_MATERIAL_ELECTRIC_BEAM_KEY);
			break;															 
		}																	 
		case eSkillIconType::ELECTRIC_STRIKE:								 
		{																	 
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_MATERIAL_ELECTRIC_STRIKE_KEY);
			break;															 
		}																	 
		case eSkillIconType::ELECTRIC_TORNADO:								 
		{																	 
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_MATERIAL_ELECTRIC_TORNADO_KEY);
			break;
		}
		case eSkillIconType::MELLE_ATTACK_DAMAGE:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_ICON_MATERIAL_MELLE_ATTACK_KEY);
			break;
		}
		case eSkillIconType::SPEED:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_ICON_MATERIAL_SPEED_KEY);
			break;
		}
		case eSkillIconType::HEALTH:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_ICON_MATERIAL_HEALTH_KEY);
			break;
		}

		default:
			assert(false);
			break;
		}


		assert(pMesh != nullptr && pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void UISkillIconObject::setScript()
	{
		UILevelUpScript* pScript = new UISkillIconScript(meSkillIconType);
		this->AddScript(pScript);
	}

	void UISkillIconObject::setTransform()
	{
		switch (meSkillIconType)
		{
		case eSkillIconType::ELECTRIC_BEAM:
		{
			GetTransform()->SetOnlyXYScale(ELECTRIC_BEAM_SCALUE_VALUE);
			break;
		}
		case eSkillIconType::ELECTRIC_STRIKE:
		{
			GetTransform()->SetOnlyXYScale(ELECTRIC_STRIKE_SCALUE_VALUE);
			break;
		}
		case eSkillIconType::ELECTRIC_TORNADO:
		{
			GetTransform()->SetOnlyXYScale(ELECTRIC_TORNADO_SCALUE_VALUE);
			break;
		}
		case eSkillIconType::MELLE_ATTACK_DAMAGE:
		{
			GetTransform()->SetOnlyXYScale(MELLE_ATTACK_SCALUE_VALUE);
			break;
		}
		case eSkillIconType::SPEED:
		{
			GetTransform()->SetOnlyXYScale(SPEED_SCALUE_VALUE);
			break;
		}
		case eSkillIconType::HEALTH:
		{
			GetTransform()->SetOnlyXYScale(HEALTH_SCALUE_VALUE);
			break;
		}
		default:
			assert(false);
			break;
		}
		GetTransform()->SetPosition(Vector3(0.0f, WAIT_Y_POS, LEVEL_UP_UI_SKILL_IOCN_Z_VALUE));
	}

	void UISkillIconObject::setAnimator()
	{

		Texture* pAtlas = nullptr;
		float width = 0.0f;
		float heigt = 0.0f;
		float mag = 0.0f;
		UINT spriteCount = 0;
		float animDuration = 0.0f;
		std::wstring key;
		Animator* pAnimator = new Animator();
		switch (meSkillIconType)
		{
		case eSkillIconType::ELECTRIC_BEAM:
		{
			pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::SKILL_TEXTURE_ELECTRIC_BEAM_KEY);
			assert(pAtlas != nullptr);
			width = 375.0f;
			heigt = 64.0f;
			mag = 500.0f;
			spriteCount = 9;
			animDuration = 0.2f;
			key = L"ElectricBeamKey";
			break;
		}
		case eSkillIconType::ELECTRIC_STRIKE:
		{
			pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::SKILL_TEXTURE_ELECTRIC_STRIKE_KEY);
			assert(pAtlas != nullptr);
			width = 80.0f;
			heigt = 176.0f;
			mag = 600.0f;
			spriteCount = 10;
			animDuration = 0.075f;
			key = L"ElectricStrikeKey";
			break;
		}
		case eSkillIconType::ELECTRIC_TORNADO:
		{
			pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::SKILL_TEXTURE_ELECTRIC_TORNADO_KEY);
			assert(pAtlas != nullptr);
			width = 64.0f;
			heigt = 64.0f;
			mag = 300.0f;
			spriteCount = 18;
			animDuration = 0.2f;
			key = L"ElectricTornadoKey";
			break;
		}
		case eSkillIconType::MELLE_ATTACK_DAMAGE:
		{
			pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::SKILL_ICON_TEXTURE_MELLE_ATTACK_KEY);
			assert(pAtlas != nullptr);
			width = 90.0f;
			heigt = 37.0f;
			mag = 300.0f;
			spriteCount = 17;
			animDuration = 0.1f;
			key = L"AttackKey";
			break;
		}
		case eSkillIconType::SPEED:
		{
			pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::SKILL_ICON_TEXTURE_SPEED_KEY);
			assert(pAtlas != nullptr);
			width = 90.0f;
			heigt = 37.0f;
			mag = 300.0f;
			spriteCount = 8;
			animDuration = 0.1f;
			key = L"SpeedKey";
			break;
		}
		case eSkillIconType::HEALTH:
		{
			pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::SKILL_ICON_TEXTURE_HEALTH_KEY);
			assert(pAtlas != nullptr);
			width = 64.0f;
			heigt = 16.0f;
			mag = 300.0f;
			spriteCount = 8;
			animDuration = 0.1f;
			key = L"HelathKey";
			break;
			break;
		}
		default:
			assert(false);
			break;
		}

		const Vector2 ANIM_SIZE(width, heigt);
		const Vector2 OFFSET(Vector2::Zero);
		pAnimator->Create(
			key,
			pAtlas,
			Vector2::Zero,
			ANIM_SIZE,
			OFFSET,
			spriteCount,
			animDuration,
			mag
		);
		this->AddComponent(pAnimator);
		pAnimator->PlayAnimation(key, true);
	}
}