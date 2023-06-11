#include "jhMonsterUIScript.h"
#include "jhMonsterScript.h"
#include "jhDebugHelper.h"
#include "jhResourceMaker.h"
#include "jhMath.h"
#include "jhTime.h"
#include "jhTransform.h"

using namespace jh::math;

static constexpr float HP_BAR_Z_VALUE = 1.0f;
static constexpr float HP_BAR_Y_DISTANCE_FROM_MONSTER = 1.5f;

namespace jh
{
	MonsterUIScript::MonsterUIScript(MonsterScript* pMonsterScript)
		: Script()
		, mpMonsterScript(pMonsterScript)
		, mpTransform(nullptr)
		, mpMonsterTransform(pMonsterScript->GetOwner()->GetTransform())
	{
		assert(mpMonsterScript != nullptr && mpMonsterTransform != nullptr);
	}

	void MonsterUIScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void MonsterUIScript::Update()
	{
		Vector2 currMonPos = mpMonsterTransform->GetOnlyXYPosition();
		assert(mpTransform != nullptr);
		const MonsterHPstatus monHpStat = mpMonsterScript->GetCurrentHPStatus();
		MonsterUIBarBuffer buffer;
		ZeroMemory(&buffer, sizeof(MonsterUIBarBuffer));
		buffer.UV.x = static_cast<float>(monHpStat.CurrHP) / monHpStat.MaxHP;

		ConstantBuffer* pCB = ResourceMaker::GetInstance().GetMonsterUIBarCBOrNull();
		assert(pCB != nullptr);
		pCB->WirteDataAtBuffer(&buffer, sizeof(UIBarBuffer));
		pCB->SetPipeline();
		mpTransform->SetPosition(Vector3(currMonPos.x, currMonPos.y + HP_BAR_Y_DISTANCE_FROM_MONSTER, HP_BAR_Z_VALUE));
	}

}