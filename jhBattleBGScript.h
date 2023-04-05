#pragma once
#include "jhScript.h"
#include "jhMath.h"

namespace jh
{
	class BattleBGScript final : public Script
	{
	public:
		BattleBGScript();
		virtual ~BattleBGScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		void wirteDataAtBuffer();
		void setPipeline();
	private:
		const float					mSpeed;
		jh::math::Vector2			mUVMove;
	};

}

