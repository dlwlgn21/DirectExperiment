#include "jhGraphicDeviceDX11.h"
#include "jhTime.h"
#include "jhInput.h"

using namespace DirectX;

namespace jh::graphics
{
	void GraphicDeviceDX11::InitializeDevice(const UINT screenWidth, const UINT screenHeight, HWND hwnd)
	{
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Width = screenWidth;
		swapChainDesc.BufferDesc.Height = screenHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		swapChainDesc.Windowed = TRUE;
		swapChainDesc.OutputWindow = hwnd;

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
		ifFailedHR(hr);



		hr = mcpSwapChain->GetBuffer(
			0,
			IID_PPV_ARGS(mcpRenderTargetTextrue.ReleaseAndGetAddressOf())
		);
		ifFailedHR(hr);

		hr = mcpDevice->CreateRenderTargetView(
			mcpRenderTargetTextrue.Get(),
			nullptr,
			mcpRenderTargetView.ReleaseAndGetAddressOf()
		);
		ifFailedHR(hr);

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
		ifFailedHR(hr);

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


		initializePipelineAndReources();
	}

	void GraphicDeviceDX11::Update()
	{
		static const float SPEED = 1.0f;
		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			mZ -= XM_PI * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			mZ += XM_PI * Time::DeltaTime();
		}


		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			mX -= SPEED * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			mX += SPEED * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			mY += SPEED * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			mY -= SPEED * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::N_1) == eKeyState::PRESSED)
		{
			Time::SetScale(1.0f);
		}
		if (Input::GetKeyState(eKeyCode::N_2) == eKeyState::PRESSED)
		{
			Time::SetScale(2.0f);
		}
		if (Input::GetKeyState(eKeyCode::N_3) == eKeyState::PRESSED)
		{
			Time::SetScale(3.0f);
		}

		mWorldMat = XMMatrixIdentity();
		mWorldMat *= XMMatrixRotationZ(mZ);
		mWorldMat *= XMMatrixTranslation(mX, mY, 0.0f);
	}

	void GraphicDeviceDX11::FixedUpdate()
	{
		MatrixBuffer matBuffer;
		matBuffer.worldMat = DirectX::XMMatrixTranspose(mWorldMat);
		WriteDataAtBuffer(mcpConstantBuffer.Get(), &matBuffer, sizeof(MatrixBuffer));
	}

	void GraphicDeviceDX11::Render()
	{
		static float CLEAR_COLOR[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mcpDeviceContext->ClearRenderTargetView(
			mcpRenderTargetView.Get(),
			CLEAR_COLOR
		);
		mcpDeviceContext->ClearDepthStencilView(
			mcpDepthStencilView.Get(),
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f,                                               // 이 값으로 뎊스 버퍼를 지움.
			0                                                   // 이 값으로 스텐실 버퍼를 지움
		);

		UINT stride = sizeof(Vertex);		// 하나의 버텍스 정보가 몇 바이트인지를 표시
		UINT offset = 0;					// 데이터의 첫번째 위치를 바이트로 지정

		/*mcpDeviceContext->IASetVertexBuffers(
			0,
			1,
			mcpVertexBuffer.GetAddressOf(),
			&stride,
			&offset
		);*/
		mspMesh->SetVertexBuffer();


		mcpDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		mcpDeviceContext->PSSetSamplers(POINT_SAMPLER_SLOT_NUMBER, 1, mcpPointSampler.GetAddressOf());

		mcpDeviceContext->PSSetShaderResources(
			DEFAULT_TEXTURE_SLOT_NUMBER,
			1,
			mspTexture->GetSRV().GetAddressOf()
		);
		mcpDeviceContext->OMSetBlendState(mcpBlendState.Get(), nullptr, 0xffffffff);

		mspMesh->Render();
		mcpSwapChain->Present(0, 0);
	}

	void GraphicDeviceDX11::WriteDataAtBuffer(ID3D11Resource* pResource, const void* pData, const size_t dataSize)
	{
		/*
			DYNAMIC 버퍼는 Data를 쓰는 과정을 조금 특이하게 진행해야 함.
			CPU가 값을 쓰고 GPU가 읽어간다고 했는데, 이 과정이 서로 맞지 않으면,
			값을 쓰는 도중 GPU가 읽어갈 수도 있음. 그럼 이상한 결과가 나올 것임.
			이를 막기 위해서 사용하는 것이 MAP/UNMAP 구조.
			즉, CPU(우리코드)에서 값을 쓸 때는 MAP을 해둬서 GPU가 읽지 못하도록 하고,
			값을 다 쓰고나면, GPU가 가져갈 수 있도록 UNMAP을 해주는 것.
			과거의 DirectX 버전은 조금 더 이름이 명확해서 Lock/Unlock으로 사용했었다고 함.
		*/

		// 매핑된 서브 리소스에 대한 구조체. 서브 리소스란 전체 리소스의 일부(subset)를 말함.
		// 물론 전체 리소스도 가능함. MAP의 결과값으로 받아올 것이므로 특별히 초기화는 필요 없음
		D3D11_MAPPED_SUBRESOURCE mappedSubresource;
		HRESULT hr = mcpDeviceContext->Map(
			pResource,							// 매핑할 리소스. 버텍스 버퍼를 넘겨줬음
			0,									// 서브리소스의 인덱스. 우리는 통째로 넘겨주므로 지정할 필요 없음
			D3D11_MAP_WRITE_DISCARD,			// 매핑방식을 지정. D3D11_MAP_WRITE_DISCARD 의미는 값을 쓰고 이전에 있던 값은 버리라는 의미.
			NULL,								// 추가 옵션으로 GPU가 바빠서 대기하고 있을 때, CPU의 작업을 지정한다. 현재는 DO_NOT_WAIT만 정의되어 있음. 우리는 GPU가 사용을 끝낼때 까지 기다린 후 버퍼에 값을 채워야 하니까 NULL을 주면 됨.
			&mappedSubresource					// 매핑된 리소스의 구조체를 돌려줌. 중요한것은 멤버 pData임. 여기에 리소스의 실제 데이터포인터가 void*로 들어있음.
		);
		ifFailedHR(hr);

		memcpy(mappedSubresource.pData, pData, dataSize);
		mcpDeviceContext->Unmap(pResource, 0);
		/*
			복잡하지만 이런 방식의 설계를 통해서 GPU/CPU를 분리하여 더욱 안전하게 하드웨어 가속을 처리할 수 있게 됨.
			버퍼에 접근할 때는 해당 버퍼가 GPU가 사용하는지를 확인하고 MAP/UNMAP을 수행한다고 기억해두면 됨.
		*/
	}


	void GraphicDeviceDX11::Release()
	{
		mcpConstantBuffer.Reset();
		mcpBlendState.Reset();
		mspTexture.reset();
		mspMesh.reset();
		mcpPointSampler.Reset();
		mcpPixelShader.Reset();
		mcpVertexShader.Reset();
		mcpVSBlob.Reset();
		mcpPSBlob.Reset();
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
	bool GraphicDeviceDX11::ifFailedHR(HRESULT hr)
	{
		if (FAILED(hr))
		{
			assert(false);
			return false;
		}
		return true;
	}
	void GraphicDeviceDX11::initializePipelineAndReources()
	{
		initializeVertexAndIndexBuffer();
		createAndSetShaders();
		createAndSetSamplerState();
		createAndSetBlendState();
		createConstantBufferForTransform();
		initializeInputLayoutAndSetIA();
		loadTexture();
	}
	void GraphicDeviceDX11::initializeVertexAndIndexBuffer()
	{
		mVertices[0] = { {-0.5f,		0.5f,		0.0f},	{0.0f, 0.0f} };
		mVertices[1] = { {0.5f,			0.5f,		0.0f},	{1.0f, 0.0f} };
		mVertices[2] = { {-0.5f,		-0.5f,		0.0f},	{0.0f, 1.0f} };
		mVertices[3] = { {0.5f,			-0.5f,		0.0f},	{1.0f, 1.0f} };
		mspMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * VERTEX_COUNT);

		//WriteDataAtBuffer(mcpVertexBuffer.Get(), mVertices, sizeof(Vertex) * VERTEX_COUNT);
	}
	void GraphicDeviceDX11::createAndSetShaders()
	{
		HRESULT hr;
		hr = D3DCompileFromFile(
			L"jhVertexShader.hlsl",
			0,
			0,
			"main",
			"vs_4_0_level_9_3",
			0,
			0,
			mcpVSBlob.GetAddressOf(),
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
			mcpVSBlob->GetBufferPointer(),
			mcpVSBlob->GetBufferSize(),
			nullptr,
			mcpVertexShader.ReleaseAndGetAddressOf()
		);
		ifFailedHR(hr);


		hr = D3DCompileFromFile(
			L"jhPixelShader.hlsl",
			0,
			0,
			"main",
			"ps_4_0_level_9_3",
			0,
			0,
			mcpPSBlob.GetAddressOf(),
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
			mcpPSBlob->GetBufferPointer(),
			mcpPSBlob->GetBufferSize(),
			nullptr,
			mcpPixelShader.ReleaseAndGetAddressOf()
		);
		ifFailedHR(hr);
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
	void GraphicDeviceDX11::createAndSetSamplerState()
	{
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = 0;
		mcpDevice->CreateSamplerState(
			&samplerDesc,
			mcpPointSampler.ReleaseAndGetAddressOf()
		);
	}
	void GraphicDeviceDX11::createAndSetBlendState()
	{
		D3D11_BLEND_DESC desc;
		HRESULT hr;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;				// SRC -> PixelShader의 출력 RGB값
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;		// Dest-> RenderTarget에 있는 RGB 값
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;				// 위 두 값을 연산하는 방법

		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;			// PixelShader의 출력 Alpha값
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;			// RenderTarget에 있는 Alpha 값
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		hr = mcpDevice->CreateBlendState(&desc, mcpBlendState.ReleaseAndGetAddressOf());
		ifFailedHR(hr);
	}
	void GraphicDeviceDX11::createConstantBufferForTransform()
	{
		D3D11_BUFFER_DESC BufferDesc;
		ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
		BufferDesc.ByteWidth = sizeof(MatrixBuffer);
		BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		BufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		BufferDesc.MiscFlags = 0;
		BufferDesc.StructureByteStride = 0;

		HRESULT hr = mcpDevice->CreateBuffer(
			&BufferDesc,
			nullptr,
			mcpConstantBuffer.ReleaseAndGetAddressOf()
		);

		ifFailedHR(hr);
		mcpDeviceContext->VSSetConstantBuffers(
			0,
			1,
			mcpConstantBuffer.GetAddressOf()
		);
		mX = 0.0f;
		mY = 0.0f;
		mZ = 0.0f;
	}
	void GraphicDeviceDX11::initializeInputLayoutAndSetIA()
	{
		/*
			이제 InputAssembler에 값을 넘겨주기 위해서, 입력값이 어떤 식으로 구성되어 있는지를 알려주어야 함.
			이를 입력 레이아웃이라고 부름.
			이런 입력 레이아웃을 이용해서, 셰이더 코드에서 각각의 입력이 어떤 형태로 구성되어 있는지 판단함.
		*/
		const UINT INPUT_ELEMENT_COUNT = 2;
		D3D11_INPUT_ELEMENT_DESC inputElementDesc[INPUT_ELEMENT_COUNT] =
		{
			{
				"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
				D3D11_INPUT_PER_VERTEX_DATA, 0
			},
			{
				"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3,
				D3D11_INPUT_PER_VERTEX_DATA, 0
			}
		};

		HRESULT hr = mcpDevice->CreateInputLayout(
			inputElementDesc,
			2,
			mcpVSBlob->GetBufferPointer(),
			mcpVSBlob->GetBufferSize(),
			mcpInputLayout.ReleaseAndGetAddressOf()
		);
		ifFailedHR(hr);

		mcpDeviceContext->IASetInputLayout(mcpInputLayout.Get());
	}
	void GraphicDeviceDX11::loadTexture()
	{
		mspTexture->Load(L"T_Splash_Logo_HumbleGames.png");
	}
}
