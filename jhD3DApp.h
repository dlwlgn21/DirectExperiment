#pragma once
#include "jhEngine.h"
#include "jhGraphics.h"
#include "jhTexture.h"

namespace jh
{
	class D3DApp final
	{
	public:
		static D3DApp& GetInstance()
		{
			static D3DApp instance;
			return instance;
		}
		D3DApp(const D3DApp& other) = delete;
		D3DApp& operator=(const D3DApp& other) = delete;

		void Initialize(LPCWSTR className, LPCWSTR titleName, const UINT screenWidth, const UINT screenHeight, HINSTANCE hInstance, const int nCmdShow);
		void Run();
		void Update();
		void FixedUpdate();
		void RenderFrame();
		void Release();
		

		bool IfFailedHR(HRESULT hr);
		HWND GetHwnd() const { return mHwnd; }

	private:
		void initializeWindow(LPCWSTR className, LPCWSTR titleName, const UINT screenWidth, const UINT screenHeight, HINSTANCE hInstance, const int nCmdShow);


		__forceinline HWND GetHWND() const { return mHwnd; }
		__forceinline UINT GetScreenWidth() const { return mScreenWidth; }
		__forceinline UINT GetScreenHeight() const { return mScreenHeight; }

	private:
		D3DApp()
			: mScreenWidth()
			, mScreenHeight()
			, mHwnd()
			, mHDC()
		{
		}
		~D3DApp() = default;

	private:
		UINT mScreenWidth;
		UINT mScreenHeight;
		HWND mHwnd;
		HDC	 mHDC;
	};
}