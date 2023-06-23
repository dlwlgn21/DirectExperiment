#pragma once
#include "jhGameObject.h"

namespace jh
{
	enum class eMenuButtonType
	{
		START,
		QUIT,
		RESTART,
		START_SELECT_BOX,
		GAME_OVER_SELECT_BOX,
		COUNT
	};
	class MenuButtonObejct final : public GameObject
	{
	public:
		MenuButtonObejct(const eMenuButtonType eType);
		virtual ~MenuButtonObejct() = default;

	private:
		void setRenderer(const eMenuButtonType eType);
		void setTransform(const eMenuButtonType eType);
	};
}