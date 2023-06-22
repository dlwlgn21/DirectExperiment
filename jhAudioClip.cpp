#include "jhAudioClip.h"

namespace jh
{
	AudioClip::AudioClip()
		: Resource(eReousrceType::AUDIO_CLIP)
		, mpSound(nullptr)
		, mpChannel(nullptr)
		, mMinDistance(1.0f)
		, mMaxDistance(1000.0f)
		, mVolumn(1.0f)
		, mbIsLoop(false)
	{
	}

	AudioClip::~AudioClip()
	{
		assert(mpSound != nullptr);
		mpSound->release();
		mpSound = nullptr;
	}

	HRESULT AudioClip::Load(const std::wstring& filename)
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += L"\\Resources\\" + filename;
		std::wstring fullPath = path;
		std::string fullPathString(fullPath.begin(), fullPath.end());

		if (!FmodManager::GetInstace().CreateSound(fullPathString, &mpSound))
		{
			assert(false);
			return S_FALSE;
		}
		mpSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);
		return S_OK;
	}

	void AudioClip::Play()
	{
		if (mbIsLoop)	{mpSound->setMode(FMOD_LOOP_NORMAL);}
		else			{mpSound->setMode(FMOD_LOOP_OFF);}
		FmodManager::GetInstace().SoundPlay(mpSound, &mpChannel);
	}
	void AudioClip::Stop()
	{
		mpChannel->stop();
	}
	void AudioClip::Set3DAttributes(const jh::math::Vector3& pos, const jh::math::Vector3& vel)
	{
		FMOD_VECTOR fmodPos({ pos.x, pos.y, pos.z });
		FMOD_VECTOR fmodVel({ vel.x, vel.y, vel.z });

		mpChannel->set3DAttributes(&fmodPos, &fmodVel);
	}

	void AudioClip::SetVolumn(const float value)
	{
		assert(value < 1.0f && value > 0.0f);
		mVolumn = value;
	}

}