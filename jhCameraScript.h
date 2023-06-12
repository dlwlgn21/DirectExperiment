#pragma once
#include "jhScript.h"
#include "jhGraphics.h"
#include "jhMath.h"

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
		void setCameraAtSpecifiedYPosition(jh::math::Vector3& pos);
		void setPlayerScript();
		void monsterAttackCamShake(jh::math::Vector3& pos);
		void skillAttackCamShake(jh::math::Vector3& pos);
		void powerAttackCamShake(jh::math::Vector3& pos);
	private:
		Transform*			mpTranform;
		Transform*			mpPlayerTransform;
		PlayerScript*		mpPlayerScript;
		float				mSpeed;
		float				mPowerAttackCamShakeTimer;
		float				mSkillAttackCamShakeTimer;
	};
}

