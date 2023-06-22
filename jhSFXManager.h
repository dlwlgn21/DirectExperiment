#pragma once
#include "jhEngine.h"
#include "jhSFXEnum.h"


namespace jh
{
	class AudioSource;
	class SFXManager final
	{
	public:
		static SFXManager& GetInstance()
		{
			static SFXManager instance;
			return instance;
		}
		SFXManager(const SFXManager& other) = delete;
		SFXManager& operator=(const SFXManager& other) = delete;

		void Initialize();
		void Play(const eSFXType eType);
		void Stop(const eSFXType eType);
		void SetAudioSource(const eSFXType eType, AudioSource* pAudioSource);
	
	private:
		void setVolumn(const eSFXType eType, const float value);
		void setLoop(const eSFXType eType, const bool bIsLoop);
	private:
		SFXManager()
			: mpAudioSources()
		{
			mpAudioSources.reserve(static_cast<UINT>(eSFXType::COUNT));
			mpAudioSources.resize(static_cast<UINT>(eSFXType::COUNT));
		}
		~SFXManager() = default;

	private:
		std::vector<AudioSource*>		mpAudioSources;
	};
}