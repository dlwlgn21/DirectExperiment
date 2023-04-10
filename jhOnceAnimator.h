#pragma once
#include "jhAnimator.h"

namespace jh
{
	enum class eOnceAnimationState
	{
		WAIT,
		PLAYING,
		COMPLETE,
		COUNT
	};

	class OnceAnimator final : public Animator
	{
	public:
		OnceAnimator();
		virtual ~OnceAnimator() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void SetPlaying(bool isPlaying);
		void SetComplete() { meState = eOnceAnimationState::COMPLETE; }
	private:
		eOnceAnimationState			meState;
	};
}


