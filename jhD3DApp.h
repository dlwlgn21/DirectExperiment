#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <memory>
#include <d3d11.h>
#include <wrl/client.h>
#include <assert.h>

#pragma comment(lib, "d3d11.lib")

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

	private:
		void initializeWindow(LPCWSTR className, LPCWSTR titleName, const UINT screenWidth, const UINT screenHeight, HINSTANCE hInstance, const int nCmdShow);
		void initializeDirectX();


		__forceinline HWND GetHWND() const { return mHwnd; }
		__forceinline UINT GetScreenWidth() const { return mScreenWidth; }
		__forceinline UINT GetScreenHeight() const { return mScreenHeight; }

	private:
		D3DApp()
			: mScreenWidth()
			, mScreenHeight()
			, mHwnd()
			, mcpDevice(nullptr)
			, mcpDeviceContext(nullptr)
		{

		}
		~D3DApp() = default;
	private:
		UINT mScreenWidth;
		UINT mScreenHeight;
		HWND mHwnd;

		Microsoft::WRL::ComPtr<ID3D11Device>			mcpDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		mcpDeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain>			mcpSwapChain;

		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mcpRenderTargetTextrue;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  mcpRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>			mcpDepthStencilTextrue;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	mcpDepthStencilView;



	};
}