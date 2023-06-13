#pragma once
#include "jhGameObject.h"

namespace jh
{
	class UILevelUpBorderObject : public GameObject
	{
	public:
		UILevelUpBorderObject();
		virtual ~UILevelUpBorderObject() = default;

	private:
		void setRenderer();
		void setScript();
		void setTransform();
	};
}