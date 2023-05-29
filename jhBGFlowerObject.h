#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class BGFlowerObject final : public AnimatedGameObject
	{
	public:
		BGFlowerObject();
		virtual ~BGFlowerObject() = default;
		void SetPosition(const float xPos);

	public:
		static const float BG_FLOWER_Y_VALUE;
	protected:
		void setAnimator() override;
		void setRenderer() override;
	};
}