#pragma once
#include "jhMenuSelectBoxScript.h"

namespace jh
{

	class Transform;
	class GameOberMenuSelectBoxScript : public MenuSelectBoxScript
	{
	public:
		GameOberMenuSelectBoxScript();
		virtual ~GameOberMenuSelectBoxScript() = default;
		void OnSelected(const float currYPos, const float prevYPos) override;
	};
}