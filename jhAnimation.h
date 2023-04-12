#pragma once
#include "jhEngine.h"
#include "jhGraphics.h"

namespace jh
{
	class Animator;
	class Texture;
	class Animation final
	{
	public:
		Animation();
		~Animation() = default;

		struct Sprite
		{
			jh::math::Vector2 LeftTop;
			jh::math::Vector2 Size;
			jh::math::Vector2 Offset;
			jh::math::Vector2 AtlasImageSize;
			float Duration;

			Sprite()
				: LeftTop(jh::math::Vector2::Zero)
				, Size(jh::math::Vector2::Zero)
				, Offset(jh::math::Vector2::Zero)
				, AtlasImageSize(jh::math::Vector2::Zero)
				, Duration(0.0f)
			{
			}
		};

		void Update();
		void FixedUpdate();
		void Render();

		void Create(
			const std::wstring& animKey, 
			Texture* pAtalsImage, 
			const jh::math::Vector2 leftTop,
			const jh::math::Vector2 seperatingSize,
			const jh::math::Vector2 offset,
			const UINT spriteCount, 
			const float duration, 
			const float magnification
		);

		void SetPipeline();
		void ClearPipeline();
		void Reset();

		__forceinline bool IsAnimComplete()   const	{ return mbIsAnimComplete; }
		const std::wstring& GetAnimationKey() const	{ return mAnimKey; }
		void SetHorizontalFlip(const bool isFlip)	{ mbIsHorizontalFlip = isFlip; }

	private:
		void clearTexureSRV();
		void clearCB();
	private:
		std::wstring			mAnimKey;
		Animator*				mpAnimator;
		Texture*				mpAtlasImage;
		std::vector<Sprite>		mSpriteSheets;
		UINT					mIndex;
		float					mAccumTimer;
		bool					mbIsAnimComplete;
		bool					mbIsHorizontalFlip;
	};
}

