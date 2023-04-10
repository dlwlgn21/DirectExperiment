#include "jhOnceAnimator.h"


namespace jh
{
	OnceAnimator::OnceAnimator()
		: Animator()
		, meState(eOnceAnimationState::WAIT)
	{
	}
	void OnceAnimator::Initialize()
	{
		Animator::Initialize();
	}
	void OnceAnimator::Update()
	{
		switch (meState)
		{
		case eOnceAnimationState::WAIT:
			return;
		case eOnceAnimationState::PLAYING:
			Animator::Update();
			break;
		case eOnceAnimationState::COMPLETE:
			meState = eOnceAnimationState::WAIT;
			break;
		default:
			assert(false);
			break;
		}
	}
	void OnceAnimator::FixedUpdate()
	{
		if (meState == eOnceAnimationState::WAIT || meState == eOnceAnimationState::COMPLETE)
		{
			return;
		}
		Animator::FixedUpdate();
	}
	void OnceAnimator::Render()
	{
		if (meState == eOnceAnimationState::WAIT || meState == eOnceAnimationState::COMPLETE)
		{
			return;
		}
		Animator::Render();
	}
	void OnceAnimator::SetPlaying(bool isPlaying)
	{
		if (isPlaying)	{meState = eOnceAnimationState::PLAYING;}
		else            {meState = eOnceAnimationState::WAIT;}
	}
}