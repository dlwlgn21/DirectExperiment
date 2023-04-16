#include "jhWeaponColliderScript.h"
#include "jhInput.h"
#include "jhPlayerScript.h"
#include "jhCollider2D.h"
#include "jhTime.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhEffectScript.h"

using namespace jh::math;
static constexpr const float START_COUNTING_TIME = 0.25f;
static constexpr const float COLIDER_DURATION_CHECK_TIME = 0.5f;
static constexpr const float LEFT_RIGHT_DISTANCE = 1.5f;

namespace jh
{
	WeaponColliderScript::WeaponColliderScript(Collider2D* pCollider, Transform* pPlayerTransform, EffectScript* pEffectScript)
		: Script()
		, mpCollider(pCollider)
		, mColliderStartTimer(START_COUNTING_TIME)
		, mColliderDurationTimer(COLIDER_DURATION_CHECK_TIME)
		, mSpeed(3.0f)
		, meState(eWeponCoilderTimerState::WAITING)
		, mpTransform(nullptr)
		, mpPlayerTransform(pPlayerTransform)
		, mpEffectScript(pEffectScript)
		, meLookDir(eObjectLookDirection::RIGHT)
	{
		assert(mpCollider != nullptr);
		assert(mpPlayerTransform != nullptr);
		assert(mpEffectScript != nullptr);
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

		switch (meState)
		{
		case eWeponCoilderTimerState::WAITING:
			if (Input::GetKeyState(eKeyCode::Z) == eKeyState::PRESSED)
			{
				changeState(eWeponCoilderTimerState::START_TIME_COUNTING);
				//mpEffectScript->PlayAnimation();
			}
			break;

		case eWeponCoilderTimerState::START_TIME_COUNTING:
			mColliderStartTimer -= Time::DeltaTime();
			if (mColliderStartTimer <= 0.0f)
			{
				mColliderStartTimer = START_COUNTING_TIME;
				changeState(eWeponCoilderTimerState::COLIDER_CHECK_TIME_COUNTING);
			}
			break;

		case eWeponCoilderTimerState::COLIDER_CHECK_TIME_COUNTING:
			if (mpCollider->GetState() != eColliderState::ACTIVE)
			{
				mpCollider->SetState(eColliderState::ACTIVE);
			}

			mColliderDurationTimer -= Time::DeltaTime();
			if (mColliderDurationTimer <= 0.0f)
			{
				mColliderDurationTimer = COLIDER_DURATION_CHECK_TIME;
				changeState(eWeponCoilderTimerState::WAITING);
				mpCollider->SetState(eColliderState::INACTIVE);
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
		assert(mpEffectScript != nullptr);
		mpEffectScript->PlayAnimation();
	}
	void WeaponColliderScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
	}
	void WeaponColliderScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
}