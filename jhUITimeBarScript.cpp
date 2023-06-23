#include "jhUITimeBarScript.h"
#include "jhResourceMaker.h"
#include "jhMonsterSpawner.h"
#include "jhTransform.h"
#include "jhTime.h"
namespace jh
{
	UITimeBarScript::UITimeBarScript()
		: Script()
		, mStageChangeTime(MonsterSpawner::STAGE_CHANGE_TIME)
	{
	}

	void UITimeBarScript::Update()
	{
		const float accumTime = MonsterSpawner::GetInstance().GetStageChangeTimerTime();
		Transform* pTransform = GetOwner()->GetTransform();
		assert(pTransform != nullptr);
		//if (std::abs(accumTime) < FLT_EPSILON)
		//{
		//	pTransform->SetOnlyXScale(10.0f);
		//}
		//const float prevXScale = pTransform->GetOnlyXScale();
		//float currXScale =  1.0f - ((accumTime / mStageChangeTime) * Time::DeltaTime());
		//pTransform->SetOnlyXScale(prevXScale * currXScale);

		float currRatio =  accumTime / mStageChangeTime;

		UITimeBuffer timeBuffer;
		//ZeroMemory(&timeBuffer, sizeof(timeBuffer));
		timeBuffer.Time.x = currRatio;
		
		ConstantBuffer* pCB = ResourceMaker::GetInstance().GetUITimeCBOrNull();
		assert(pCB != nullptr);
		pCB->WirteDataAtBuffer(&timeBuffer, sizeof(UITimeBuffer));
		pCB->SetPipeline();
	}
}