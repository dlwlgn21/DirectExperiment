#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class BGObeliskObject final : public AnimatedGameObject
	{
	public:
		BGObeliskObject();
		virtual ~BGObeliskObject() = default;

	protected:
		void setAnimator() override;
		void setRenderer() override;
	};
}