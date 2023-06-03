#include "jhMonsterAttackColiderScript.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhAnimator.h"
#include "jhMonsterScript.h"
#include "jhPlayer.h"
#include "jhPlayerScript.h"

using namespace jh::math;
static constexpr const float START_COUNTING_TIME = 0.1f;
static constexpr const float DISTANCE = 1.5f;
static constexpr const float ATTACING_FLOATING_DISTANCE = -2.0f;
static constexpr const float WAIT_FLOATING_DISTANCE = -4.0f;


static constexpr const UINT CAGED_SHOCKER_ATTACk_VAILED_INDEX_1 = 7;
static constexpr const UINT CAGED_SHOCKER_ATTACk_VAILED_INDEX_2 = 12;
static constexpr const UINT CAGED_SHOCKER_ATTACk_DAMAGE = 2;

static constexpr const UINT SWEEPER_ATTACK_VAILED_INDEX = 5;
static constexpr const UINT SWEEPER_ATTACK_DAMAGE = 2;

static constexpr const UINT WARDEN_ATTACK_VAILED_INDEX = 6;
static constexpr const UINT WARDEN_ATTACK_DAMAGE = 2;

static constexpr const UINT ZOMBIE_ATTACK_VAILED_INDEX = 6;
static constexpr const UINT ZOMBIE_ATTACK_DAMAGE = 2;

static constexpr const UINT HEABY_SLICER_ATTACK_VAILED_INDEX_1 = 5;
static constexpr const UINT HEABY_SLICER_ATTACK_VAILED_INDEX_2 = 9;
static constexpr const UINT HEABY_SLICER_ATTACK_DAMAGE = 4;

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
		, meMonsterType(pMonsterScript->GetMonsterType())
		, mDistance(DISTANCE)
	{
		assert(mpCollider != nullptr && mpMonsterTransform != nullptr && mpMonsterScript != nullptr && mpAnimator);
		mpCollider->SetState(eColliderState::ACTIVE);
		adjustColliderDistance();
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

	void MonsterAttackColiderScript::setPosByMonsterLookDirectionAndMonsterState()
	{
		Vector3 pos = mpTransform->GetPosition();
		const eObjectLookDirection eMonsterLookDir = mpMonsterScript->GetMonsterLookDirection();
		switch (eMonsterLookDir)
		{
		case eObjectLookDirection::LEFT:
			pos.x = mpMonsterTransform->GetPosition().x - mDistance;
			break;
		case eObjectLookDirection::RIGHT:
			pos.x = mpMonsterTransform->GetPosition().x + mDistance;
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


	void MonsterAttackColiderScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{
	}
	void MonsterAttackColiderScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER)
		{
			const UINT CURR_IDX = mpAnimator->GetCurrentAnimationIndex();
			PlayerScript* pPlayerScript = static_cast<PlayerScript*>(pOtherCollider->GetOwner()->GetScriptOrNull());
			assert(pPlayerScript != nullptr);

			switch (meMonsterType)
			{
			case eMonsterType::LV_1_CAGED_SHOKER:
			{
				if (CURR_IDX == CAGED_SHOCKER_ATTACk_VAILED_INDEX_1 || CURR_IDX == CAGED_SHOCKER_ATTACk_VAILED_INDEX_2)
				{
					damageToPlayer(pPlayerScript, CAGED_SHOCKER_ATTACk_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_SWEEPER:
			{
				if (CURR_IDX == SWEEPER_ATTACK_VAILED_INDEX)
				{
					damageToPlayer(pPlayerScript, SWEEPER_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_WARDEN:
			{
				if (CURR_IDX == WARDEN_ATTACK_VAILED_INDEX)
				{
					damageToPlayer(pPlayerScript, WARDEN_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_ZOMBIE:
			{
				if (CURR_IDX == ZOMBIE_ATTACK_VAILED_INDEX)
				{
					damageToPlayer(pPlayerScript, ZOMBIE_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_HEABY_SLICER:
			{
				if (CURR_IDX == HEABY_SLICER_ATTACK_VAILED_INDEX_1 || CURR_IDX == HEABY_SLICER_ATTACK_VAILED_INDEX_2)
				{
					damageToPlayer(pPlayerScript, HEABY_SLICER_ATTACK_DAMAGE);
				}
				break;
			}
			default:
				assert(false);
				break;
			}

		}
	}

	void MonsterAttackColiderScript::damageToPlayer(PlayerScript* pPlayerScript, const UINT damage)
	{
		assert(pPlayerScript != nullptr);
		pPlayerScript->EnemyAttackHiited(damage);
	}

	void MonsterAttackColiderScript::adjustColliderDistance()
	{
		switch (meMonsterType)
		{
		case jh::eMonsterType::LV_1_CAGED_SHOKER:
		{
			break;
		}
		case jh::eMonsterType::LV_1_SWEEPER:
		{
			break;
		}
		case jh::eMonsterType::LV_1_WARDEN:
		{
			break;
		}
		case jh::eMonsterType::LV_1_ZOMBIE:
		{
			mDistance = 0.5f;
			break;
		}
		case jh::eMonsterType::LV_1_HEABY_SLICER:
		{
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void MonsterAttackColiderScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
}