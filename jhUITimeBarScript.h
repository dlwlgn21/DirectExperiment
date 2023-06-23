#pragma once
#include "jhScript.h"

namespace jh
{
	class UITimeBarScript final : public Script
	{
	public:
		UITimeBarScript();
		virtual ~UITimeBarScript() = default;

		void Update() override;
	private:
		const float mStageChangeTime;
	};
}