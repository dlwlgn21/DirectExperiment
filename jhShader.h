#pragma once
#include "jhResource.h"

namespace jh
{
	class Shader : public Resource
	{
	public:
		Shader();
		virtual ~Shader();

		void SetPipeline();
		virtual void CreateShaders(const std::wstring& VSFileName, const std::wstring& PSFileName);
		void SetPrimitiveTopology(const D3D11_PRIMITIVE_TOPOLOGY topology) { mPrimitiveTopology = topology; }

	protected:
		void createResource();
		void createShaders(const std::wstring& VSFileName, const std::wstring& PSFileName);
		void setShaders();

		void createInputLayout();
		void setInputLayout();

		void createVS(ID3D11Device* pDevice, const std::wstring& VSFileName);
		void createPS(ID3D11Device* pDevice, const std::wstring& PSFileName);

		void createBlendState();
		void setBlendState();

	protected:
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpPSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				mcpErrorBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		mcpVS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		mcpPS;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>		mcpInputLayout;
		Microsoft::WRL::ComPtr<ID3D11BlendState>		mcpBlendState;
		D3D11_PRIMITIVE_TOPOLOGY						mPrimitiveTopology;
	};
}

