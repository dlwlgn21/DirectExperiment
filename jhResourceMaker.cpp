#include "jhResourceMaker.h"
#include "jhResourcesManager.h"
#include "jhMesh.h"
#include "jhShader.h"
#include "jhTexture.h"
#include "jhMaterial.h"


namespace jh
{
	const std::wstring ResourceMaker::RECT_MESH_KEY = L"RectMeshKey";
	const std::wstring ResourceMaker::SPRITE_SHADER_KEY = L"SpriteShaderKey";
	const std::wstring ResourceMaker::LOGO_TEXTURE_KEY = L"LogoTextureKey";
	const std::wstring ResourceMaker::LOGO_MATERIAL_KEY = L"LogoMaterialKey";


	void ResourceMaker::Initialize()
	{
		createMeshs();
		createShaders();
		createTextures();
		createMaterial();
		createSamplerState();
	}

	void ResourceMaker::createMeshs()
	{
		Mesh* pRectMesh = new Mesh();
		mVertices[0] = { {-0.1f,		0.1f,		0.0f},	{0.0f, 0.0f} };
		mVertices[1] = { {0.1f,			0.1f,		0.0f},	{1.0f, 0.0f} };
		mVertices[2] = { {-0.1f,		-0.1f,		0.0f},	{0.0f, 1.0f} };
		mVertices[3] = { {0.1f,			-0.1f,		0.0f},	{1.0f, 1.0f} };
		pRectMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * RECT_VERTEX_COUNT);
		ResourcesManager::Insert<Mesh>(RECT_MESH_KEY, pRectMesh);

	}

	void ResourceMaker::createShaders()
	{
		Shader* pSriteShader = new Shader();
		pSriteShader->CreateShaders(L"jhVertexShader.hlsl", L"jhPixelShader.hlsl");
		ResourcesManager::Insert<Shader>(SPRITE_SHADER_KEY, pSriteShader);

	}

	void ResourceMaker::createTextures()
	{
		Texture* pLogoTexture = new Texture();
		pLogoTexture->Load(L"T_Splash_Logo_HumbleGames.png");
		ResourcesManager::Insert<Texture>(LOGO_TEXTURE_KEY, pLogoTexture);
	}

	void ResourceMaker::createMaterial()
	{
		Material* pLogoMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(LOGO_TEXTURE_KEY));
		ResourcesManager::Insert<Material>(LOGO_MATERIAL_KEY, pLogoMaterial);
	
	}

	void ResourceMaker::createSamplerState()
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
		graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateSamplerState(
			&samplerDesc,
			mcpPointSampler.ReleaseAndGetAddressOf()
		);

		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetSamplers(POINT_SAMPLER_SLOT_NUMBER, 1, mcpPointSampler.GetAddressOf());
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetSamplers(POINT_SAMPLER_SLOT_NUMBER, 1, mcpPointSampler.GetAddressOf());
	}
	

	void ResourceMaker::Release()
	{
		mcpPointSampler.Reset();
	}

}

