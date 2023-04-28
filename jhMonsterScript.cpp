#include "jhMonsterScript.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhHitEffectScript.h"
#include "jhCollider2D.h"
#include "jhPlayerScript.h"

using namespace jh::math;
static constexpr const float ATTACK_RANGE_DISTANCE = 2.0f;

namespace jh
{
	MonsterScript::MonsterScript(HitEffectScript* pEffectScript, PlayerScript* pPlayerScript)
		: Script()
		, mpTranform(nullptr)
		, mpPlayerTransform(nullptr)
		, mpAnimator(nullptr)
		, mpEffectScript(pEffectScript)
		, mpPlayerScript(pPlayerScript)
		, mSpeed(1.0f)
		, mHittedPushDistance(2.0f)
		, mAnimIdleKey(L"MonsterIdle")
		, mAnimMoveKey(L"MonsterMove")
		, mAnimAttackKey(L"MonsterAttack")
		, mAnimHittedKey(L"MonsterHitted")
		, meLookDir(eObjectLookDirection::RIGHT)
		, meState(eMonsterState::TRACING)
	{
	}

	void MonsterScript::Initialize()
	{
		setAnimator();
		assert(mpEffectScript != nullptr);
		mpEffectScript->Initialize();
		mpTranform = GetOwner()->GetTransform();
		assert(mpTranform != nullptr);

		assert(mpPlayerScript != nullptr);
		mpPlayerTransform = mpPlayerScript->GetOwner()->GetTransform();
		assert(mpPlayerTransform != nullptr);

		mpTranform->SetPosition(Vector3(6.0f, -1.8f, 4.0f));
		mpTranform->SetScale(Vector3(6.0f, 6.0f, 1.0f));
	}

	void MonsterScript::Update()
	{
		setPosition();
		setAnimationFlip();
		playAnimation();
	}
	void MonsterScript::FixedUpdate()
	{
	}
	void MonsterScript::Render()
	{
	}

	void MonsterScript::Start()
	{
	}

	void MonsterScript::Complete()
	{
	}

	void MonsterScript::End()
	{
	}

	void MonsterScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{

		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER)
		{
			setState(eMonsterState::ATTACKING);
			return;
		}
		if (meState == eMonsterState::HITTED)
		{
			return;
		}
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER_WEAPON)
		{
			setState(eMonsterState::HITTED);
		}
	}
	void MonsterScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
	}
	void MonsterScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
	void MonsterScript::AnimationAttackStart()
	{
	}
	void MonsterScript::AnimationAttackComplete()
	{
		setState(eMonsterState::TRACING);
	}
	void MonsterScript::AnimationHittedStart()
	{
	}
	void MonsterScript::AnimationHittedComplete()
	{
		setState(eMonsterState::TRACING);
	}

	void MonsterScript::setAnimator()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimAttackKey) = std::bind(&MonsterScript::AnimationAttackStart, this);
		mpAnimator->GetCompleteEvent(mAnimAttackKey) = std::bind(&MonsterScript::AnimationAttackComplete, this);

		mpAnimator->GetStartEvent(mAnimHittedKey) = std::bind(&MonsterScript::AnimationHittedStart, this);
		mpAnimator->GetCompleteEvent(mAnimHittedKey) = std::bind(&MonsterScript::AnimationHittedComplete, this);
	}

	void MonsterScript::setPosition()
	{
		switch (meState)
		{
		case jh::eMonsterState::TRACING:
		{
			assert(mpTranform != nullptr);
			Vector3 monCurrPos = mpTranform->GetPosition();
			Vector3 dir = mpPlayerTransform->GetPosition() - monCurrPos;
			Vector3 lookDirVector(dir);
			if (isDistanceCloseToPlayer(lookDirVector))
			{
				setState(eMonsterState::ATTACKING);
				return;
			}

			dir.Normalize();
			Vector3 moveVector = monCurrPos;
			moveVector += dir * mSpeed * Time::DeltaTime();
			mpTranform->SetPosition(Vector3(moveVector.x, monCurrPos.y, monCurrPos.z));
			setLookDir(lookDirVector);
			
			break;
			return;
		}
		case jh::eMonsterState::ATTACKING:
			return;
		case jh::eMonsterState::HITTED:
		{
			if (mpPlayerScript->GetAttackType() == eAttackType::PUSH)
			{
				Vector3 monCurrPos = mpTranform->GetPosition();
				if (meLookDir == eObjectLookDirection::LEFT)
				{
					mpTranform->SetPosition(Vector3(monCurrPos.x + mHittedPushDistance * Time::DeltaTime(), monCurrPos.y, monCurrPos.z));
				}
				else
				{
					mpTranform->SetPosition(Vector3(monCurrPos.x - mHittedPushDistance * Time::DeltaTime(), monCurrPos.y, monCurrPos.z));
				}
			}
			return;
			break;
		}
		case jh::eMonsterState::DEAD:
			break;
		default:
			break;
		}
	}

	void MonsterScript::setLookDir(const jh::math::Vector3& lookDirVector)
	{
		if (lookDirVector.x < 0.0f)
		{
			meLookDir = eObjectLookDirection::LEFT;
		}
		else
		{
			meLookDir = eObjectLookDirection::RIGHT;
		}
	}

	bool MonsterScript::isDistanceCloseToPlayer(const Vector3& lookDirVector)
	{
		if (std::abs(lookDirVector.x) <= ATTACK_RANGE_DISTANCE)
		{
			setLookDir(lookDirVector);
			return true;
		}
		return false;
	}

	void MonsterScript::setAnimationFlip()
	{
		assert(mpAnimator != nullptr);
		if (meLookDir == eObjectLookDirection::RIGHT)
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(false);
		}
		else
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(true);
		}
	}
	void MonsterScript::playAnimation()
	{
		switch (meState)
		{
		case eMonsterState::TRACING:
		{
			mpAnimator->PlayAnimation(mAnimMoveKey, true);
			break;
		}
		case eMonsterState::ATTACKING:
		{
			mpAnimator->PlayAnimation(mAnimAttackKey, true);
			break;
		}
		case eMonsterState::HITTED:
		{
			mpAnimator->PlayAnimation(mAnimHittedKey, true);
			if (mpPlayerScript->GetAttackType() == eAttackType::NORMAL)
			{
				mpEffectScript->PlayAnimation(meLookDir);
			}
			break;
		}
		default:
			break;
		}
	}
}