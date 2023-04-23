#pragma once
#include "jhCamera.h"

namespace jh
{
	
	class CameraManager final
	{
	public:
		static CameraManager& GetInstance()
		{
			static CameraManager instance;
			return instance;
		}
		CameraManager(const CameraManager& other) = delete;
		CameraManager& operator=(const CameraManager& other) = delete;
		

		void SetCamera(Camera* pCamera) { assert(pCamera != nullptr); mpMainCam = pCamera; }
		void SetUICamera(Camera* pUICamera) { assert(pUICamera != nullptr); mpUICam = pUICamera; }
		Camera* GetMainCamera() { assert(mpMainCam != nullptr); return mpMainCam; }
		
		__forceinline void Render() { assert(mpMainCam != nullptr && mpUICam != nullptr); mpMainCam->Render(); mpUICam->Render(); }

	private:
		CameraManager() 
			: mpMainCam(nullptr)
			, mpUICam(nullptr)
		{}
		~CameraManager() = default;

	private:
		Camera* mpMainCam;
		Camera* mpUICam;
	};
}

