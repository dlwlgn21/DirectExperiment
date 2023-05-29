#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	class BGMushRoomStatueObject final : public AnimatedGameObject
	{
	public:
		BGMushRoomStatueObject();
		virtual ~BGMushRoomStatueObject() = default;
		void SetPosition(const float xPos);

	public:
		static const float BG_MUSHROOM_STATUE_Y_VALUE;
	protected:
		void setAnimator() override;
		void setRenderer() override;
	};
}