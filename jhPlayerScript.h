#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"


namespace jh
{
	class Animator;
	class Transform;

	class PlayerScript final : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void Start();
		void Complete();
		void End();

	private:
		Transform*						mpTranform;
		Animator*						mpAnimator;
		float							mSpeed;
		const std::wstring				mAnimIdleKey;
		const std::wstring				mAnimMoveKey;
		const std::wstring				mAnimLeftPunchKey;
		const std::wstring				mAnimRightPunchKey;
		bool							mbIsMoving;
		bool							mbIsPunching;
		eAnimatedObjectLookDirection    meLookDir;
	};
}

