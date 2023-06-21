#pragma once
#include "jhComponent.h"

namespace jh
{
	class AudioListener : public Component
	{
	public:
		AudioListener();
		virtual ~AudioListener() = default;

		virtual void FixedUpdate() override;
	};
}