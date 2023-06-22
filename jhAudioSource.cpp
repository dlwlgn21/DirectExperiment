#include "jhAudioSource.h"
#include "jhTransform.h"
#include "jhAudioClip.h"

using namespace jh::math;

namespace jh
{
	AudioSource::AudioSource(AudioClip* pAudioClipp)
		: Component(eComponentType::AUDIO_SOURCE)
		, mpAudioClip(pAudioClipp)
	{
		assert(mpAudioClip != nullptr);
	}


	void AudioSource::FixedUpdate()
	{
		Transform* pTransform = GetOwner()->GetTransform();
		assert(pTransform != nullptr);
		Vector3 pos = pTransform->GetPosition();
		Vector3 foward = pTransform->GetForward();
		mpAudioClip->Set3DAttributes(pos, foward);
	}

	void AudioSource::Play()
	{
		mpAudioClip->Play();

	}
	void AudioSource::Stop()
	{
		mpAudioClip->Stop();
	}
	void AudioSource::SetLoop(const bool bIsloop)
	{
		mpAudioClip->SetLoop(bIsloop);
	}
	void AudioSource::SetVolumn(const float value)
	{
		assert(value < 1.0f && value > 0.0f);
		mpAudioClip->SetVolumn(value);
	}
}
