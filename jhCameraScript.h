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

		void SetPlayerTransform(Transform* pPlayerTransform) { assert(pPlayerTransform != nullptr); mpPlayerTransform = pPlayerTransform; }

	private:
		Transform*	mpTranform;
		Transform*	mpPlayerTransform;
		float		mSpeed;
	};
}

