#pragma once
#include "jhGameObject.h"

namespace jh
{
	class GameCompleteObject final : public GameObject
	{
	public:
		GameCompleteObject();
		virtual ~GameCompleteObject() = default;

	private:
		void setRenderer();
		void setScript();
		void setTransform();
	};
}