#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class ObeliskObject final : public AnimatedGameObject
	{
	public:
		ObeliskObject();
		virtual ~ObeliskObject() = default;

	protected:
		void setAnimator() override;
		void setRenderer() override;
	};
}