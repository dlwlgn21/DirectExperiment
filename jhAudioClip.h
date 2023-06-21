#pragma once
#include "jhResource.h"
#include "jhFmodManager.h"

namespace jh
{
	class AudioClip final : public Resource
	{
	public:
		AudioClip();
		virtual ~AudioClip();

		HRESULT Load(const std::wstring& path) override;

		void Play();
		void Stop();
		void Set3DAttributes(const jh::math::Vector3& pos, const jh::math::Vector3& vel);
		void SetLoop(const bool bIsLoop) { mbIsLoop = bIsLoop; }

	private:
		FMOD::Sound*		mpSound;
		FMOD::Channel*		mpChannel;
		float				mMinDistance;
		float				mMaxDistance;
		bool				mbIsLoop;
	};
}