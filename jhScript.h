#pragma once
#include "jhComponent.h"


namespace jh
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;
	};
}

