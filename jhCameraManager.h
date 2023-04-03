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
		Camera* GetMainCamera() { assert(mpMainCam != nullptr); return mpMainCam; }

		void Render() { assert(mpMainCam != nullptr); mpMainCam->Render(); }

	private:
		CameraManager() : mpMainCam(nullptr) {}
		~CameraManager() = default;

	private:
		Camera* mpMainCam;
	};
}

