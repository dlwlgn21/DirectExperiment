#include "jhCameraScript.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhInput.h"
#include "jhTime.h"

using namespace jh::math;

namespace jh
{
	CameraScript::CameraScript()
		: Script()
		, mpTranform(nullptr)
		, mSpeed(50.0f)
	{
	}

	void CameraScript::Initialize()
	{
	}

	void CameraScript::Update()
	{
		mpTranform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(mpTranform != nullptr);
		Vector3 pos = mpTranform->GetPosition();
		if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos += mSpeed * mpTranform->GetForward() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos += mSpeed * -mpTranform->GetForward() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos += mSpeed * mpTranform->GetRight() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos += mSpeed * -mpTranform->GetRight() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			pos += mSpeed * mpTranform->GetUp() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			pos += mSpeed * -mpTranform->GetUp() * Time::DeltaTime();
		}

		mpTranform->SetPosition(pos);
	}

	void CameraScript::FixedUpdate()
	{
	}

	void CameraScript::Render()
	{
	}

}
