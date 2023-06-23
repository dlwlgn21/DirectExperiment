#include "jhMenuSelectBoxScript.h"
#include "jhGameObject.h"
#include "jhInput.h"
#include "jhTransform.h"
#include "jhSFXManager.h"
#include "jhSceneManager.h"
#include "jhPlayScene.h"



namespace jh
{
	MenuSelectBoxScript::MenuSelectBoxScript(const eMenuSelectBoxType eType)
		: Script()
		, meBoxPosition(eMenuSelectBoxPosition::TOP)
		, mpTransform(nullptr)
		, mpTopButton(nullptr)
		, mpBottomButton(nullptr)
		, meTpye(eType)
	{

	}

	void MenuSelectBoxScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}

	void MenuSelectBoxScript::Update()
	{
		assert(mpTransform != nullptr);
		static float currYPos = START_BUTTON_Y_POS;
		static float prevYpos = currYPos;
		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::DOWN)
		{
			if (prevYpos <= EXIT_BUTTON_Y_POS)
			{
				mpTransform->SetOnlyYPosition(prevYpos);
				return;
			}
			currYPos = EXIT_BUTTON_Y_POS;
			prevYpos = currYPos;
			mpTransform->SetOnlyYPosition(currYPos);
			SFXManager::GetInstance().Play(eSFXType::UI_LEVEL_UP_MOVING);
			return;
		}
		else if (Input::GetKeyState(eKeyCode::UP) == eKeyState::DOWN)
		{
			if (prevYpos >= START_BUTTON_Y_POS)
			{
				mpTransform->SetOnlyYPosition(prevYpos);
				return;
			}
			currYPos = START_BUTTON_Y_POS;
			prevYpos = currYPos;
			mpTransform->SetOnlyYPosition(currYPos);
			SFXManager::GetInstance().Play(eSFXType::UI_LEVEL_UP_MOVING);
			return;
		}

		if (Input::GetKeyState(eKeyCode::ENTER) == eKeyState::UP)
		{
			OnSelected(currYPos, prevYpos);
		}
	}
}