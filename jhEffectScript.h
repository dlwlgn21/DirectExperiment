#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"
#include "jhWeaponScript.h"


namespace jh
{
	class Transform;
	class OnceAnimator;
	class EffectScript : public Script
	{
	public:
		EffectScript();
		virtual ~EffectScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void PlayAnimation(eObjectLookDirection eLookDir);


		void Start();
		void Complete();
		void End();

	private:
		OnceAnimator*					mpAnimator;
		const std::wstring				mAnimHitEffectKey;
		eWeaponState					meState;
	};

}

