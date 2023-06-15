#include "jhPlayerSkillManager.h"
#include "jhResourceMaker.h"
#include "jhPlayerScript.h"
#include "jhPlayerSkillObject.h"
#include "jhPlayerSkillScript.h"
#include "jhSceneManager.h"
#include "jhPlayScene.h"

using namespace jh::math;

static constexpr const float DEFAULT_SKILL_ANIM_DURATION = 0.1f;
static constexpr const UINT ELETRIC_SKILL_MAX_DAMAGE = 10;
static constexpr const float ELETRIC_SKILL_MIN_COLL_TIME = 0.1f;

static constexpr const UINT DAMAGE_INCREASE_AMOUNT = 1;
static constexpr const float COOL_TIME_DECREASE_AMOUNT = 0.9f;

namespace jh
{
	void PlayerSkillManager::Update()
	{
		assert(mpPlayerScript != nullptr);
	}

	void PlayerSkillManager::AddSkillObject(const ePlayerSkillType eSkillType)
	{
		static_cast<PlayScene*>(SceneManager::GetInstance().GetCurrentScene())->AddSkillObejct(makePlayerSkilObjectOrNull(eSkillType));
	}

	PlayerSkillObject* PlayerSkillManager::makePlayerSkilObjectOrNull(const ePlayerSkillType eSkillType)
	{
		assert(mpPlayerScript != nullptr);
		SkillAnimationInfo animInfo;
		PlayerSkillObject* pSkillObejct = nullptr;
		switch (eSkillType)
		{
		case ePlayerSkillType::ELETRIC_BEAM:
		{
			fillAnimInfo(animInfo, 375.0f, 64.0f, 500.0f, 9, DEFAULT_SKILL_ANIM_DURATION, L"ElectricBeamKey");
			pSkillObejct = new PlayerSkillObject(
				eSkillType, 
				mpPlayerScript, 
				ResourceMaker::SKILL_TEXTURE_ELECTRIC_BEAM_KEY,
				ResourceMaker::SKILL_MATERIAL_ELECTRIC_BEAM_KEY,
				animInfo
			);
			break;
		}
		case ePlayerSkillType::ELETRIC_STRIKE:
		{
			fillAnimInfo(animInfo, 80.0f, 176.0f, 600.0f, 10, DEFAULT_SKILL_ANIM_DURATION -0.025f, L"ElectricStrikeKey");
			pSkillObejct = new PlayerSkillObject(
				eSkillType,
				mpPlayerScript,
				ResourceMaker::SKILL_TEXTURE_ELECTRIC_STRIKE_KEY,
				ResourceMaker::SKILL_MATERIAL_ELECTRIC_STRIKE_KEY,
				animInfo
			);
			break;
		}
		case ePlayerSkillType::TORNADO:
		{
			fillAnimInfo(animInfo, 64.0f, 64.0f, 300.0f, 18, DEFAULT_SKILL_ANIM_DURATION, L"ElectricTornadoKey");
			pSkillObejct = new PlayerSkillObject(
				eSkillType,
				mpPlayerScript,
				ResourceMaker::SKILL_TEXTURE_ELECTRIC_TORNADO_KEY,
				ResourceMaker::SKILL_MATERIAL_ELECTRIC_TORNADO_KEY,
				animInfo
			);
			break;
		}
		default:
			assert(false);
			break;
		}
		pSkillObejct->Initialize();
		mpPlayerSkillObjects[static_cast<UINT>(eSkillType)] = pSkillObejct;
		assert(pSkillObejct != nullptr);
		return pSkillObejct;
	}

	void PlayerSkillManager::IncreaseElectricSkillDamage(const ePlayerSkillType eSkillType)
	{
		PlayerSkillScript* pScript = nullptr;
		switch (eSkillType)
		{
		case ePlayerSkillType::ELETRIC_BEAM:
		{
			increaseElectricSkillDamage(ePlayerSkillType::ELETRIC_BEAM);
			break;
		}
		case ePlayerSkillType::ELETRIC_STRIKE:
		{
			increaseElectricSkillDamage(ePlayerSkillType::ELETRIC_STRIKE);
			break;
		}
		default:
			assert(false);
			break;
		}
	}
	void PlayerSkillManager::DecreaseElectricSkillCollTime(const ePlayerSkillType eSkillType)
	{
		switch (eSkillType)
		{
		case ePlayerSkillType::ELETRIC_BEAM:
		{
			decreaseElectricSkillCollTime(ePlayerSkillType::ELETRIC_BEAM);
			break;
		}
		case ePlayerSkillType::ELETRIC_STRIKE:
		{
			decreaseElectricSkillCollTime(ePlayerSkillType::ELETRIC_STRIKE);
			break;
		}
		case ePlayerSkillType::TORNADO:
		{
			decreaseElectricSkillCollTime(ePlayerSkillType::TORNADO);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void PlayerSkillManager::increaseElectricSkillDamage(const ePlayerSkillType eSkillType)
	{
		PlayerSkillScript* pScript = static_cast<PlayerSkillScript*>(mpPlayerSkillObjects[static_cast<UINT>(eSkillType)]->GetScriptOrNull());
		assert(pScript != nullptr);
		pScript->mSkillStat.Damage += DAMAGE_INCREASE_AMOUNT;
		assert(pScript->mSkillStat.Damage < ELETRIC_SKILL_MAX_DAMAGE);
	}
	void PlayerSkillManager::decreaseElectricSkillCollTime(const ePlayerSkillType eSkillType)
	{
		PlayerSkillScript* pScript = static_cast<PlayerSkillScript*>(mpPlayerSkillObjects[static_cast<UINT>(eSkillType)]->GetScriptOrNull());
		assert(pScript != nullptr);
		pScript->mSkillStat.CoolTime *= COOL_TIME_DECREASE_AMOUNT;
		assert(pScript->mSkillStat.CoolTime > ELETRIC_SKILL_MIN_COLL_TIME);
	}

	void PlayerSkillManager::fillAnimInfo(SkillAnimationInfo& animInfo, const float width, const float height, const float mag, const UINT spriteCount, const float animDuration, const std::wstring& animKey)
	{
		animInfo.Width = width;
		animInfo.Height = height;
		animInfo.Mag = mag;
		animInfo.SpriteCount = spriteCount;
		animInfo.AnimationDuration = animDuration;
		animInfo.animKey = animKey;
	}
}