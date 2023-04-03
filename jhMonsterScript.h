#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"

namespace jh
{
	class Transform;
	class MonsterScript final : public Script
	{
	public:
		MonsterScript();
		virtual ~MonsterScript();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	};
}

