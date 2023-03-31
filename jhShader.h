#pragma once
#include "jhGraphics.h"

namespace jh
{
	class Shader final
	{
	public:
		Shader();
		~Shader();

		void SetPipeline();

	private:
		void createResource();
		void createShaders();
		void setShaders();

		void createInputLayout();
		void setInputLayout();

		void createVS(ID3D11Device* pDevice);
		void createPS(ID3D11Device* pDevice);

		void createBlendState();
		void setBlendState();

	private:
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

