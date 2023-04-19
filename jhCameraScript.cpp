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
		, mpPlayerTransform(nullptr)
		, mSpeed(50.0f)
	{
	}

	void CameraScript::Initialize()
	{
		mpTranform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
	}

	void CameraScript::Update()
	{
		assert(mpTranform != nullptr);
		assert(mpPlayerTransform != nullptr);
		Vector3 pos = mpTranform->GetPosition();

		// Added Part At 2023-04-19 15:49 For Chasing playerTransform

		Vector3 dir = mpPlayerTransform->GetPosition() - mpTranform->GetPosition();
		dir.Normalize();
		pos += Vector3(dir.x * mSpeed * Time::DeltaTime(), dir.y * mSpeed * Time::DeltaTime(), 0.0f);

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
