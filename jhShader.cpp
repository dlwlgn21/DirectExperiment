#include "jhShader.h"
#include "jhGraphicDeviceDX11.h"

namespace jh
{
	Shader::Shader()
		: Resource(eReousrceType::SHADER)
		, mcpErrorBlob()
		, mcpVSBlob()
		, mcpPSBlob()
		, mcpVS()
		, mcpPS()
		, mcpInputLayout()
		, mcpBlendState()
		, mPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP)
	{
	}

	Shader::~Shader()
	{
		mcpVSBlob.Reset();
		mcpPSBlob.Reset();
		mcpErrorBlob.Reset();
		mcpVS.Reset();
		mcpPS.Reset();
		mcpInputLayout.Reset();
		mcpBlendState.Reset();
	}

	void Shader::createShaders(const std::wstring& VSFileName, const std::wstring& PSFileName)
	{
		auto* pGraphicDevice = graphics::GraphicDeviceDX11::GetInstance().GetDeivce();
		createVS(pGraphicDevice, VSFileName);
		createPS(pGraphicDevice, PSFileName);
	}
	void Shader::setShaders()
	{
		assert(mcpVS != nullptr && mcpPS != nullptr);
		auto* pGraphicDeviceContext = graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext();
		pGraphicDeviceContext->VSSetShader(
			mcpVS.Get(),
			nullptr,
			0
		);
		pGraphicDeviceContext->PSSetShader(
			mcpPS.Get(),
			nullptr,
			0
		);
	}

	void Shader::createInputLayout()
	{
		auto* pGraphicDevice = graphics::GraphicDeviceDX11::GetInstance().GetDeivce();
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

		HRESULT hr = pGraphicDevice->CreateInputLayout(
			inputElementDesc,
			2,
			mcpVSBlob->GetBufferPointer(),
			mcpVSBlob->GetBufferSize(),
			mcpInputLayout.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr)) { assert(false); return; }

	}
	void Shader::setInputLayout()
	{
		assert(mcpInputLayout != nullptr);
		auto* pGraphicDeviceContext = graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext();
		pGraphicDeviceContext->IASetInputLayout(mcpInputLayout.Get());
	}

	void Shader::createResource()
	{
		createInputLayout();
		createBlendState();
	}

	void Shader::SetPipeline()
	{
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->IASetPrimitiveTopology(mPrimitiveTopology);
		setInputLayout();
		setShaders();
		setBlendState();
	}

	void Shader::CreateShaders(const std::wstring& VSFileName, const std::wstring& PSFileName)
	{
		createShaders(VSFileName, PSFileName);
		createResource();
	}


	void Shader::createVS(ID3D11Device* pDevice, const std::wstring& VSFileName)
	{
		HRESULT hr;
		hr = D3DCompileFromFile(
			VSFileName.c_str(),
			0,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main",
			"vs_5_0",
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

		hr = pDevice->CreateVertexShader(
			mcpVSBlob->GetBufferPointer(),
			mcpVSBlob->GetBufferSize(),
			nullptr,
			mcpVS.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr)) { assert(false); }
	}
	void Shader::createPS(ID3D11Device* pDevice, const std::wstring& PSFileName)
	{
		HRESULT hr;
		hr = D3DCompileFromFile(
			PSFileName.c_str(),
			0,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main",
			"ps_5_0",
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

		hr = pDevice->CreatePixelShader(
			mcpPSBlob->GetBufferPointer(),
			mcpPSBlob->GetBufferSize(),
			nullptr,
			mcpPS.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr)) { assert(false); }
	}
	void Shader::createBlendState()
	{
		auto* pGraphicDevice = graphics::GraphicDeviceDX11::GetInstance().GetDeivce();
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

		hr = pGraphicDevice->CreateBlendState(&desc, mcpBlendState.ReleaseAndGetAddressOf());
		if (FAILED(hr)) { assert(false); }
	}

	void Shader::setBlendState()
	{
		assert(mcpBlendState != nullptr);
		auto* pGraphicDeviceContext = graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext();
		pGraphicDeviceContext->OMSetBlendState(mcpBlendState.Get(),	nullptr, 0xffffffff);
	}
}