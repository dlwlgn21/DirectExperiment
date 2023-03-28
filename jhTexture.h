#pragma once
#include "jhD3DApp.h"
#include <DirectXTex.h>

namespace jh
{
	class Texture final
	{
	public:
		Texture();
		~Texture();

		HRESULT Load(const std::wstring& filePath);
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() const { return mcpSRV; }

	private:
		void createSRVFromLoadedFile();
	private:
		DirectX::ScratchImage								mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>				mcpTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mcpSRV;
		D3D11_TEXTURE2D_DESC								mTextureDesc;
	};
}

