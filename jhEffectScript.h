#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"
#include "jhWeaponScript.h"


namespace jh
{
	class Transform;
	class OnceAnimator;
	class PlayerScript;

	class EffectScript : public Script
	{
	public:
		EffectScript(PlayerScript* pPlayer);
		virtual ~EffectScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void PlayAnimation();

		void Start();
		void Complete();
		void End();

	private:
		OnceAnimator*					mpAnimator;
		PlayerScript*					mpPlayerScript;
		const std::wstring				mAinmSwingEffectKey;
		eObjectLookDirection    mePlayerLookDir;
		eWeaponState					meState;
	};

}

