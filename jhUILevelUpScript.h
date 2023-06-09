#pragma once
#include "jhScript.h"

namespace jh
{
	enum class eUILevelUpState
	{
		WAIT,
		ENTERING,
		STAYING,
		COUNT
	};
	enum class eSkillPosition
	{
		TOP,
		CENTER,
		BOTTOM,
		NONE,
		COUNT
	};

	class Transform;
	class UILevelUpScript : public Script
	{
	public:
		UILevelUpScript();
		virtual ~UILevelUpScript() = default;

		void Initialize() override;
		void Update() override;

		void InitWaitingStatePosition();
		void SetCameraTransform(Transform* pCameraTransform) { assert(pCameraTransform != nullptr); mpCameraTransform = pCameraTransform; }
		void SetState(const eUILevelUpState eState) { meState = eState; }
		const eUILevelUpState GetState() const { return meState; }

	protected:
		virtual void SetWaitingPosition();
		virtual void SetStayingXYPosition() = 0;
		virtual void SetEnteringYPostion(const float yPos) = 0;
	protected:
		Transform* mpTransform;
		Transform* mpCameraTransform;
		eUILevelUpState meState;
	};
}