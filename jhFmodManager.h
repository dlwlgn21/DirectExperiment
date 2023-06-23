#pragma once
#include "jhEngine.h"
#include "jhMath.h"

#include "Fmod/Include/fmod.hpp"
#include "Fmod/Include/fmod_codec.h"
#include "Fmod/Include/fmod_common.h"
#include "Fmod/Include/fmod_studio.hpp"

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#pragma comment(lib, "fmodstudioL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#pragma comment(lib, "fmodstudio_vc.lib")
#endif // _DEBUG

namespace jh
{
	class FmodManager final
	{
	public:
		static FmodManager& GetInstace()
		{
			static FmodManager instance;
			return instance;
		}
		FmodManager(const FmodManager& other) = delete;
		FmodManager& operator=(const FmodManager& other) = delete;

		void Initialize();
		bool CreateSound(const std::string& path, FMOD::Sound** sound);
		void SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel);
		void Set3DListenerAttributes(const jh::math::Vector3* pos, const jh::math::Vector3* vel, const jh::math::Vector3* forward, const jh::math::Vector3* up);
		void Release();

	private:
		FmodManager()
			: mpSystem(nullptr)
			, mpCoreSystem(nullptr)
		{

		}
		~FmodManager() = default;

	private:
		FMOD::Studio::System*	mpSystem;
		FMOD::System*			mpCoreSystem;
	};
}