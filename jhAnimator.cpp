#include "jhAnimator.h"
#include "jhAnimation.h"
#include "jhTexture.h"

static constexpr const UINT RESEVE_SIZE = 16;

namespace jh
{
	Animator::Animator()
		: Component(eComponentType::ANIMATOR)
		, mpCurrAnimatingAnimation(nullptr)
		, mbIsAnimationLooping(false)
	{
		mAnimationMap.reserve(RESEVE_SIZE);
		mEventsMap.reserve(RESEVE_SIZE);
	}

	Animator::~Animator()
	{
		for (auto iter = mAnimationMap.begin(); iter != mAnimationMap.end(); ++iter)
		{
			if (iter->second != nullptr)
			{
				delete iter->second;
			}
		}
		for (auto iter = mEventsMap.begin(); iter != mEventsMap.end(); ++iter)
		{
			if (iter->second != nullptr)
			{
				delete iter->second;
			}
		}
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mpCurrAnimatingAnimation == nullptr)
		{
			//assert(false);
			return;
		}

		if (mpCurrAnimatingAnimation->IsAnimComplete())
		{
			Events* pEvents = FindEventsOrNull(mpCurrAnimatingAnimation->GetAnimationKey());
			if (pEvents == nullptr)
			{
				assert(false);
				return;
			}
			pEvents->CompleteEvent();
			if (mbIsAnimationLooping)
			{
				mpCurrAnimatingAnimation->Reset();
			}
		}

		mpCurrAnimatingAnimation->Update();
	}

	void Animator::FixedUpdate()
	{
	}

	void Animator::Render()
	{
	}

	Animation* Animator::Create(const std::wstring& animKey, Texture* pAtalsImage, const jh::math::Vector2 leftTop, const jh::math::Vector2 seperatingSize, const jh::math::Vector2 offset, const UINT spriteCount, const float duration, const float magnification)
	{
		if (pAtalsImage == nullptr) {assert(false);}

		Animation* pAnimation = FindAnimationOrNull(animKey);
		if (pAnimation != nullptr)	{assert(false);}

		pAnimation = new Animation();
		pAnimation->Create(animKey, pAtalsImage, leftTop, seperatingSize, offset, spriteCount, duration, magnification);
		mAnimationMap.insert(std::make_pair(animKey, pAnimation));
		Events* pEvents = new Events();
		mEventsMap.insert(std::make_pair(animKey, pEvents));
		return pAnimation;
	}

	void Animator::PlayAnimation(const std::wstring& key, bool bIsLooping)
	{
		Animation* pPrevAnim = mpCurrAnimatingAnimation;
		Events* pEvents = nullptr;

		if (pPrevAnim != nullptr)
		{
			Events* pEvents = FindEventsOrNull(pPrevAnim->GetAnimationKey());
			if (pEvents == nullptr)
			{
				return;
			}
		}
		if (pEvents != nullptr)
		{
			pEvents->EndEvent();
		}

		mpCurrAnimatingAnimation = FindAnimationOrNull(key);
		if (mpCurrAnimatingAnimation == nullptr)
		{
			assert(false); return;
		}
		//mCurrAnimatingAnimation->Reset();
		mbIsAnimationLooping = bIsLooping;

		pEvents = FindEventsOrNull(mpCurrAnimatingAnimation->GetAnimationKey());
		if (pEvents == nullptr)
		{
			return;
		}

		pEvents->StartEvent();
	}

	void Animator::PlayAnimationWithReset(const std::wstring& key, bool bIsLooping)
	{
		Animation* pPrevAnim = mpCurrAnimatingAnimation;
		Events* pEvents = nullptr;

		if (pPrevAnim != nullptr)
		{
			Events* pEvents = FindEventsOrNull(pPrevAnim->GetAnimationKey());
			if (pEvents == nullptr)
			{
				return;
			}
		}
		if (pEvents != nullptr)
		{
			pEvents->EndEvent();
		}

		mpCurrAnimatingAnimation = FindAnimationOrNull(key);
		if (mpCurrAnimatingAnimation == nullptr)
		{
			assert(false); return;
		}
		mpCurrAnimatingAnimation->Reset();
		mbIsAnimationLooping = bIsLooping;

		pEvents = FindEventsOrNull(mpCurrAnimatingAnimation->GetAnimationKey());
		if (pEvents == nullptr)
		{
			return;
		}

		pEvents->StartEvent();
	}

	void Animator::SetPipeline()
	{
		if (mpCurrAnimatingAnimation == nullptr)
		{
			//assert(false);
			return;
		}

		mpCurrAnimatingAnimation->SetPipeline();
	}

	void Animator::ClearPipeline()
	{
		if (mpCurrAnimatingAnimation == nullptr)
		{
			//assert(false);
			return;
		}

		mpCurrAnimatingAnimation->Clear();
	}
	Animation* Animator::FindAnimationOrNull(const std::wstring& key)
	{
		auto iter = mAnimationMap.find(key);
		if (iter == mAnimationMap.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	Animator::Events* Animator::FindEventsOrNull(const std::wstring& key)
	{
		auto iter = mEventsMap.find(key);
		if (iter == mEventsMap.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& key)
	{
		Events* pEvents = FindEventsOrNull(key);
		if (pEvents == nullptr)
		{
			assert(false);
		}
		return pEvents->StartEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& key)
	{
		Events* pEvents = FindEventsOrNull(key);
		if (pEvents == nullptr)
		{
			assert(false);
		}
		return pEvents->CompleteEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& key)
	{
		Events* pEvents = FindEventsOrNull(key);
		if (pEvents == nullptr)
		{
			assert(false);
		}
		return pEvents->EndEvent.mEvent;
	}

	void Animator::SetCurrAnimationHorizontalFlip(const bool isFlip)
	{
		assert(mpCurrAnimatingAnimation != nullptr);
		mpCurrAnimatingAnimation->SetHorizontalFlip(isFlip);
	}
}



