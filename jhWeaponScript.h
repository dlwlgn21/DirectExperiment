#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"


namespace jh
{
	class Transform;
	class OnceAnimator;
	class PlayerScript;

	enum class eWeaponState
	{
		WAITING,
		ATTACKING,
		COUNT
	};

	class WeaponScript : public Script
	{
	public:
		WeaponScript(PlayerScript* pPlayer);
		virtual ~WeaponScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void Start();
		void Complete();
		void End();

	private:
		OnceAnimator*					mpAnimator;
		PlayerScript*					mpPlayerScript;
		const std::wstring				mAnimTopDownSwingKey;
		eObjectLookDirection			mePlayerLookDir;
		eWeaponState					meState;
	};

}
