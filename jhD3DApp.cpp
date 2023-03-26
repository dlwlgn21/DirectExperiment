#include "jhD3DApp.h"

using namespace DirectX;
using namespace Microsoft::WRL;

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

	void D3DApp::initializeVertexAndIndexBuffer()
	{
		mVertices[0] = { {0.5f,		0.5f,		0.5f},	{1.0f, 0.0f, 0.0f, 1.0f} };
		mVertices[1] = { {0.5f,		-0.5f,		0.5f},	{0.0f, 1.0f, 0.0f, 1.0f} };
		mVertices[2] = { {-0.5f,	-0.5f,		0.5f},	{0.0f, 0.0f, 1.0f, 1.0f} };
		D3D11_BUFFER_DESC vbDesc;
		ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));
		vbDesc.ByteWidth = sizeof(Vertex) * VERTEX_COUNT;
		vbDesc.Usage = D3D11_USAGE_DYNAMIC;
		vbDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = mcpDevice->CreateBuffer(
			&vbDesc,
			nullptr,
			mcpVertexBuffer.ReleaseAndGetAddressOf()
		);
		IfFailedHR(hr);

		WriteDataAtBuffer(mcpVertexBuffer.Get(), mVertices, sizeof(Vertex) * VERTEX_COUNT);

		//mcpDeviceContext->IASetVertexBuffers();
	}

	void D3DApp::createShaderAndSetShaders()
	{
		ComPtr<ID3DBlob> cpVertexShader;
		ComPtr<ID3DBlob> cpPixelShader;

		HRESULT hr;
		hr = D3DCompileFromFile(
			L"jhVertexShader.hlsl",
			0,
			0,
			"main",
			"vs_4_0_level_9_3",
			0,
			0,
			cpVertexShader.GetAddressOf(),
			mcpErrorBlob.ReleaseAndGetAddressOf()
		);

		if (FAILED(hr))
		{
			OutputDebugStringA((char*)mcpErrorBlob->GetBufferPointer());
			mcpErrorBlob->Release();
			assert(false);
			return;
		}

		hr = mcpDevice->CreateVertexShader(
			cpVertexShader->GetBufferPointer(),
			cpVertexShader->GetBufferSize(),
			nullptr,
			mcpVertexShader.ReleaseAndGetAddressOf()
		);
		IfFailedHR(hr);


		hr = D3DCompileFromFile(
			L"jhPixelShader.hlsl",
			0,
			0,
			"main",
			"ps_4_0_level_9_3",
			0,
			0,
			cpPixelShader.GetAddressOf(),
			mcpErrorBlob.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr))
		{
			OutputDebugStringA((char*)mcpErrorBlob->GetBufferPointer());
			mcpErrorBlob->Release();
			assert(false);
			return;
		}

		hr = mcpDevice->CreatePixelShader(
			cpPixelShader->GetBufferPointer(),
			cpPixelShader->GetBufferSize(),
			nullptr,
			mcpPixelShader.ReleaseAndGetAddressOf()
		);
		IfFailedHR(hr);
		mcpDeviceContext->VSSetShader(
			mcpVertexShader.Get(),
			nullptr,
			0
		);
		mcpDeviceContext->PSSetShader(
			mcpPixelShader.Get(),
			nullptr,
			0
		);
	}

	void D3DApp::initializeAndSetIA()
	{
		/*
			���� InputAssembler�� ���� �Ѱ��ֱ� ���ؼ�, �Է°��� � ������ �����Ǿ� �ִ����� �˷��־�� ��.
			�̸� �Է� ���̾ƿ��̶�� �θ�. �̷� �Է� ���̾ƿ��� �̿��ؼ�, ���̴� �ڵ忡�� ������ �Է��� � ���·� �����Ǿ� �ִ��� �Ǵ���.
		*/
		const UINT INPUT_ELEMENT_COUNT = 2;
		D3D11_INPUT_ELEMENT_DESC inputElementDesc[INPUT_ELEMENT_COUNT] =
		{
			{
				"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
				D3D11_INPUT_PER_VERTEX_DATA, 0
			},
			{
				"COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(float) * 3,
				D3D11_INPUT_PER_VERTEX_DATA, 0
			}
		};

		//HRESULT hr = mcpDevice->CreateInputLayout(
		//	inputElementDesc,
		//	2,

		//);

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
		mcpPixelShader.Reset();
		mcpVertexShader.Reset();
		mcpErrorBlob.Reset();
		mcpVertexBuffer.Reset();
		mcpDepthStencilView.Reset();
		mcpDepthStencilTextrue.Reset();
		mcpRenderTargetView.Reset();
		mcpRenderTargetTextrue.Reset();
		mcpSwapChain.Reset();
		mcpDeviceContext.Reset();
		mcpDevice.Reset();

	}
	void D3DApp::WriteDataAtBuffer(ID3D11Resource* pResource, const void* pData, const size_t dataSize)
	{
		/*
			DYNAMIC ���۴� Data�� ���� ������ ���� Ư���ϰ� �����ؾ� ��.
			CPU�� ���� ���� GPU�� �о�ٰ� �ߴµ�, �� ������ ���� ���� ������,
			���� ���� ���� GPU�� �о ���� ����. �׷� �̻��� ����� ���� ����.
			�̸� ���� ���ؼ� ����ϴ� ���� MAP/UNMAP ����.
			��, CPU(�츮�ڵ�)���� ���� �� ���� MAP�� �صּ� GPU�� ���� ���ϵ��� �ϰ�,
			���� �� ������, GPU�� ������ �� �ֵ��� UNMAP�� ���ִ� ��.
			������ DirectX ������ ���� �� �̸��� ��Ȯ�ؼ� Lock/Unlock���� ����߾��ٰ� ��.
		*/

		// ���ε� ���� ���ҽ��� ���� ����ü. ���� ���ҽ��� ��ü ���ҽ��� �Ϻ�(subset)�� ����.
		// ���� ��ü ���ҽ��� ������. MAP�� ��������� �޾ƿ� ���̹Ƿ� Ư���� �ʱ�ȭ�� �ʿ� ����
		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
		HRESULT hr = mcpDeviceContext->Map(
			pResource,							// ������ ���ҽ�. ���ؽ� ���۸� �Ѱ�����
			0,									// ���긮�ҽ��� �ε���. �츮�� ��°�� �Ѱ��ֹǷ� ������ �ʿ� ����
			D3D11_MAP_WRITE_DISCARD,			// ���ι���� ����. D3D11_MAP_WRITE_DISCARD �ǹ̴� ���� ���� ������ �ִ� ���� ������� �ǹ�.
			NULL,								// �߰� �ɼ����� GPU�� �ٺ��� ����ϰ� ���� ��, CPU�� �۾��� �����Ѵ�. ����� DO_NOT_WAIT�� ���ǵǾ� ����. �츮�� GPU�� ����� ������ ���� ��ٸ� �� ���ۿ� ���� ä���� �ϴϱ� NULL�� �ָ� ��.
			&mappedSubresource					// ���ε� ���ҽ��� ����ü�� ������. �߿��Ѱ��� ��� pData��. ���⿡ ���ҽ��� ���� �����������Ͱ� void*�� �������.
		);
		IfFailedHR(hr);

		memcpy(mappedSubresource.pData, pData, dataSize);
		mcpDeviceContext->Unmap(pResource, 0);
		/*
			���������� �̷� ����� ���踦 ���ؼ� GPU/CPU�� �и��Ͽ� ���� �����ϰ� �ϵ���� ������ ó���� �� �ְ� ��.
			���ۿ� ������ ���� �ش� ���۰� GPU�� ����ϴ����� Ȯ���ϰ� MAP/UNMAP�� �����Ѵٰ� ����صθ� ��.
		*/
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
