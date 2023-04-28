#include "jhEffectScript.h"
#include "jhOnceAnimator.h"

namespace jh
{
	EffectScript::EffectScript()
		: Script()
		, meState(eEffectState::WAIT)
		, mpAnimator(nullptr)
		, mpTransform(nullptr)
	{
	}

	bool EffectScript::isPlayingAnmation()
	{
		if (mpAnimator->GetState() == eOnceAnimationState::PLAYING)
		{
			return true;
		}
		return false;
	}

}


