#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"

namespace jh
{
	class Animator;
	class Transform;
	class MonsterScript final : public Script
	{
	public:
		MonsterScript();
		virtual ~MonsterScript() = default;

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
		eAnimatedObjectLookDirection    meLookDir;
	};
}

