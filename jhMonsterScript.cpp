#include "jhMonsterScript.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhEffectScript.h"
#include "jhCollider2D.h"
#include "jhPlayerScript.h"
using namespace jh::math;

namespace jh
{
	MonsterScript::MonsterScript(EffectScript* pEffectScript, PlayerScript* pPlayerScript)
		: Script()
		, mpTranform(nullptr)
		, mpPlayerTransform(nullptr)
		, mpAnimator(nullptr)
		, mpEffectScript(pEffectScript)
		, mpPlayerScript(pPlayerScript)
		, mSpeed(1.0f)
		, mHittedPushDistance(1.0f)
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

		mpTranform->SetPosition(Vector3(6.0f, -1.7f, 4.0f));
		mpTranform->SetScale(Vector3(5.0f, 5.0f, 1.0f));
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
	void MonsterScript::OnCollisionEnter(Collider2D* pOtherCollider)
	{
	}
	void MonsterScript::OnCollisionStay(Collider2D* pOtherCollider)
	{
	}
	void MonsterScript::OnCollisionExit(Collider2D* pOtherCollider)
	{
	}
	void MonsterScript::OnTriggerEnter(Collider2D* pOtherCollider)
	{
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER)
		{
			setState(eMonsterState::ATTACKING);
		}

		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER_WEAPON)
		{
			mpEffectScript->PlayAnimation(meLookDir);
		}
	}
	void MonsterScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER_WEAPON)
		{
			mpEffectScript->PlayAnimation(meLookDir);
			setState(eMonsterState::HITTED);
		}
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
			dir.Normalize();
			Vector3 moveVector = monCurrPos;
			moveVector += dir * mSpeed * Time::DeltaTime();
			mpTranform->SetPosition(Vector3(moveVector.x, monCurrPos.y, monCurrPos.z));
			setLookDir(lookDirVector);
			break;
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

	void MonsterScript::setLookDir(const jh::math::Vector3& lookDirvector)
	{
		if (lookDirvector.x < 0.0f)
		{
			meLookDir = eObjectLookDirection::LEFT;
		}
		else
		{
			meLookDir = eObjectLookDirection::RIGHT;
		}
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
			mpAnimator->PlayAnimation(mAnimMoveKey, true);
			break;
		case eMonsterState::ATTACKING:
			mpAnimator->PlayAnimation(mAnimAttackKey, true);
			break;
		case eMonsterState::HITTED:
			mpAnimator->PlayAnimation(mAnimHittedKey, true);
			break;
		default:
			break;
		}
	}
}