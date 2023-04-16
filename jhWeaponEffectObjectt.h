#pragma once
#include "jhAnimatedGameObject.h"


namespace jh
{
	class PlayerScript;
	class WeaponEffectObject : public AnimatedGameObject
	{
	public:
		WeaponEffectObject();
		virtual ~WeaponEffectObject() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void SetScript(PlayerScript* pPlayerScript);

	protected:
		void setAnimator() override;
		void setRenderer() override;
		void setScript() override;

	private:
		PlayerScript* mpPlayerScript;
	};
}

