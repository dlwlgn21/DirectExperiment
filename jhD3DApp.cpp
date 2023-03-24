#include "jhD3DApp.h"

namespace jh
{
	void D3DApp::Initialize(LPCWSTR className, LPCWSTR titleName, const UINT screenWidth, const UINT screenHeight, HINSTANCE hInstance, const int nCmdShow)
	{
		initializeWindow(className, titleName, screenWidth, screenHeight, hInstance, nCmdShow);
		initializeDirectX();
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
			screenWidth / 2,
			screenHeight / 2 - 300,
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

		ShowWindow(mHwnd, nCmdShow);
		SetForegroundWindow(mHwnd);
		SetFocus(mHwnd);
		UpdateWindow(mHwnd);

	}
	void D3DApp::initializeDirectX()
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Width = mScreenWidth;
		swapChainDesc.BufferDesc.Height = mScreenHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		swapChainDesc.Windowed = TRUE;
		swapChainDesc.OutputWindow = mHwnd;

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			NULL,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			mcpSwapChain.ReleaseAndGetAddressOf(),
			mcpDevice.ReleaseAndGetAddressOf(),
			NULL,
			mcpDeviceContext.ReleaseAndGetAddressOf()
		);
		IfFailedHR(hr);



		hr = mcpSwapChain->GetBuffer(
			0,
			IID_PPV_ARGS(mcpRenderTargetTextrue.ReleaseAndGetAddressOf())
		);
		IfFailedHR(hr);

		hr = mcpDevice->CreateRenderTargetView(
			mcpRenderTargetTextrue.Get(),
			nullptr,
			mcpRenderTargetView.ReleaseAndGetAddressOf()
		);
		IfFailedHR(hr);

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
		depthStencilDesc.Width = mScreenWidth;
		depthStencilDesc.Height = mScreenHeight;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;


		hr = mcpDevice->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			mcpDepthStencilTextrue.ReleaseAndGetAddressOf()
		);
		IfFailedHR(hr);

		hr = mcpDevice->CreateDepthStencilView(
			mcpDepthStencilTextrue.Get(),
			nullptr,
			mcpDepthStencilView.ReleaseAndGetAddressOf()
		);

		mcpDeviceContext->OMSetRenderTargets(
			1,
			mcpRenderTargetView.GetAddressOf(),
			mcpDepthStencilView.Get()
		);

		D3D11_VIEWPORT viewPort;
		ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
		viewPort.TopLeftX = 0.0f;
		viewPort.TopLeftY = 0.0f;
		viewPort.Width = static_cast<float>(mScreenWidth);
		viewPort.Height = static_cast<float>(mScreenHeight);
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;

		mcpDeviceContext->RSSetViewports(
			1,
			&viewPort
		);
	}

	void D3DApp::Run()
	{
		Update();
		FixedUpdate();
		RenderFrame();
	}
	void D3DApp::Update()
	{
	}
	void D3DApp::FixedUpdate()
	{
	}
	void D3DApp::RenderFrame()
	{
	}
	void D3DApp::Release()
	{
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
