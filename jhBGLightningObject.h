#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	enum class eBGLightningType
	{
		LARGE,
		SMALL,
		COUNT
	};
	class BGLightningObject final : public AnimatedGameObject
	{
	public:
		BGLightningObject(const eBGLightningType eLightningType);
		virtual ~BGLightningObject() = default;
		void SetPosition(const float xPos);

	public:
		static const float BG_LARGE_LIGHTNING_Y_VALUE;
		static const float BG_SAMLL_LIGHTNING_Y_VALUE;
	protected:
		void setAnimator() override;
		void setRenderer() override;

	private:
		const eBGLightningType meType;
	};
}