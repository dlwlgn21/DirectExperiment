#include "jhMonsterScript.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhGameObject.h"
#include "jhTransform.h"

using namespace jh::math;

namespace jh
{
	MonsterScript::MonsterScript()
		: Script()
	{
	}
	MonsterScript::~MonsterScript()
	{
	}
	void MonsterScript::Initialize()
	{
	}
	void MonsterScript::Update()
	{
		static const float SPEED = 1.0f;
		Transform* pTransform = GetOwner()->GetTransform();
		assert(pTransform != nullptr);
		Vector3 moveVector = pTransform->GetPosition();
		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			moveVector.z += DirectX::XM_PI * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			moveVector.z -= DirectX::XM_PI * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			moveVector.x += SPEED * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			moveVector.x -= SPEED * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			moveVector.y -= SPEED * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			moveVector.y += SPEED * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::N_1) == eKeyState::PRESSED)
		{
			Time::SetScale(1.0f);
		}
		if (Input::GetKeyState(eKeyCode::N_2) == eKeyState::PRESSED)
		{
			Time::SetScale(2.0f);
		}
		if (Input::GetKeyState(eKeyCode::N_3) == eKeyState::PRESSED)
		{
			Time::SetScale(3.0f);
		}

		pTransform->SetPosition(moveVector);
	}
	void MonsterScript::FixedUpdate()
	{
	}
	void MonsterScript::Render()
	{
	}

}