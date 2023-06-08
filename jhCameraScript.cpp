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
static constexpr const float Y_CAMERA_POS = 0.0f;
static constexpr const float PLAYER_POWER_ATTACK_CAM_SHAKE_TIME = 0.2f;


namespace jh
{
	CameraScript::CameraScript()
		: Script()
		, mpTranform(nullptr)
		, mpPlayerTransform(nullptr)
		, mpPlayerScript(nullptr)
		, mSpeed(100.0f)
		, mPowerAttackCamShakeTimer(PLAYER_POWER_ATTACK_CAM_SHAKE_TIME)
		, mPowerAttackCamShakeTime(PLAYER_POWER_ATTACK_CAM_SHAKE_TIME)
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
		pos += Vector3(dir.x * mSpeed * Time::DeltaTime(), pos.y, 0.0f);

		// Added Part AT 2023-05-02 11:57 For CameraShaking
		const ePlayerState eState = mpPlayerScript->GetPlayerState();
		if (eState == ePlayerState::HITTED)
		{
			cameraShake(pos);
			return;
		}

		if (mpPlayerScript->IsHitAttack())
		{
			mPowerAttackCamShakeTimer -= Time::DeltaTime();
			if (mPowerAttackCamShakeTimer < 0.0f)
			{
				mPowerAttackCamShakeTimer = mPowerAttackCamShakeTime;
				mpPlayerScript->SetIsHitAttack(false);
				setCameraAtSpecifiedYPosition(pos);
				return;
			}
			cameraShake(pos);
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
		setCameraAtSpecifiedYPosition(pos);
	}

	void CameraScript::SetPlayerTransform(Transform* pPlayerTransform)
	{
		assert(pPlayerTransform != nullptr); 
		mpPlayerTransform = pPlayerTransform;
		setPlayerScript();
	}

	void CameraScript::setCameraAtSpecifiedYPosition(Vector3& pos)
	{
		pos.y = Y_CAMERA_POS;
		mpTranform->SetPosition(pos);
	}

	void CameraScript::setPlayerScript()
	{
		assert(mpPlayerTransform != nullptr);
		mpPlayerScript = static_cast<PlayerScript*>(mpPlayerTransform->GetOwner()->GetScriptOrNull());
		assert(mpPlayerScript != nullptr);
	}
	void CameraScript::cameraShake(Vector3& pos)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_int_distribution<> dist(-CAM_SHAKE_RANGE, CAM_SHAKE_RANGE);
		float xMove = dist(gen) / RESTRICTION;
		//float yMove = dist(gen) / RESTRICTION;
		pos.x += xMove;
		//pos.y += yMove;
		mpTranform->SetPosition(pos);
	}
}
