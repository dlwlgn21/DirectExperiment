#pragma once
#include "jhScript.h"

namespace jh
{
	enum class eEffectState
	{
		WAIT,
		PLAYING,
		COUNT
	};
	class Transform;
	class OnceAnimator;
	class EffectScript : public Script
	{
	public:
		EffectScript();
		virtual ~EffectScript() = default;

		bool isPlayingAnmation();
		void SetStatePlaying() { meState = eEffectState::PLAYING; }
	protected:
		void SetState(const eEffectState eState) { meState = eState; }
		virtual void setAnimator() = 0;
	protected:
		eEffectState		meState;
		Transform*			mpTransform;
		OnceAnimator*		mpAnimator;
	};
}