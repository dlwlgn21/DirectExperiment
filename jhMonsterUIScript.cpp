#include "jhMonsterUIScript.h"
#include "jhMonsterScript.h"
#include "jhDebugHelper.h"
#include "jhResourceMaker.h"
#include "jhTime.h"
#include "jhTransform.h"
#include "jhUIBarObject.h"
//#include "jhMonsterUIManager.h"

using namespace jh::math;

static constexpr float HP_BAR_Z_VALUE = 1.0f;
static constexpr float HP_BORDER_BAR_Z_VALUE = 1.1f;
static constexpr float HP_BAR_Y_DISTANCE_FROM_MONSTER = 1.5f;

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
		if (meType == eUIBarType::MONSTER_HP_BAR)
		{
			assert(mpTransform != nullptr);
			const MonsterHPstatus monHpStat = mpMonsterScript->GetCurrentHPStatus();
			const float hpRatio = static_cast<float>(monHpStat.CurrHP) / monHpStat.MaxHP;
			//MonsterUIAttribute uiAttribute;
			//ZeroMemory(&uiAttribute, sizeof(MonsterUIAttribute));
			//uiAttribute.MonsterHPRatio.x = static_cast<float>(monHpStat.CurrHP) / monHpStat.MaxHP;
			//MonsterUIManager::GetInstance().PushMonsterUIAttribute(uiAttribute);
			mpTransform->SetOnlyXScale(hpRatio);
			mpTransform->SetPosition(Vector3(currMonPos.x, currMonPos.y + HP_BAR_Y_DISTANCE_FROM_MONSTER, HP_BAR_Z_VALUE));
		}
		else
		{
			mpTransform->SetPosition(Vector3(currMonPos.x, currMonPos.y + HP_BAR_Y_DISTANCE_FROM_MONSTER, HP_BORDER_BAR_Z_VALUE));
		}
	}

}