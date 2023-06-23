#pragma once
#include "jhScript.h"

namespace jh
{
	class GameCompleteScript final : public Script
	{
	public:
		GameCompleteScript();
		virtual ~GameCompleteScript() = default;

		void Update() override;
	};
}
