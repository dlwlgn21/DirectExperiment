#pragma once
#include "jhScript.h"
#include "jhUIBarObject.h"

namespace jh
{
	class PlayerScript;
	class UIBarScript : public Script
	{
	public:
		UIBarScript(const eUIBarType eType, PlayerScript* pPlayer);
		virtual ~UIBarScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		eUIBarType			meType;
		PlayerScript*		mpPlayerScript;
	};
}
