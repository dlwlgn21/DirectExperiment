#include "jhTexture.h"


namespace jh
{
	Texture::Texture()
		: mcpTexture(nullptr)
		, mcpSRV(nullptr)
		, mTextureDesc{}
	{
	}
	Texture::~Texture()
	{
		mcpSRV.Reset();
		mcpTexture.Reset();
	}


	HRESULT Texture::Load(const std::wstring& filePath)
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += L"\\Resources\\" + filePath;

		const UINT MAX_LENGTH = 256;
		wchar_t szExtension[MAX_LENGTH] = {};
		if (_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, MAX_LENGTH) != 0)
		{
			// FAILED _wsplitpath_s
			assert(false);
		}

		std::wstring extension(szExtension);

		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(DirectX::LoadFromDDSFile(path.c_str(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		createSRVFromLoadedFile();

		return S_OK;
	}
	void Texture::createSRVFromLoadedFile()
	{
		HRESULT hr = DirectX::CreateShaderResourceView(
			D3DApp::GetInstance().GetDevice(),
			mImage.GetImages(),
			mImage.GetImageCount(),
			mImage.GetMetadata(),
			mcpSRV.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr))
		{
			assert(false);
			return;
		}
		mcpSRV->GetResource(reinterpret_cast<ID3D11Resource**>(mcpTexture.GetAddressOf()));
	}
}