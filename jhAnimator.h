#pragma once
#include "jhComponent.h"
#include <functional>
#include "jhMath.h"


namespace jh
{
	class Texture;
	class Animation;
	class Animator final : public Component
	{
	public:
		struct Events
		{
			struct Event
			{
				void operator=(std::function<void()> func)
				{
					mEvent = std::move(func);
				}

				void operator()()
				{
					if (mEvent != nullptr)
					{
						mEvent();
						return;
					}
					//assert(false);
				}
				std::function<void()> mEvent;

			};
			Event StartEvent;					// �ִϸ��̼��� ���۵� �� ȣ��
			Event CompleteEvent;				// �� �ִϸ��̼��� �� ����Ŭ �������� ���� ȣ��
			Event EndEvent;						// �ִϸ��̼��� ��ü�Ǿ��� ����
		};

		Animator();
		virtual ~Animator();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

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
		void PlayAnimation(const std::wstring& key, bool bIsLooping);
		void SetPipeline();
		void ClearPipeline();

		__forceinline Animation* GetCurrentAnimatingAnimation() const { return mpCurrAnimatingAnimation; }
		Animation* FindAnimationOrNull(const std::wstring& key);
		Events* FindEventsOrNull(const std::wstring& key);

		std::function<void()>& GetStartEvent(const std::wstring& key);
		std::function<void()>& GetCompleteEvent(const std::wstring& key);
		std::function<void()>& GetEndEvent(const std::wstring& key);

		void SetCurrAnimationHorizontalFlip(const bool isFlip);

	private:
		std::unordered_map<std::wstring, Animation*>	mAnimationMap;
		std::unordered_map<std::wstring, Events*>		mEventsMap;
		Animation* mpCurrAnimatingAnimation;
		bool											mbIsAnimationLooping;
	};
}
