#pragma once
#include "jhGameObject.h"

namespace jh
{
	enum class eUIBarType
	{
		HEALTH_BORDER,
		STAMINAR_BORDER,
		HEALTH_BAR,
		STAMINA_BAR,
		COUNT
	};
	class PlayerScript;
	class UIBarScript;
	class UIBarObject : public GameObject
	{
	public:
		UIBarObject(const eUIBarType eType, PlayerScript* pPlayerScript);
		virtual ~UIBarObject() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		void setRenderer();
		void setScript(PlayerScript* pPlayerScript);
	private:
		const eUIBarType meType;
	};
}