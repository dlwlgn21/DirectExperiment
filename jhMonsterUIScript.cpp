#include "jhMonsterUIScript.h"
#include "jhMonsterScript.h"
#include "jhDebugHelper.h"
#include "jhResourceMaker.h"
#include "jhMath.h"
#include "jhTime.h"
#include "jhTransform.h"

using namespace jh::math;

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
		const MonsterHPstatus monHpStat = mpMonsterScript->GetCurrentHPStatus();
		UIBarBuffer buffer;
		ZeroMemory(&buffer, sizeof(UIBarBuffer));
		buffer.UV.x = static_cast<float>(monHpStat.CurrHP) / monHpStat.MaxHP;

		ConstantBuffer* pCB = ResourceMaker::GetInstance().GetUIBarCBOrNull();
		assert(pCB != nullptr);
		pCB->WirteDataAtBuffer(&buffer, sizeof(UIBarBuffer));
		pCB->SetPipeline();
		mpTransform->SetOnlyXYPosition(mpMonsterTransform->GetOnlyXYPosition());
	}

}