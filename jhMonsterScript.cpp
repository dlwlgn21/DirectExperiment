#include "jhMonsterScript.h"
#include "jhInput.h"
#include "jhTime.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhAnimator.h"

using namespace jh::math;

namespace jh
{
	MonsterScript::MonsterScript()
		: Script()
		, mpTranform(nullptr)
		, mpAnimator(nullptr)
		, mSpeed(1.0f)
		, mAnimIdleKey(L"MonsterIdle")
		, meLookDir(eAnimatedObjectLookDirection::RIGHT)
	{
	}

	void MonsterScript::Initialize()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimIdleKey) = std::bind(&MonsterScript::Start, this);
		mpAnimator->GetCompleteEvent(mAnimIdleKey) = std::bind(&MonsterScript::Complete, this);
		mpAnimator->GetEndEvent(mAnimIdleKey) = std::bind(&MonsterScript::End, this);
	}
	void MonsterScript::Update()
	{
		mpTranform = static_cast<Transform*>(GetOwner()->GetComponentOrNull(eComponentType::TRANSFORM));
		assert(mpTranform != nullptr);
		Vector3 pos = mpTranform->GetPosition();
		mpAnimator->PlayAnimation(mAnimIdleKey, true);


		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			pos.y -= mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos.y += mSpeed * Time::DeltaTime();
		}
		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos.x -= mSpeed * Time::DeltaTime();
			meLookDir = eAnimatedObjectLookDirection::RIGHT;
		}
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos.x += mSpeed * Time::DeltaTime();
			meLookDir = eAnimatedObjectLookDirection::LEFT;
		}

		assert(mpAnimator != nullptr);
		if (meLookDir == eAnimatedObjectLookDirection::RIGHT)
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(false);
		}
		else
		{
			mpAnimator->SetCurrAnimationHorizontalFlip(true);
		}


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
}