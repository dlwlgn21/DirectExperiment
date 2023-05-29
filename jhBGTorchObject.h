#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class BGTorchObject final : public AnimatedGameObject
	{
	public:
		BGTorchObject();
		virtual ~BGTorchObject() = default;
		void SetPosition(const float xPos);

	public:
		static const float BG_TORCH_Y_VALUE;
	protected:
		void setAnimator() override;
		void setRenderer() override;
	};
}