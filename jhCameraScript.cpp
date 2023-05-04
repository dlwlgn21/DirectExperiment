#include <random>
#include "jhCameraScript.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhPlayerScript.h"

using namespace jh::math;

static constexpr const INT CAM_SHAKE_RANGE = 5;
static constexpr const float RESTRICTION = 100.0f;
static constexpr const float Y_CAMERA_POS = -1.0f;

namespace jh
{
	CameraScript::CameraScript()
		: Script()
		, mpTranform(nullptr)
		, mpPlayerTransform(nullptr)
		, mpPlayerScript(nullptr)
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

		// Added Part At 2023-04-19 15:49 For Chasing PlayerTransform
		Vector3 dir = mpPlayerTransform->GetPosition() - mpTranform->GetPosition();
		dir.Normalize();
		pos += Vector3(dir.x * mSpeed * Time::DeltaTime(), dir.y, 0.0f);

		// Added Part AT 2023-05-02 11:57 For CameraShaking
		const ePlayerState eState = mpPlayerScript->GetPlayerState();
		if (eState == ePlayerState::HITTED)
		{
			static std::random_device rd;
			static std::mt19937 gen(rd());
			static std::uniform_int_distribution<> dist(-CAM_SHAKE_RANGE, CAM_SHAKE_RANGE);
			float xMove = dist(gen) / RESTRICTION;
			float yMove = dist(gen) / RESTRICTION;
			pos.x += xMove;
			pos.y += yMove;
			mpTranform->SetPosition(pos);
			return;
		}

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
		pos.y = Y_CAMERA_POS;
		mpTranform->SetPosition(pos);
	}

	void CameraScript::SetPlayerTransform(Transform* pPlayerTransform)
	{
		assert(pPlayerTransform != nullptr); 
		mpPlayerTransform = pPlayerTransform;
		setPlayerScript();
	}

	void CameraScript::setPlayerScript()
	{
		assert(mpPlayerTransform != nullptr);
		mpPlayerScript = static_cast<PlayerScript*>(mpPlayerTransform->GetOwner()->GetScriptOrNull());
		assert(mpPlayerScript != nullptr);
	}
}
