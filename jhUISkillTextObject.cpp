#include "jhUISkillTextObject.h"
#include "jhSpriteRendererIncludeFiles.h"
#include "jhTransform.h"
#include "jhUISkillTextScript.h"
#include "jhLayerZValue.h"

using namespace jh::math;

static constexpr const float WAIT_Y_POS = 10.0f;
static constexpr const float DEFAULT_X_SCALE_VALUE = 4.0f;
static constexpr const float DEFAULT_Y_SCALE_VALUE = 1.0f;
static constexpr const Vector2 DEFAULT_SCALE_VECTOR(DEFAULT_X_SCALE_VALUE, DEFAULT_Y_SCALE_VALUE);

namespace jh
{
	UISKillTextObject::UISKillTextObject(const eSkillTextType eType)
		: UISkillObject()
		, meSkillTextType(eType)
	{
		setRenderer();
		setScript();
		setTransform();
	}

	void UISKillTextObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = nullptr;
		switch (meSkillTextType)
		{
		case eSkillTextType::ELECTRIC_BEAM_LV_1:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_TEXT_MATERIAL_ELECTRIC_BEAM_LV_1_KEY);
			break;
		}
		case eSkillTextType::ELECTRIC_STRKIE_LV_1:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_TEXT_MATERIAL_ELECTRIC_STRIKE_LV_1_KEY);
			break;
		}
		case eSkillTextType::ELECTRIC_TORNADO_LV_1:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_TEXT_MATERIAL_ELECTRIC_TORANDO_LV_1_KEY);
			break;
		}
		case eSkillTextType::ELECTRIC_DAMAGE:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_TEXT_MATERIAL_ELECTRIC_DAMAGE_INCREASE_KEY);
			break;
		}
		case eSkillTextType::ELECTRIC_SPAWN_SPEED:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_TEXT_MATERIAL_ELECTRIC_SPAWN_SPEED_KEY);
			break;
		}
		case eSkillTextType::SWORD_DAMAGE:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_TEXT_MATERIAL_SWORD_DAMAGE_KEY);
			break;
		}
		case eSkillTextType::MOVEMENT_SPEED:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_TEXT_MATERIAL_MOVEMENT_SPEED_KEY);
			break;
		}
		case eSkillTextType::RECORVER_HEALTH:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::SKILL_TEXT_MATERIAL_RECOVER_HEALTH_KEY);
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
	void UISKillTextObject::setScript()
	{
		UILevelUpScript* pScript = new UISkillTextScript(meSkillTextType);
		this->AddScript(pScript);
	}
	void UISKillTextObject::setTransform()
	{
		GetTransform()->SetOnlyXYScale(DEFAULT_SCALE_VECTOR);

		//switch (meSkillTextType)
		//{
		//case eSkillTextType::ELECTRIC_BEAM_LV_1:
		//{
		//	GetTransform()->SetOnlyXYScale(DEFAULT_SCALE_VECTOR);
		//	break;
		//}
		//case eSkillTextType::ELECTRIC_STRKIE_LV_1:
		//{
		//	break;
		//}
		//case eSkillTextType::ELECTRIC_TORNADO_LV_1:
		//{
		//	break;
		//}
		//case eSkillTextType::ELECTRIC_DAMAGE:
		//{
		//	break;
		//}
		//case eSkillTextType::ELECTRIC_SPAWN_SPEED:
		//{
		//	break;
		//}
		//case eSkillTextType::SWORD_DAMAGE:
		//{
		//	break;
		//}
		//case eSkillTextType::MOVEMENT_SPEED:
		//{
		//	break;
		//}
		//case eSkillTextType::RECORVER_HEALTH:
		//{
		//	break;
		//}
		//default:
		//	assert(false);
		//	break;
		//}
		GetTransform()->SetPosition(Vector3(0.0f, WAIT_Y_POS, LEVEL_UP_UI_SKILL_IOCN_Z_VALUE));
	}
}