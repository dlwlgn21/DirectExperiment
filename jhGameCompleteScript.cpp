#include "jhGameCompleteScript.h"
#include "jhInput.h"

namespace jh
{
	GameCompleteScript::GameCompleteScript()
		: Script()
	{
	}

	void GameCompleteScript::Update()
	{
		if (Input::GetKeyState(eKeyCode::ENTER) == eKeyState::UP)
		{
			PostQuitMessage(0);
		}
	}
}