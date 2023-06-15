#pragma once
#include "jhGameObject.h"
#include "jhMath.h"

namespace jh
{
	class Player;
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
		virtual void setAnimator();
		virtual void setRenderer();
		virtual void setScript();
	};
}

