#pragma once
#include "jhComponent.h"

namespace jh
{
	class AudioClip;
	class AudioSource : public Component
	{
	public:
		AudioSource(AudioClip* pAudioClip);
		virtual ~AudioSource() = default;

		virtual void FixedUpdate() override;

		void Play();
		void Stop();
		void SetLoop(const bool bIsloop);

		AudioClip* GetClip() { return mpAudioClip; }

	private:
		AudioClip* mpAudioClip;
	};
}