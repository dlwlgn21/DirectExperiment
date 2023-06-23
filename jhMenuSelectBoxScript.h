#pragma once
#include "jhScript.h"

namespace jh
{
	enum class eMenuSelectBoxPosition
	{
		TOP,
		BOTTOM,
		COUNT
	};
	enum class eMenuSelectBoxType
	{
		START_MENU,
		GAME_OVER_MENU,
		COUNT
	};

	class Transform;
	class MenuSelectBoxScript : public Script
	{
	public:
		MenuSelectBoxScript(const eMenuSelectBoxType eType);
		virtual ~MenuSelectBoxScript() = default;

		void Initialize() override;
		void Update() override;

		void SetTopButtonObject(GameObject* pTopButton) { mpTopButton = pTopButton; }
		void SetBottomButtonObject(GameObject* pBottomButton) { mpBottomButton = pBottomButton; }

		virtual void OnSelected(const float currYPos, const float prevYPos) = 0;

		static constexpr const float START_BUTTON_Y_POS = 0.0f;
		static constexpr const float EXIT_BUTTON_Y_POS = -1.0f;

	protected:
		eMenuSelectBoxPosition				meBoxPosition;
		Transform*							mpTransform;
		GameObject*							mpTopButton;
		GameObject*							mpBottomButton;
		const eMenuSelectBoxType			meTpye;
	};
}