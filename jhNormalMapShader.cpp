#include "jhNormalMapShader.h"
#include "jhGraphicDeviceDX11.h"

namespace jh
{
	NormalMapShader::NormalMapShader()
		: Shader()
	{
	}
	void NormalMapShader::CreateShaders(const std::wstring& VSFileName, const std::wstring& PSFileName)
	{
		Shader::createShaders(VSFileName, PSFileName);
		createIA();
		Shader::createBlendState();
	}
	void NormalMapShader::createIA()
	{
		auto* pGraphicDevice = graphics::GraphicDeviceDX11::GetInstance().GetDeivce();
		const UINT INPUT_ELEMENT_COUNT = 4;
		D3D11_INPUT_ELEMENT_DESC inputElementDesc[INPUT_ELEMENT_COUNT] =
		{
			{ "POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,    0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "TANGENT",  0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,    0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		HRESULT hr = pGraphicDevice->CreateInputLayout(
			inputElementDesc,
			INPUT_ELEMENT_COUNT,
			mcpVSBlob->GetBufferPointer(),
			mcpVSBlob->GetBufferSize(),
			mcpInputLayout.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr)) { assert(false); return; }
	}
}