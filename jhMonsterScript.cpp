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
		, mAnimIdleKey(L"MonsterIdle")
		, meLookDir(eObjectLookDirection::RIGHT)
	{
	}

	void MonsterScript::Initialize()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimIdleKey) = std::bind(&MonsterScript::Start, this);
		mpAnimator->GetCompleteEvent(mAnimIdleKey) = std::bind(&MonsterScript::Complete, this);
		mpAnimator->GetEndEvent(mAnimIdleKey) = std::bind(&MonsterScript::End, this);

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
	}
	void MonsterScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
		if (pOtherCollider->GetColliderLayerType() == eColliderLayerType::PLAYER_WEAPON)
		{
			mpEffectScript->PlayAnimation(meLookDir);
		}
	}
	void MonsterScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
	void MonsterScript::setPosition()
	{
		assert(mpTranform != nullptr);
		Vector3 monCurrPos = mpTranform->GetPosition();
		Vector3 dir = mpPlayerTransform->GetPosition() - monCurrPos;
		Vector3 lookDirVector(dir);
		dir.Normalize();
		Vector3 moveVector = monCurrPos;
		moveVector += dir * mSpeed * Time::DeltaTime();
		mpTranform->SetPosition(Vector3(moveVector.x, monCurrPos.y, monCurrPos.z));

		if (lookDirVector.x < 0.0f)
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
		mpAnimator->PlayAnimation(mAnimIdleKey, true);
	}
}