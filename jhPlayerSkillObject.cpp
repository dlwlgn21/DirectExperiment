#include "jhPlayerSkillObject.h"
#include "jhTransform.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhResourceMaker.h"
#include "jhAnimator.h"
#include "jhAnimation.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhSpriteRenderer.h"
#include "jhPlayerScript.h"
#include "jhPlayerSkillElectricBeamScript.h"
#include "jhLayerZValue.h"

using namespace jh::math;

static constexpr const float ELECTRIC_BEAM_XY_SCALE_VALUE = 15.0f;

static constexpr const float ELECTRIC_BEAM_Y_POS_DISTANCE_FROM_PLAYER = 0.5f;

namespace jh
{

	const std::wstring PlayerSkillObject::ELECTRIC_BEAM_ANIM_KEY = L"ElectricAnimKey";

	PlayerSkillObject::PlayerSkillObject(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, const std::wstring& textureKey, const std::wstring& materialKey, SkillAnimationInfo& animInfo)
		: AnimatedGameObject()
		, meSkillType(eSkillType)
	{
		assert(pPlayerScript != nullptr);
		Animator* pAnimator = setAnimator(textureKey, animInfo);
		setRenderer(materialKey);
		setScript(pPlayerScript, pAnimator);
		setTransform(pPlayerScript);
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
			ELECTRIC_BEAM_ANIM_KEY,
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
	void PlayerSkillObject::setScript(PlayerScript* pPlayerScript, Animator* pAnimator)
	{
		assert(pPlayerScript != nullptr && pAnimator != nullptr);
		switch (meSkillType)
		{
		case jh::ePlayerSkillType::ELETRIC_BEAM:
		{
			PlayerSkillScript* pScript = new PlayerSkillElectricBeamScript(meSkillType, pPlayerScript, pAnimator);
			this->AddScript(pScript);
			break;
		}
		case jh::ePlayerSkillType::ELETRIC_STRIKE:
		{

			break;
		}
		case jh::ePlayerSkillType::TORNADO:
		{

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

			break;
		}
		case jh::ePlayerSkillType::TORNADO:
		{

			break;
		}
		default:
			assert(false);
			break;
		}
	}
}