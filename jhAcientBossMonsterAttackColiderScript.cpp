#include "jhAcientBossMonsterAttackColiderScript.h"
#include "jhAcientBossMonsterScript.h"
#include "jhTransform.h"
#include "jhCollider2D.h"
#include "jhAnimator.h"
#include "jhPlayer.h"
#include "jhPlayerScript.h"


using namespace jh::math;


static constexpr const float ATTACKING_STATE_COLLIDER_BOX_Y_POSITION	= -2.0f;
static constexpr const float TRACING_STATE_COLLIDER_BOX_Y_POSITION		= -4.0f;

static constexpr const float MELEE_ATTACK_DISTANCE_FROM_HIT_COLLIDER	= 1.0f;
static constexpr const float SPIN_ATTACK_DISTANCE_FROM_HIT_COLLIDER		= 2.0f;
static constexpr const float RANGE_ATTACK_DISTANCE_FROM_HIT_COLLIDER	= 3.0f;
static constexpr const float SUPER_ATTACK_DISTANCE_FROM_HIT_COLLIDER	= 4.0f;


static constexpr const UINT MELLE_ATTACK_VAILED_INDEX	= 13;
static constexpr const UINT SPIN_ATTACK_VAILED_INDEX	= 3;
static constexpr const UINT RANGE_ATTACK_VAILED_INDEX	= 10;
static constexpr const UINT SUPER_ATTACK_VAILED_INDEX	= 9;

static constexpr const UINT MELLE_ATTACK_DAMAGE			= 7;
static constexpr const UINT SPIN_ATTACK_DAMAGE			= 5;
static constexpr const UINT RANGE_ATTACK_DAMAGE			= SPIN_ATTACK_DAMAGE;
static constexpr const UINT SUPER_ATTACK_DAMAGE			= 9;

namespace jh
{

	AcientBossMonsterAttackColiderScript::AcientBossMonsterAttackColiderScript(Collider2D* pCollider, Transform* pMonsterTransform, AcientBossMonsterScript* pMonsterScript, Animator* pAnimator, const eBossMonsterColliderType eCollderType)
		: Script()
		, mpCollider(pCollider)
		, mpTransform(nullptr)
		, mpMonsterTransform(pMonsterTransform)
		, mpMonsterScript(pMonsterScript)
		, mpAnimator(pAnimator)
		, meLookDir(eObjectLookDirection::RIGHT)
		, mDistanceFormHitCollider(0.0f)
		, meAttackType(eCollderType)
	{
		assert(mpCollider != nullptr && mpMonsterTransform != nullptr && mpMonsterScript != nullptr && mpAnimator);
		mpCollider->SetState(eColliderState::ACTIVE);
		switch (eCollderType)
		{
		case eBossMonsterColliderType::MELEE_ATTACK:
		{
			mDistanceFormHitCollider = MELEE_ATTACK_DISTANCE_FROM_HIT_COLLIDER;
			break;
		}
		case eBossMonsterColliderType::RANGE_ATTACK:
		{
			mDistanceFormHitCollider = SPIN_ATTACK_DISTANCE_FROM_HIT_COLLIDER;
			break;
		}
		case eBossMonsterColliderType::SPIN_ATTACK:
		{
			mDistanceFormHitCollider = RANGE_ATTACK_DISTANCE_FROM_HIT_COLLIDER;
			break;
		}
		case eBossMonsterColliderType::SUPER_ATTACK:
		{
			mDistanceFormHitCollider = SUPER_ATTACK_DISTANCE_FROM_HIT_COLLIDER;
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void AcientBossMonsterAttackColiderScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void AcientBossMonsterAttackColiderScript::Update()
	{
		setPosByMonsterLookDirectionAndMonsterState();
	}

	void AcientBossMonsterAttackColiderScript::setPosByMonsterLookDirectionAndMonsterState()
	{
		Vector3 pos = mpTransform->GetPosition();
		const eObjectLookDirection eMonsterLookDir = mpMonsterScript->GetLookDirection();
		switch (eMonsterLookDir)
		{
		case eObjectLookDirection::LEFT:
			pos.x = mpMonsterTransform->GetPosition().x - mDistanceFormHitCollider;
			break;
		case eObjectLookDirection::RIGHT:
			pos.x = mpMonsterTransform->GetPosition().x + mDistanceFormHitCollider;
			break;
		default:
			break;
		}
		pos.y = TRACING_STATE_COLLIDER_BOX_Y_POSITION;

		const eBossMonsterState eState = mpMonsterScript->GetState();
		if (eState == eBossMonsterState::MELLE_ATTACKING || 
			eState == eBossMonsterState::SPIN_ATTACKING ||
			eState == eBossMonsterState::RANGE_ATTACKING ||
			eState == eBossMonsterState::SUPER_ATTACKING)
		{
			pos.y = ATTACKING_STATE_COLLIDER_BOX_Y_POSITION;
		}
		mpTransform->SetPosition(pos);
	}

	void AcientBossMonsterAttackColiderScript::damageToPlayer(PlayerScript* pPlayerScript, const UINT damage)
	{
		assert(pPlayerScript != nullptr);
		pPlayerScript->EnemyAttackHiited(damage);
	}

#pragma region COLLIDER_TRIGGER
	void AcientBossMonsterAttackColiderScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{

	}
	void AcientBossMonsterAttackColiderScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER)
		{
			const UINT CURR_IDX = mpAnimator->GetCurrentAnimationIndex();
			PlayerScript* pPlayerScript = static_cast<PlayerScript*>(pOtherCollider->GetOwner()->GetScriptOrNull());
			assert(pPlayerScript != nullptr);

			switch (meAttackType)
			{
			case eBossMonsterColliderType::MELEE_ATTACK:
			{
				if (CURR_IDX == MELLE_ATTACK_VAILED_INDEX)
				{
					damageToPlayer(pPlayerScript, MELLE_ATTACK_DAMAGE);
				}
				break;
			}
			case eBossMonsterColliderType::RANGE_ATTACK:
			{

				if (CURR_IDX == RANGE_ATTACK_VAILED_INDEX)
				{
					damageToPlayer(pPlayerScript, RANGE_ATTACK_DAMAGE);
				}
				break;
			}
			case eBossMonsterColliderType::SPIN_ATTACK:
			{
				if (CURR_IDX == SPIN_ATTACK_VAILED_INDEX)
				{
					damageToPlayer(pPlayerScript, SPIN_ATTACK_DAMAGE);
				}
				break;
			}
			case eBossMonsterColliderType::SUPER_ATTACK:
			{
				if (CURR_IDX == SUPER_ATTACK_VAILED_INDEX)
				{
					damageToPlayer(pPlayerScript, SUPER_ATTACK_DAMAGE);
				}
				break;
			}
			default:
				assert(false);
				break;
			}
		}
	}
	void AcientBossMonsterAttackColiderScript::OnTriggerExit(Collider2D* pOtherCollider)
	{

	}
#pragma endregion


}