#include "jhWeaponColliderScript.h"
#include "jhInput.h"
#include "jhPlayerScript.h"
#include "jhCollider2D.h"
#include "jhTime.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhEffectScript.h"
#include "jhDebugHelper.h"


using namespace jh::math;
static constexpr const float START_COUNTING_TIME = 0.1f;
static constexpr const float LEFT_RIGHT_DISTANCE = 1.5f;

namespace jh
{
	WeaponColliderScript::WeaponColliderScript(Collider2D* pCollider, Transform* pPlayerTransform)
		: Script()
		, mpCollider(pCollider)
		, mColliderStartTimer(START_COUNTING_TIME)
		, mSpeed(3.0f)
		, meState(eWeponCoilderTimerState::WAITING)
		, mpTransform(nullptr)
		, mpPlayerTransform(pPlayerTransform)
		, meLookDir(eObjectLookDirection::RIGHT)
	{
		assert(mpCollider != nullptr);
		assert(mpPlayerTransform != nullptr);
		pCollider->SetState(eColliderState::INACTIVE);
	}
	void WeaponColliderScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void WeaponColliderScript::Update()
	{
		Vector3 pos = mpTransform->GetPosition();


		switch (meState)
		{
		case eWeponCoilderTimerState::WAITING:
			if (meLookDir == eObjectLookDirection::LEFT)
			{
				pos.x = mpPlayerTransform->GetPosition().x - LEFT_RIGHT_DISTANCE;
			}
			else
			{
				pos.x = mpPlayerTransform->GetPosition().x + LEFT_RIGHT_DISTANCE;
			}

			if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
			{
				pos.x += mSpeed * Time::DeltaTime();
				meLookDir = eObjectLookDirection::RIGHT;

			}
			if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
			{
				pos.x -= mSpeed * Time::DeltaTime();
				meLookDir = eObjectLookDirection::LEFT;
			}

			if (mpCollider->GetState() == eColliderState::ACTIVE)
			{
				mpCollider->SetState(eColliderState::INACTIVE);
			}

			if (Input::GetKeyState(eKeyCode::Z) == eKeyState::DOWN)
			{
				changeState(eWeponCoilderTimerState::START_TIME_COUNTING);
			}
			break;
		case eWeponCoilderTimerState::START_TIME_COUNTING:
			mColliderStartTimer -= Time::DeltaTime();

			if (mColliderStartTimer <= 0.0f)
			{
				mColliderStartTimer = START_COUNTING_TIME;
				if (mpCollider->GetState() != eColliderState::ACTIVE)
				{
					mpCollider->SetState(eColliderState::ACTIVE);
				}
				changeState(eWeponCoilderTimerState::WAITING);
			}
			break;
		default:
			break;
		}

		mpTransform->SetPosition(pos);
	}
	void WeaponColliderScript::FixedUpdate()
	{
	}
	void WeaponColliderScript::Render()
	{
	}

	void WeaponColliderScript::Start()
	{
	}
	void WeaponColliderScript::Complete()
	{
	}
	void WeaponColliderScript::End()
	{
	}

	void WeaponColliderScript::OnCollisionEnter(Collider2D* pOtherCollider)
	{
	}
	void WeaponColliderScript::OnCollisionStay(Collider2D* pOtherCollider)
	{
	}
	void WeaponColliderScript::OnCollisionExit(Collider2D* pOtherCollider)
	{
	}
	void WeaponColliderScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{
	}
	void WeaponColliderScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
	}
	void WeaponColliderScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
}