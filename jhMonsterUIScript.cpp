#include "jhMonsterUIScript.h"
#include "jhMonsterScript.h"
#include "jhDebugHelper.h"
#include "jhResourceMaker.h"
#include "jhTime.h"
#include "jhTransform.h"
#include "jhUIBarObject.h"
#include "jhLayerZValue.h"
#include "jhMonsterUIManager.h"
#include "jhMonsterHPSpriteRenderer.h"
#include "jhCameraManager.h"
#include "jhCamera.h"

using namespace jh::math;

static constexpr float HP_BAR_Y_DISTANCE_FROM_MONSTER = 1.5f;
static constexpr float HP_BAR_Y_DISTANCE_FROM_BOSS_MONSTER = 2.5f;

namespace jh
{

	MonsterUIScript::MonsterUIScript(MonsterScript* pMonsterScript)
		: Script()
		, mpMonsterScript(pMonsterScript)
		, mpTransform(nullptr)
		, mpMonsterTransform(pMonsterScript->GetOwner()->GetTransform())
		, meType(eUIBarType::COUNT)
	{
		assert(mpMonsterScript != nullptr && mpMonsterTransform != nullptr);
	}

	void MonsterUIScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
		assert(meType != eUIBarType::COUNT);
	}

	void MonsterUIScript::Update()
	{
		Vector2 currMonPos = mpMonsterTransform->GetOnlyXYPosition();
		assert(mpTransform != nullptr);
		const MonsterHPstatus monHpStat = mpMonsterScript->GetCurrentHPStatus();
		const float hpRatio = static_cast<float>(monHpStat.CurrHP) / monHpStat.MaxHP;
		// Boss Monster
		if (mpMonsterScript->GetMonsterType() == eMonsterType::LV_1_ACIENT_BOSS)
		{
			MonsterUIManager::GetInstance().WriteMonsterUIDataAtBuffer(hpRatio);
			mpTransform->SetPosition(Vector3(currMonPos.x, currMonPos.y + HP_BAR_Y_DISTANCE_FROM_BOSS_MONSTER, MONSTER_HP_BAR_Z_VALUE));
			return;
		}
		mpTransform->SetOnlyXScale(hpRatio);
		mpTransform->SetPosition(Vector3(currMonPos.x, currMonPos.y + HP_BAR_Y_DISTANCE_FROM_MONSTER, MONSTER_HP_BAR_Z_VALUE));
	}
}