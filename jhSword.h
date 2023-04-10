#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class PlayerScript;
	class Sword final : public AnimatedGameObject
	{
	public:
		Sword();
		virtual ~Sword() = default;
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

