#pragma once
#include "jhGameObject.h"

namespace jh
{
	class AnimatedGameObject : public GameObject
	{
	public:
		AnimatedGameObject();
		virtual ~AnimatedGameObject() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	protected:
		virtual void setAnimator() = 0;
		virtual void setRenderer() = 0;
	};
}

