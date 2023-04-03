#pragma once
#include "jhScript.h"
#include "jhGraphics.h"

namespace jh
{
	class Transform;
	class CameraScript final : public Script
	{
	public:
		CameraScript();
		virtual ~CameraScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		Transform* mpTranform;
		float mSpeed;
	};
}

