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
		
		switch (meType)
		{
		case eUIBarType::HEALTH_BAR:
		{
			buffer.UV.y = static_cast<float>(playerStat.CurrentHP) / playerStat.MaxHP;
			debuger::CustomOutputDebugString("HP is :", buffer.UV.y);
			break;
		}
		case eUIBarType::STAMINA_BAR:
		{
			buffer.UV.x = static_cast<float>(playerStat.CurrentStamina) / playerStat.MaxStamina;
			break;
		}
		default:
			assert(false);
			break;
		}
		ConstantBuffer* pCB = ResourceMaker::GetInstance().GetUIBarCBOrNull();
		assert(pCB != nullptr);

		pCB->WirteDataAtBuffer(pCB->GetBuffer(), &buffer, sizeof(UIBarBuffer));
		pCB->SetPipeline();
		//Script::Update();
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