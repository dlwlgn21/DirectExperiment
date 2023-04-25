#include "jhUIBarScript.h"
#include "jhPlayerScript.h"
#include "jhDebugHelper.h"
#include "jhResourceMaker.h"

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
			debuger::CustomOutputDebugString("InUIBarScript!!\n\n", playerStat.CurrentStamina);
			break;
		default:
			assert(false);
			break;
		}

		Script::Update();
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