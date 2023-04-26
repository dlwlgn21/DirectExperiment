#include "jhMonsterAttackColiderScript.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhMonsterScript.h"

using namespace jh::math;
static constexpr const float START_COUNTING_TIME = 0.1f;
static constexpr const float LEFT_RIGHT_DISTANCE = 1.5f;
static constexpr const float WAIT_FLOATING_DISTANCE = 0.5f;
static constexpr const float ATTACING_FLOATING_DISTANCE = -1.5f;

namespace jh
{
	MonsterAttackColiderScript::MonsterAttackColiderScript(Collider2D* pCollider, Transform* pMonsterTransform, MonsterScript* pMonsterScript)
		: Script()
		, mpCollider(pCollider)
		, mpTransform(nullptr)
		, mpMonsterTransform(pMonsterTransform)
		, mpMonsterScript(pMonsterScript)
		, meLookDir(eObjectLookDirection::RIGHT)
	{
		assert(mpCollider != nullptr);
		assert(mpMonsterTransform != nullptr);
		assert(mpMonsterScript != nullptr);
		mpCollider->SetState(eColliderState::ACTIVE);
	}
	void MonsterAttackColiderScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void MonsterAttackColiderScript::Update()
	{
		setPosByMonsterLookDirectionAndMonsterState();
	}
	void MonsterAttackColiderScript::FixedUpdate()
	{
	}
	void MonsterAttackColiderScript::Render()
	{
	}
	void MonsterAttackColiderScript::setPosByMonsterLookDirectionAndMonsterState()
	{
		Vector3 pos = mpTransform->GetPosition();
		const eObjectLookDirection eMonsterLookDir = mpMonsterScript->GetMonsterLookDirection();
		switch (eMonsterLookDir)
		{
		case eObjectLookDirection::LEFT:
			pos.x = mpMonsterTransform->GetPosition().x - LEFT_RIGHT_DISTANCE;
			break;
		case eObjectLookDirection::RIGHT:
			pos.x = mpMonsterTransform->GetPosition().x + LEFT_RIGHT_DISTANCE;
			break;
		default:
			// TODO : why..??
			//assert(false);
			break;
		}
		//pos.y = WAIT_FLOATING_DISTANCE;

		//const ePlayerState eState = mpPlayerScript->GetPlayerState();
		//if (eState == ePlayerState::ATTACKING)
		//{
		//	pos.y = ATTACING_FLOATING_DISTANCE;
		//}

		mpTransform->SetPosition(pos);
	}

	void MonsterAttackColiderScript::Start()
	{
	}
	void MonsterAttackColiderScript::Complete()
	{
	}
	void MonsterAttackColiderScript::End()
	{
	}

	void MonsterAttackColiderScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{
	}
	void MonsterAttackColiderScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
	}
	void MonsterAttackColiderScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
}