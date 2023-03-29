#include "jhD3DApp.h"
#include "jhTime.h"
#include "jhInput.h"
#include "jhGraphicDeviceDX11.h"


using namespace DirectX;
using namespace Microsoft::WRL;

namespace jh
{

	void D3DApp::Initialize(LPCWSTR className, LPCWSTR titleName, const UINT screenWidth, const UINT screenHeight, HINSTANCE hInstance, const int nCmdShow)
	{
		initializeWindow(className, titleName, screenWidth, screenHeight, hInstance, nCmdShow);
		Time::Initialize();
		Input::Initialize();
		graphics::GraphicDeviceDX11::GetInstance().InitializeDevice(mScreenWidth, mScreenHeight, mHwnd);
	}
	void D3DApp::initializeWindow(LPCWSTR className, LPCWSTR titleName, const UINT screenWidth, const UINT screenHeight, HINSTANCE hInstance, const int nCmdShow)
	{
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;
		RECT wr{ 0, 0, static_cast<LONG>(mScreenWidth), static_cast<LONG>(mScreenHeight) };
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

		mHwnd = CreateWindowW(
			className,
			titleName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			wr.right - wr.left,
			wr.bottom - wr.top,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		if (mHwnd == nullptr)
		{
			assert(false);
		}
		mHDC = GetDC(mHwnd);
		ShowWindow(mHwnd, nCmdShow);
		SetForegroundWindow(mHwnd);
		SetFocus(mHwnd);
		UpdateWindow(mHwnd);
	}

	void D3DApp::Run()
	{
		Update();
		FixedUpdate();
		RenderFrame();
	}
	void D3DApp::Update()
	{
		Time::Update();
		Input::Update();
		graphics::GraphicDeviceDX11::GetInstance().Update();
	}
	void D3DApp::FixedUpdate()
	{
		graphics::GraphicDeviceDX11::GetInstance().FixedUpdate();
	}
	void D3DApp::RenderFrame()
	{
		Time::Render(mHDC);
		graphics::GraphicDeviceDX11::GetInstance().Render();
	}
	void D3DApp::Release()
	{
		graphics::GraphicDeviceDX11::GetInstance().Release();
	}
	bool D3DApp::IfFailedHR(HRESULT hr)
	{
		if (FAILED(hr))
		{
			assert(false);
			return false;
		}
		return true;
	}
}
