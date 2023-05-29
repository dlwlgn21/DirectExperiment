#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class BGGroundGrassObject final : public AnimatedGameObject
	{
	public:
		BGGroundGrassObject();
		virtual ~BGGroundGrassObject() = default;
		void SetPosition(const float xPos);

	public:
		static const float BG_FOREGROUND_GRASS_Y_VALUE;
	protected:
		void setAnimator() override;
		void setRenderer() override;
	};
}