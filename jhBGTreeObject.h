#pragma once
#include "jhAnimatedGameObject.h"

namespace jh
{
	enum class eTreeShapeType
	{
		HIGH,
		WIDE,
		COUNT
	};

	enum class eTreeAnimType
	{
		BLOOD,
		MARKINGS,
		BLINK,
		OVER_GROWN,
		COUNT
	};
	class Animator;
	class Texture;
	class BGTreeObject final : public AnimatedGameObject
	{
	public:
		BGTreeObject(const eTreeShapeType eShapeType, const eTreeAnimType eType);
		virtual ~BGTreeObject() = default;

	protected:
		void setAnimator() override;
		void setRenderer() override;

	protected:
		void makeAnimation(Animator* pAnimator, Texture* pAtalsImage, const jh::math::Vector2 leftTop, const jh::math::Vector2 seperatingSize, const jh::math::Vector2 offset, const UINT spriteCount, const float duration, const float magnification);

	private:
		const eTreeShapeType	meTreeShapeType;
		const eTreeAnimType		meTreeAnimType;
	};
}