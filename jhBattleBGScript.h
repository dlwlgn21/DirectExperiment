#pragma once
#include "jhScript.h"
#include "jhMath.h"

namespace jh
{
	enum class eBGType
	{
		NORMAL,
		PARRARELL,
		COUNT
	};
	class BattleBGScript final : public Script
	{
	public:
		BattleBGScript(const eBGType eType);
		virtual ~BattleBGScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		void wirteDataAtBuffer();
		void setPipeline();
	private:
		float					mSpeed;
		jh::math::Vector2		mUVMove;
		eBGType					meType;
	};

}

