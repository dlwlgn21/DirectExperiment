#include "jhWeaponColliderScript.h"
#include "jhInput.h"
#include "jhPlayer.h"
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
	WeaponColliderScript::WeaponColliderScript(Collider2D* pCollider, Transform* pPlayerTransform, PlayerScript* pPlayerScript)
		: Script()
		, mpCollider(pCollider)
		, mColliderStartTimer(START_COUNTING_TIME)
		, mSpeed(3.0f)
		, meState(eWeponCoilderTimerState::WAITING)
		, mpTransform(nullptr)
		, mpPlayerTransform(pPlayerTransform)
		, mpPlayerScript(pPlayerScript)
		, meLookDir(eObjectLookDirection::RIGHT)
	{
		assert(mpCollider != nullptr);
		assert(mpPlayerTransform != nullptr);
		assert(mpPlayerScript != nullptr);
		mpCollider->SetState(eColliderState::INACTIVE);
	}
	void WeaponColliderScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void WeaponColliderScript::Update()
	{
		setPosByPlayerLookDirection();
		setColliderStateByPlayerState();
	}
	void WeaponColliderScript::FixedUpdate()
	{
	}
	void WeaponColliderScript::Render()
	{
	}
	void WeaponColliderScript::setPosByPlayerLookDirection()
	{
		Vector3 pos = mpTransform->GetPosition();
		const eObjectLookDirection ePlayerLookDir = mpPlayerScript->GetPlayerLookDirection();
		switch (ePlayerLookDir)
		{
		case eObjectLookDirection::LEFT:
			pos.x = mpPlayerTransform->GetPosition().x - LEFT_RIGHT_DISTANCE;
			break;
		case eObjectLookDirection::RIGHT:
			pos.x = mpPlayerTransform->GetPosition().x + LEFT_RIGHT_DISTANCE;
			break;
		default:
			assert(false);
			break;
		}
		mpTransform->SetPosition(pos);
	}
	void WeaponColliderScript::setColliderStateByPlayerState()
	{
		const ePlayerState eState = mpPlayerScript->GetPlayerState();
		if (eState == ePlayerState::ATTACKING)
		{
			mpCollider->SetState(eColliderState::ACTIVE);
		}
		else
		{
			mpCollider->SetState(eColliderState::INACTIVE);
		}
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
		int a = 0;
	}
	void WeaponColliderScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
	}
	void WeaponColliderScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}


}