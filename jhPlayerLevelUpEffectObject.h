#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class PlayerScript;
	class PlayerLevelUpEffectObject final : public AnimatedGameObject
	{
	public:
		PlayerLevelUpEffectObject(PlayerScript* pPlayerScript);
		virtual ~PlayerLevelUpEffectObject() = default;

	
	private:
		void setAnimator() override;
		void setRenderer() override;
		void setScript(PlayerScript* pPlayerScript);
	};
}