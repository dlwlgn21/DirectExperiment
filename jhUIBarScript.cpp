#include "jhUIBarScript.h"
#include "jhPlayerScript.h"


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