#include "jhPlayerSkillObject.h"
#include "jhTransform.h"
#include "jhTexture.h"
#include "jhCollider2D.h"
#include "jhResourcesManager.h"
#include "jhResourceMaker.h"
#include "jhAnimator.h"
#include "jhAnimation.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"
#include "jhPlayerScript.h"
#include "jhPlayerSkillElectricBeamScript.h"
#include "jhPlayerSkillElectricStrikeScript.h"
#include "jhPlayerSkillElectricTornadoScript.h"
#include "jhLayerZValue.h"

using namespace jh::math;

static constexpr const float ELECTRIC_BEAM_XY_SCALE_VALUE = 12.0f;
static constexpr const float ELECTRIC_BEAM_Y_POS_DISTANCE_FROM_PLAYER = 0.5f;
static constexpr const float ELECTRIC_STRIKE_XY_SCALE_VALUE = 20.0f;
static constexpr const float ELECTRIC_TORNADO_XY_SCALE_VALUE = 12.0f;


namespace jh
{

	PlayerSkillObject::PlayerSkillObject(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, const std::wstring& textureKey, const std::wstring& materialKey, SkillAnimationInfo& animInfo)
		: AnimatedGameObject()
		, meSkillType(eSkillType)
	{
		assert(pPlayerScript != nullptr);
		Animator* pAnimator = setAnimator(textureKey, animInfo);
		setRenderer(materialKey);
		setScript(pPlayerScript);
		setTransform(pPlayerScript);
		setCollider2D();
	}

	Animator* PlayerSkillObject::setAnimator(const std::wstring& textureKey, SkillAnimationInfo& animInfo)
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(textureKey);
		assert(pAtlas != nullptr);
		const float WIDTH = animInfo.Width;
		const float HEIGHT = animInfo.Height;
		const float MAG = animInfo.Mag;

		const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(animInfo.Offset);
		Animator* pAnimator = new Animator();
		Animation* pAnimation = pAnimator->Create(
			animInfo.animKey,
			pAtlas,
			Vector2::Zero,
			ANIM_SIZE,
			OFFSET,
			animInfo.SpriteCount,
			animInfo.AnimationDuration,
			MAG
		);
		this->AddComponent(pAnimator);
		pAnimator->SetCurrentAnimation(pAnimation);
		return pAnimator;
	}
	void PlayerSkillObject::setRenderer(const std::wstring& materialKey)
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(materialKey);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void PlayerSkillObject::setScript(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		switch (meSkillType)
		{
		case jh::ePlayerSkillType::ELETRIC_BEAM:
		{
			PlayerSkillScript* pScript = new PlayerSkillElectricBeamScript(meSkillType, pPlayerScript, static_cast<Animator*>(GetComponentOrNull(eComponentType::ANIMATOR)));
			this->AddScript(pScript);
			break;
		}
		case jh::ePlayerSkillType::ELETRIC_STRIKE:
		{
			PlayerSkillScript* pScript = new PlayerSkillElectricStrikeScript(meSkillType, pPlayerScript, static_cast<Animator*>(GetComponentOrNull(eComponentType::ANIMATOR)));
			this->AddScript(pScript);
			break;
		}
		case jh::ePlayerSkillType::TORNADO:
		{
			PlayerSkillScript* pScript = new PlayerSkillElectricTornadoScript(meSkillType, pPlayerScript, static_cast<Animator*>(GetComponentOrNull(eComponentType::ANIMATOR)));
			this->AddScript(pScript);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void PlayerSkillObject::setTransform(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		Vector3 playerPos = pPlayerScript->GetOwner()->GetTransform()->GetPosition();
		switch (meSkillType)
		{
		case jh::ePlayerSkillType::ELETRIC_BEAM:
		{
			GetTransform()->SetOnlyYZPosition(playerPos.y + ELECTRIC_BEAM_Y_POS_DISTANCE_FROM_PLAYER, PLAYER_SKILL_EFFECT_Z_VALUE);
			GetTransform()->SetOnlyXYScale(ELECTRIC_BEAM_XY_SCALE_VALUE);
			break;
		}
		case jh::ePlayerSkillType::ELETRIC_STRIKE:
		{
			GetTransform()->SetOnlyYZPosition(playerPos.y + ELECTRIC_BEAM_Y_POS_DISTANCE_FROM_PLAYER, PLAYER_SKILL_EFFECT_Z_VALUE);
			GetTransform()->SetOnlyXYScale(ELECTRIC_STRIKE_XY_SCALE_VALUE);
			break;
		}
		case jh::ePlayerSkillType::TORNADO:
		{
			GetTransform()->SetOnlyYZPosition(playerPos.y + ELECTRIC_BEAM_Y_POS_DISTANCE_FROM_PLAYER, PLAYER_SKILL_EFFECT_Z_VALUE);
			GetTransform()->SetOnlyXYScale(ELECTRIC_TORNADO_XY_SCALE_VALUE);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void PlayerSkillObject::setCollider2D()
	{
		Collider2D* pCollider = new Collider2D(eColliderLayerType::PLAYER_SKILL);
		
		switch (meSkillType)
		{
		case ePlayerSkillType::ELETRIC_BEAM:
		{
			pCollider->SetSize(Vector2(0.75f, 0.05f));
			break;
		}
		case ePlayerSkillType::ELETRIC_STRIKE:
		{
			pCollider->SetSize(Vector2(0.025f, 0.3f));
			break;
		}
		case ePlayerSkillType::TORNADO:
		{
			pCollider->SetSize(Vector2(0.05f, 0.05f));
			break;
		}
		default:
			assert(false);
			break;
		}


		this->AddComponent(pCollider);
		
	}

}