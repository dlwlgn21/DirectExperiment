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
		
		switch (meType)
		{
		case eUIBarType::HEALTH_BAR:
			break;
		case eUIBarType::STAMINA_BAR:
		{
			UIBarBuffer buffer;
			ZeroMemory(&buffer, sizeof(UIBarBuffer));
			buffer.UV = Vector4(static_cast<float>(playerStat.CurrentStamina) / playerStat.MaxStamina, 1.0f, 0.0f, 0.0f);

			ConstantBuffer* pCB = ResourceMaker::GetInstance().GetUIBarCBOrNull();
			assert(pCB != nullptr);

			pCB->WirteDataAtBuffer(pCB->GetBuffer(), &buffer, sizeof(UIBarBuffer));
			pCB->SetPipeline();
			debuger::CustomOutputDebugString("x Coordinate : ", buffer.UV.x);
			break;
		}
		default:
			assert(false);
			break;
		}

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