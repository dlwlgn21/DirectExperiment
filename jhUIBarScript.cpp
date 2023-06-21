#include "jhUIBarScript.h"
#include "jhPlayerScript.h"
#include "jhDebugHelper.h"
#include "jhResourceMaker.h"
#include "jhMath.h"
#include "jhTime.h"
#include "jhPlayerLevelManager.h"

using namespace jh::math;

namespace jh
{
	UIBarScript::UIBarScript(const eUIBarType eType, PlayerScript* pPlayerScript)
		: Script()
		, meType(eType)
		, mpPlayerScript(pPlayerScript)
	{
	}


	void UIBarScript::Update()
	{
		const PlayerScript::PlayerStat& playerStat = mpPlayerScript->GetPlayerStat();
		UIBarBuffer buffer;
		ZeroMemory(&buffer, sizeof(UIBarBuffer));
		buffer.UV.x = static_cast<float>(playerStat.CurrentStamina) / playerStat.MaxStamina;
		buffer.UV.y = static_cast<float>(playerStat.CurrentHP) / playerStat.MaxHP;
		buffer.UV.z = static_cast<float>(playerStat.CurrEXP) / playerStat.MaxEXP;
		if (mpPlayerScript->IsLevelUping())
		{
			buffer.UV.z = 1.0f;
		}

		ConstantBuffer* pCB = ResourceMaker::GetInstance().GetUIBarCBOrNull();
		assert(pCB != nullptr);
		pCB->WirteDataAtBuffer(&buffer, sizeof(UIBarBuffer));
		pCB->SetPipeline();
	}

}