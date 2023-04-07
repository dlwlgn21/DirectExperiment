#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class Sword final : public AnimatedGameObject
	{
	public:
		Sword();
		virtual ~Sword() = default;
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	protected:
		void setAnimator() override;
		void setRenderer() override;
		void setScript() override;
	};
}

