#pragma once
#include "jhAudioListener.h"
#include "jhTransform.h"
#include "jhFmodManager.h"

using namespace jh::math;

namespace jh
{
	AudioListener::AudioListener()
		: Component(eComponentType::AUDIO_LISTENER)
	{

	}


	void AudioListener::FixedUpdate()
	{
		Transform* pTransform = GetOwner()->GetTransform();
		assert(pTransform != nullptr);
		Vector3 pos = pTransform->GetPosition();
		Vector3 foward = pTransform->GetForward();
		Vector3 up = pTransform->GetUp();
		Vector3 vel = { 0.0f, 0.0f, 0.0f };

		FmodManager::GetInstace().Set3DListenerAttributes(&pos, &vel, &foward, &up);
	}
}