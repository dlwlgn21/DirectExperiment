#pragma once
#include "jhGameObject.h"

namespace jh
{
	class UITimeBarObject final : public GameObject
	{
	public:
		UITimeBarObject();
		virtual ~UITimeBarObject() = default;

	private:
		void setRenderer();
		void setScript();
		void setTransform();
	};
}