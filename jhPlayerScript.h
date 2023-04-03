#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"


namespace jh
{
	class Transform;
	class PlayerScript final : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	};
}

