#include "jhMonsterAttackColiderScript.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhAnimator.h"
#include "jhMonsterScript.h"
#include "jhPlayer.h"
#include "jhPlayerScript.h"

using namespace jh::math;
static constexpr const float START_COUNTING_TIME = 0.1f;
static constexpr const float LEFT_RIGHT_DISTANCE = 1.5f;
static constexpr const float ATTACING_FLOATING_DISTANCE = -2.0f;
static constexpr const float WAIT_FLOATING_DISTANCE = -4.0f;


// Animator Index
static constexpr const UINT CAGED_SHOCKER_ATTACk_VAILED_INDEX_1 = 7;
static constexpr const UINT CAGED_SHOCKER_ATTACk_VAILED_INDEX_2 = 12;

// DAMAGE
static constexpr const UINT CAGED_SHOCKER_ATTACk_DAMAGE = 2;

namespace jh
{
	MonsterAttackColiderScript::MonsterAttackColiderScript(Collider2D* pCollider, Transform* pMonsterTransform, MonsterScript* pMonsterScript, Animator* pAnimator)
		: Script()
		, mpCollider(pCollider)
		, mpTransform(nullptr)
		, mpMonsterTransform(pMonsterTransform)
		, mpMonsterScript(pMonsterScript)
		, mpAnimator(pAnimator)
		, meLookDir(eObjectLookDirection::RIGHT)
	{
		assert(mpCollider != nullptr && mpMonsterTransform != nullptr && mpMonsterScript != nullptr && mpAnimator);
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
			break;
		}
		pos.y = WAIT_FLOATING_DISTANCE;

		const eMonsterState eState = mpMonsterScript->GetMonsterState();
		if (eState == eMonsterState::ATTACKING)
		{
			pos.y = ATTACING_FLOATING_DISTANCE;
		}

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
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER)
		{
			const UINT CURR_IDX = mpAnimator->GetCurrentAnimationIndex();
			if (CURR_IDX == CAGED_SHOCKER_ATTACk_VAILED_INDEX_1 || CURR_IDX == CAGED_SHOCKER_ATTACk_VAILED_INDEX_2)
			{
				PlayerScript* pPlayerScript = static_cast<PlayerScript*>(pOtherCollider->GetOwner()->GetScriptOrNull());
				assert(pPlayerScript != nullptr);

				pPlayerScript->EnemyAttackHiited(CAGED_SHOCKER_ATTACk_DAMAGE);
			}
		}

	}
	void MonsterAttackColiderScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
}