#pragma once
#include "jhMenuSelectBoxScript.h"

namespace jh
{
	class Transform;
	class StartMenuSelectBoxScrip : public MenuSelectBoxScript
	{
	public:
		StartMenuSelectBoxScrip();
		virtual ~StartMenuSelectBoxScrip() = default;
		void OnSelected(const float currYPos, const float prevYPos) override;
	};
}