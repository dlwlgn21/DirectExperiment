#pragma once
#include "jhGameObject.h"

namespace jh
{
	class DebugObject final : public GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject() = default;

		void FixedUpdate() override;

	private:
	};
}

