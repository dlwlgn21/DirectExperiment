#include "jhPlayerSkillManager.h"
#include "jhResourceMaker.h"
#include "jhPlayerScript.h"
#include "jhPlayerSkillObject.h"

using namespace jh::math;

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
		switch (eSkillType)
		{
		case ePlayerSkillType::ELETRIC_BEAM:
		{
			fillAnimInfo(animInfo, 375.0f, 64.0f, 500.0f, 9, 0.1f);
			PlayerSkillObject* pSkillObejct = new PlayerSkillObject(
				eSkillType, 
				mpPlayerScript, 
				ResourceMaker::SKILL_TEXTURE_ELECTRIC_BEAM_KEY,
				ResourceMaker::SKILL_MATERIAL_ELECTRIC_BEAM_KEY,
				animInfo
			);

			return pSkillObejct;
		}
		case ePlayerSkillType::ELETRIC_STRIKE:
		{

			break;
		}
		case ePlayerSkillType::TORNADO:
		{

			break;
		}
		default:
			assert(false);
			break;
		}
		return nullptr;
	}

	void PlayerSkillManager::fillAnimInfo(SkillAnimationInfo& animInfo, const float width, const float height, const float mag, const UINT spriteCount, const float animDuration)
	{
		animInfo.Width = width;
		animInfo.Height = height;
		animInfo.Mag = mag;
		animInfo.SpriteCount = spriteCount;
		animInfo.AnimationDuration = animDuration;
	}
}