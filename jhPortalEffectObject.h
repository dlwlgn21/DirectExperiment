#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class PortalEffectObject : public AnimatedGameObject
	{
	public:
		PortalEffectObject();
		virtual ~PortalEffectObject() = default;

	protected:
		void setAnimator() override;
		void setRenderer() override;
		void setScript() override;
	};
}