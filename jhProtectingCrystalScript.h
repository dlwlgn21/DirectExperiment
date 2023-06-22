#pragma once
#include "jhScript.h"

namespace jh
{
	enum class eCrystalState
	{
		ENTERING,
		STAYING,
		HITTED,
		DEAD,
		COUNT
	};
	class PlayerScript;
	class Transform;
	class ProtectingCrystalScript final : public Script
	{
	public:
		ProtectingCrystalScript();
		virtual ~ProtectingCrystalScript() = default;

		void Initialize() override;
		void Update() override;

		void SetState(const eCrystalState eState) { meCrystalState = eState; }
		eCrystalState GetState() const { return meCrystalState; }

		void DecreaseHP(UINT damage);

		void SetPlayerScript(PlayerScript* pPlayerSciript) {assert(pPlayerSciript != nullptr); mpPlayerScript= pPlayerSciript;}
		
	private:
		void setFinalPosision(const float xPos, const float yPos);

	private:
		Transform*			mpTransform;
		float				mSpeed;
		int					mCurrHp;
		float				mInvincivlityTimer;
		eCrystalState		meCrystalState;
		PlayerScript*		mpPlayerScript;
	};
}

