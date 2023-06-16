#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class ProtectingCrystalObject final : public AnimatedGameObject
	{
	public:
		ProtectingCrystalObject();
		virtual ~ProtectingCrystalObject() = default;

	protected:
		void setAnimator() override;
		void setRenderer() override;
		void setScript() override;
		void setCollider();
	};
}