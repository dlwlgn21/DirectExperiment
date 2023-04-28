#pragma once
#include "jhAnimatedGameObject.h"


namespace jh
{
	class PlayerDustEffectObject : public AnimatedGameObject
	{
	public:
		PlayerDustEffectObject();
		virtual ~PlayerDustEffectObject() = default;

	protected:
		void setAnimator() override;
		void setRenderer() override;
		void setScript() override;
	};
}

