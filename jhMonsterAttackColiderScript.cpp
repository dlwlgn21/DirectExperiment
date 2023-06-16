#include "jhMonsterAttackColiderScript.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhAnimator.h"
#include "jhMonsterScript.h"
#include "jhPlayer.h"
#include "jhPlayerScript.h"
#include "jhMonsterAnimIndexInformation.h"
#include "jhProtectingCrystalScript.h"

using namespace jh::math;
static constexpr const float START_COUNTING_TIME = 0.1f;
static constexpr const float DISTANCE = 1.5f;
static constexpr const float ATTACKING_STATE_COLLIDER_BOX_Y_POSITION = -2.0f;
static constexpr const float WAIT_STATE_COLLIDER_BOX_Y_POSITION = -4.0f;

static constexpr const UINT CAGED_SHOCKER_ATTACk_DAMAGE = 2;

static constexpr const UINT SWEEPER_ATTACK_DAMAGE = 2;

static constexpr const UINT WARDEN_ATTACK_DAMAGE = 2;

static constexpr const UINT ZOMBIE_ATTACK_DAMAGE = 2;

static constexpr const UINT HEABY_SLICER_ATTACK_DAMAGE = 4;

static constexpr const UINT LIGHT_SLICER_ATTACK_DAMAGE = 2;

static constexpr const UINT DAGGER_ATTACK_DAMAGE = 2;

static constexpr const UINT ARCHER_ATTACK_DAMAGE = 4;

static constexpr const UINT BLASTER_ATTACK_DAMAGE = 3;

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
		pos.y = WAIT_STATE_COLLIDER_BOX_Y_POSITION;

		const eMonsterState eState = mpMonsterScript->GetMonsterState();
		if (eState == eMonsterState::ATTACKING)
		{
			pos.y = ATTACKING_STATE_COLLIDER_BOX_Y_POSITION;
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
			case eMonsterType::LV_1_LIGHT_SLICER:
			{
				if (CURR_IDX == LIGHT_SLICER_ATTACK_VAILED_INDEX_1 || CURR_IDX == LIGHT_SLICER_ATTACK_VAILED_INDEX_2 || CURR_IDX == LIGHT_SLICER_ATTACK_VAILED_INDEX_3)
				{
					damageToPlayer(pPlayerScript, LIGHT_SLICER_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_DAGGER:
			{
				if (CURR_IDX == DAGGER_ATTACK_VAILED_INDEX_1 || CURR_IDX == DAGGER_ATTACK_VAILED_INDEX_2)
				{
					damageToPlayer(pPlayerScript, DAGGER_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_ARCHER:
			{
				if (CURR_IDX == ARCHER_ATTACK_VAILED_INDEX)
				{
					damageToPlayer(pPlayerScript, ARCHER_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_BLASTER:
			{
				if (CURR_IDX == BLASTER_ATTACK_VAILED_INDEX)
				{
					damageToPlayer(pPlayerScript, BLASTER_ATTACK_DAMAGE);
				}
				break;
			}
			default:
				assert(false);
				break;
			}
			return;
		}

		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PROTECTING_OBJECT)
		{
			const UINT CURR_IDX = mpAnimator->GetCurrentAnimationIndex();
			ProtectingCrystalScript* pCrystalScript = static_cast<ProtectingCrystalScript*>(pOtherCollider->GetOwner()->GetScriptOrNull());
			assert(pCrystalScript != nullptr);

			switch (meMonsterType)
			{
			case eMonsterType::LV_1_CAGED_SHOKER:
			{
				if (CURR_IDX == CAGED_SHOCKER_ATTACk_VAILED_INDEX_1 || CURR_IDX == CAGED_SHOCKER_ATTACk_VAILED_INDEX_2)
				{
					pCrystalScript->DecreaseHP(CAGED_SHOCKER_ATTACk_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_SWEEPER:
			{
				if (CURR_IDX == SWEEPER_ATTACK_VAILED_INDEX)
				{
					pCrystalScript->DecreaseHP(SWEEPER_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_WARDEN:
			{
				if (CURR_IDX == WARDEN_ATTACK_VAILED_INDEX)
				{
					pCrystalScript->DecreaseHP(WARDEN_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_ZOMBIE:
			{
				if (CURR_IDX == ZOMBIE_ATTACK_VAILED_INDEX)
				{
					pCrystalScript->DecreaseHP(ZOMBIE_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_HEABY_SLICER:
			{
				if (CURR_IDX == HEABY_SLICER_ATTACK_VAILED_INDEX_1 || CURR_IDX == HEABY_SLICER_ATTACK_VAILED_INDEX_2)
				{
					pCrystalScript->DecreaseHP(HEABY_SLICER_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_LIGHT_SLICER:
			{
				if (CURR_IDX == LIGHT_SLICER_ATTACK_VAILED_INDEX_1 || CURR_IDX == LIGHT_SLICER_ATTACK_VAILED_INDEX_2 || CURR_IDX == LIGHT_SLICER_ATTACK_VAILED_INDEX_3)
				{
					pCrystalScript->DecreaseHP(LIGHT_SLICER_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_DAGGER:
			{
				if (CURR_IDX == DAGGER_ATTACK_VAILED_INDEX_1 || CURR_IDX == DAGGER_ATTACK_VAILED_INDEX_2)
				{
					pCrystalScript->DecreaseHP(DAGGER_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_ARCHER:
			{
				if (CURR_IDX == ARCHER_ATTACK_VAILED_INDEX)
				{
					pCrystalScript->DecreaseHP(ARCHER_ATTACK_DAMAGE);
				}
				break;
			}
			case eMonsterType::LV_1_BLASTER:
			{
				if (CURR_IDX == BLASTER_ATTACK_VAILED_INDEX)
				{
					pCrystalScript->DecreaseHP(BLASTER_ATTACK_DAMAGE);
				}
				break;
			}
			default:
				assert(false);
				break;
			}

			return;
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
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			mDistance = 2.0f;
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			mDistance = 0.5f;
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			break;
		}
		case eMonsterType::LV_1_DAGGER:
		{
			mDistance = 2.0f;
			break;
		}
		case eMonsterType::LV_1_ARCHER:
		{
			mDistance = 2.5f;
			break;
		}
		case eMonsterType::LV_1_BLASTER:
		{
			mDistance = 2.5f;
			break;
		}
		case eMonsterType::LV_1_ACIENT_BOSS:
		{
			mDistance = 2.5f;
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