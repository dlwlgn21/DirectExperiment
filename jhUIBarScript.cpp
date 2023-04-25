#include "jhUIBarScript.h"
#include "jhPlayerScript.h"
#include "jhDebugHelper.h"
#include "jhResourceMaker.h"
#include "jhMath.h"

using namespace jh::math;

namespace jh
{
	UIBarScript::UIBarScript(const eUIBarType eType, PlayerScript* pPlayerScript)
		: Script()
		, meType(eType)
		, mpPlayerScript(pPlayerScript)
	{
	}

	void UIBarScript::Initialize()
	{
		Script::Initialize();
	}
	void UIBarScript::Update()
	{
		const PlayerScript::PlayerStat& playerStat = mpPlayerScript->GetPlayerStat();
		UIBarBuffer buffer;
		ZeroMemory(&buffer, sizeof(UIBarBuffer));
		buffer.UV.x = static_cast<float>(playerStat.CurrentStamina) / playerStat.MaxStamina;
		buffer.UV.y = static_cast<float>(playerStat.CurrentHP) / playerStat.MaxHP;

		ConstantBuffer* pCB = ResourceMaker::GetInstance().GetUIBarCBOrNull();
		assert(pCB != nullptr);
		pCB->WirteDataAtBuffer(pCB->GetBuffer(), &buffer, sizeof(UIBarBuffer));
		pCB->SetPipeline();
	}
	void UIBarScript::FixedUpdate()
	{
		Script::FixedUpdate();
	}
	void UIBarScript::Render()
	{
		Script::Render();
	}
}