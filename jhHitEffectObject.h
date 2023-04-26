#pragma once
#include "jhAnimatedGameObject.h"


namespace jh
{
	class MonsterScript;
	class HitEffectObject : public AnimatedGameObject
	{
	public:
		HitEffectObject();
		virtual ~HitEffectObject() = default;

	protected:
		void setAnimator() override;
		void setRenderer() override;
		void setScript() override;

	};
}

