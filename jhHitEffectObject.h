#pragma once
#include "jhAnimatedGameObject.h"


namespace jh
{
	class MonsterScript;
	class HitEffectObject : public AnimatedGameObject
	{
	public:
		HitEffectObject();
		virtual ~HitEffectObject() = default;

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

