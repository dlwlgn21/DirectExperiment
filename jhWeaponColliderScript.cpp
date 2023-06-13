#include "jhWeaponColliderScript.h"
#include "jhInput.h"
#include "jhPlayer.h"
#include "jhPlayerScript.h"
#include "jhCollider2D.h"
#include "jhTime.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhEffectScript.h"

using namespace jh::math;
static constexpr const float START_COUNTING_TIME = 0.1f;
static constexpr const float LEFT_RIGHT_DISTANCE = 1.5f;
static constexpr const float WAIT_FLOATING_DISTANCE = 0.5f;
static constexpr const float ATTACING_FLOATING_DISTANCE = -1.5f;

namespace jh
{
	WeaponColliderScript::WeaponColliderScript(Collider2D* pCollider, Transform* pPlayerTransform, PlayerScript* pPlayerScript)
		: Script()
		, mpCollider(pCollider)
		, mpTransform(nullptr)
		, mpPlayerTransform(pPlayerTransform)
		, mpPlayerScript(pPlayerScript)
		, meLookDir(eObjectLookDirection::RIGHT)
	{
		assert(mpCollider != nullptr);
		assert(mpPlayerTransform != nullptr);
		assert(mpPlayerScript != nullptr);
		mpCollider->SetState(eColliderState::ACTIVE);
	}
	void WeaponColliderScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void WeaponColliderScript::Update()
	{
		setPosByPlayerLookDirectionAndPlayerState();
	}
	void WeaponColliderScript::FixedUpdate()
	{
	}
	void WeaponColliderScript::Render()
	{
	}
	void WeaponColliderScript::setPosByPlayerLookDirectionAndPlayerState()
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
			// TODO : why..??
			//assert(false);
			break;
		}
		pos.y = WAIT_FLOATING_DISTANCE;

		const ePlayerState eState = mpPlayerScript->GetPlayerState();
		if (eState == ePlayerState::ATTACKING)
		{
			pos.y = ATTACING_FLOATING_DISTANCE;
		}

		mpTransform->SetPosition(pos);
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