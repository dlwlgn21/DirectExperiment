#include "jhAnimation.h"
#include "jhTexture.h"
#include "jhTime.h"
#include "jhResourceMaker.h"

static constexpr const UINT MAX_SPRITE_SHEETS_COUNT = 16;
static constexpr const UINT ATLAS_TEXTURE_SLOT_NUMBER = 12;
static constexpr const UINT FLIPED = 1;
static constexpr const UINT NO_FLIPED = 0;

using namespace jh::math;

namespace jh
{
	Animation::Animation()
		: mpAnimator(nullptr)
		, mAnimKey()
		, mpAtlasImage(nullptr)
		, mIndex(0)
		, mAccumTimer(0.0f)
		, mbIsAnimComplete(false)
		, mbIsHorizontalFlip(false)
	{
		mSpriteSheets.reserve(MAX_SPRITE_SHEETS_COUNT);
	}
	void Animation::Update()
	{
		if (mbIsAnimComplete) {return;}

		mAccumTimer += Time::DeltaTime();

		// 타이머가 해당 프레임의 유지시간보다 크면 다음 인덱스로 이동
		if (mAccumTimer >= mSpriteSheets[mIndex].Duration)
		{
			mAccumTimer = 0.0f;
			++mIndex;
			if (mIndex >= mSpriteSheets.size())
			{
				mbIsAnimComplete = true;

				// 이게 무슨이야기???? 방어코드라고 함.
				mIndex = static_cast<UINT>(mSpriteSheets.size() - 1);
			}

		}
	}
	void Animation::FixedUpdate()
	{
	}
	void Animation::Render()
	{
	}
	void Animation::Create(const std::wstring& animKey, Texture* pAtalsImage, const Vector2 leftTop, const Vector2 seperatingSize, const Vector2 offset, const UINT spriteCount, const float duration, const float magnification)
	{
		assert(pAtalsImage != nullptr);
		mpAtlasImage = pAtalsImage;
		mAnimKey = animKey;
		float width = static_cast<float>(pAtalsImage->GetWidth());
		float height = static_cast<float>(pAtalsImage->GetHeight());

		for (UINT i = 0; i < spriteCount; ++i)
		{
			Sprite sprite;
			// // 텍스처 좌표는 정규화된 좌표니까 0~1사이의 값으로 바꾸어 주어야 함
			sprite.LeftTop = Vector2((leftTop.x + (seperatingSize.x * i)) / width, leftTop.y / height);
			sprite.Size = Vector2(seperatingSize.x / width, seperatingSize.y / height);
			sprite.Offset = offset;
			sprite.Duration = duration;
			sprite.AtlasImageSize = Vector2(magnification / width, magnification / height);					// PixelShader에서 아틀라스의 크기를 알게 하기 위해서 넣어주는 값
			mSpriteSheets.push_back(sprite);
		}

	}
	void Animation::SetPipeline()
	{
		assert(mpAtlasImage != nullptr);
		mpAtlasImage->SetPipeline(ATLAS_TEXTURE_SLOT_NUMBER);
		AnimationBuffer animBuffer;
		ZeroMemory(&animBuffer, sizeof(AnimationBuffer));
		animBuffer.AnimationType = static_cast<UINT>(eAnimatnionType::SECOND_DIMENTION);
		animBuffer.LeftTop = mSpriteSheets[mIndex].LeftTop;
		animBuffer.Offset = mSpriteSheets[mIndex].Offset;
		animBuffer.Size = mSpriteSheets[mIndex].Size;
		animBuffer.AtlasImageSize = mSpriteSheets[mIndex].AtlasImageSize;
		if (mbIsHorizontalFlip)
		{
			animBuffer.IsFlip = FLIPED;
		}
		else
		{
			animBuffer.IsFlip = NO_FLIPED;
		}

		ConstantBuffer* pAnimCB = ResourceMaker::GetInstance().GetAnimationCBOrNull();
		assert(pAnimCB != nullptr);
		pAnimCB->WirteDataAtBuffer(pAnimCB->GetBuffer(), &animBuffer, sizeof(AnimationBuffer));
		pAnimCB->SetPipeline();
	}
	void Animation::Clear()
	{
		clearTexureSRV();
		clearCB();
	}
	void Animation::Reset()
	{
		mAccumTimer = 0.0f;
		mIndex = 0;
		mbIsAnimComplete = false;
	}
	void Animation::clearTexureSRV()
	{
		assert(mpAtlasImage != nullptr);
		mpAtlasImage->ClearSRV(ATLAS_TEXTURE_SLOT_NUMBER);
	}
	void Animation::clearCB()
	{
		AnimationBuffer animBuffer;
		ZeroMemory(&animBuffer, sizeof(AnimationBuffer));
		ConstantBuffer* pAnimCB = ResourceMaker::GetInstance().GetAnimationCBOrNull();
		assert(pAnimCB != nullptr);
		pAnimCB->WirteDataAtBuffer(pAnimCB->GetBuffer(), &animBuffer, sizeof(AnimationBuffer));
		pAnimCB->SetPipeline();
	}
}