#include "jhMonsterScript.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhAnimator.h"
#include "jhEffectScript.h"

using namespace jh::math;

namespace jh
{
	MonsterScript::MonsterScript(EffectScript* pEffectScript)
		: Script()
		, mpTranform(nullptr)
		, mpAnimator(nullptr)
		, mpEffectScript(pEffectScript)
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
	}
	void MonsterScript::Update()
	{
		mpTranform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(mpTranform != nullptr);
		Vector3 pos = mpTranform->GetPosition();
		mpAnimator->PlayAnimation(mAnimIdleKey, true);

		//if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		//{
		//	pos.y -= mSpeed * Time::DeltaTime();
		//}

		//if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		//{
		//	pos.y += mSpeed * Time::DeltaTime();
		//}
		//if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		//{
		//	pos.x -= mSpeed * Time::DeltaTime();
		//	meLookDir = eObjectLookDirection::RIGHT;
		//}
		//if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		//{
		//	pos.x += mSpeed * Time::DeltaTime();
		//	meLookDir = eObjectLookDirection::LEFT;
		//}

		assert(mpAnimator != nullptr);
		if (meLookDir == eObjectLookDirection::RIGHT)
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(false);
		}
		else
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(true);
		}

		//if (Input::GetKeyState(eKeyCode::Z) == eKeyState::PRESSED)
		//{
		//	mpEffectScript->PlayAnimation(meLookDir);
		//}

		mpTranform->SetPosition(pos);
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
		mpEffectScript->PlayAnimation(meLookDir);
	}
	void MonsterScript::OnTriggerStay(Collider2D* pOtherCollider)
	{
	}
	void MonsterScript::OnTriggerExit(Collider2D* pOtherCollider)
	{
	}
}