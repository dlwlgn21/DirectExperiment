#pragma once
#include "jhScript.h"
#include "jhGraphics.h"

namespace jh
{
	class Transform;
	class PlayerScript;
	class CameraScript final : public Script
	{
	public:
		CameraScript();
		virtual ~CameraScript() = default;

		void Initialize() override;
		void Update() override;

		void SetPlayerTransform(Transform* pPlayerTransform);

		
	private:
		void setPlayerScript();
	private:
		Transform*			mpTranform;
		Transform*			mpPlayerTransform;
		PlayerScript*		mpPlayerScript;
		float				mSpeed;
	};
}

