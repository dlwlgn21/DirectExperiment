#include "jhPlayerSkillManager.h"
#include "jhResourceMaker.h"
#include "jhPlayerScript.h"
#include "jhPlayerSkillObject.h"

using namespace jh::math;

static constexpr const float DEFAULT_SKILL_ANIM_DURATION = 0.1f;

namespace jh
{
	void PlayerSkillManager::Update()
	{
		assert(mpPlayerScript != nullptr);
	}

	PlayerSkillObject* PlayerSkillManager::MakePlayerSkilObjectOrNull(const ePlayerSkillType eSkillType)
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
		assert(pSkillObejct != nullptr);
		return pSkillObejct;
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