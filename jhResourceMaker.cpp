#include "jhResourceMaker.h"
#include "jhResourcesManager.h"
#include "jhMesh.h"
#include "jhShader.h"
#include "jhTexture.h"
#include "jhMaterial.h"

namespace jh
{
#pragma region MESH
	const std::wstring ResourceMaker::RECT_MESH_KEY = L"RectMeshKey";
	const std::wstring ResourceMaker::BATTLE_BG_MESH_KEY = L"BattleBGMeshKey";



#pragma endregion

#pragma region SHADER
	const std::wstring ResourceMaker::SPRITE_SHADER_KEY = L"SpriteShaderKey";
	const std::wstring ResourceMaker::BATTLE_BG_SHADER_KEY = L"BattleBGShaderKey";



#pragma endregion

#pragma region TEXTURE
	const std::wstring ResourceMaker::PLAYER_TEXTURE_ATLAS_KEY = L"PlayerTextureAtlasKey";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_ATLAS_KEY = L"MonsterTextureAtalsKey";
	const std::wstring ResourceMaker::BATTLE_BG_TEXTURE_KEY = L"BattleBGTextureKey";

#pragma endregion

#pragma region MATERIAL
	const std::wstring ResourceMaker::PLAYER_MATERIAL_KEY = L"PlayerMaterialKey";
	const std::wstring ResourceMaker::MONSTER_MATERIAL_KEY = L"MonsterMaterialKey";
	const std::wstring ResourceMaker::BATTLE_BG_MATERIAL_KEY = L"BattleBGMaterialKey";



#pragma endregion

	void ResourceMaker::Initialize()
	{
		createMeshs();
		createShaders();
		createTextures();
		createMaterial();
		createSamplerState();
		setSamplerState();
		createConstantBuffer();
	}

	void ResourceMaker::createMeshs()
	{
		Mesh* pRectMesh = new Mesh();
		mVertices[0] = { {-0.5f,		0.5f,		0.0f},	{0.0f, 0.0f} };
		mVertices[1] = { {0.5f,			0.5f,		0.0f},	{1.0f, 0.0f} };
		mVertices[2] = { {-0.5f,		-0.5f,		0.0f},	{0.0f, 1.0f} };
		mVertices[3] = { {0.5f,			-0.5f,		0.0f},	{1.0f, 1.0f} };
		pRectMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * RECT_VERTEX_COUNT);
		ResourcesManager::Insert<Mesh>(RECT_MESH_KEY, pRectMesh);

		Mesh* pBattleBGMesh = new Mesh();
		mVertices[0].UV = {0.25f, 0.25f};
		mVertices[1].UV = {0.75f, 0.25f};
		mVertices[2].UV = {0.25f, 0.75f};
		mVertices[3].UV = {0.75f, 0.75f};
		pBattleBGMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * RECT_VERTEX_COUNT);
		ResourcesManager::Insert<Mesh>(BATTLE_BG_MESH_KEY, pBattleBGMesh);
	}

	void ResourceMaker::createShaders()
	{
		Shader* pSriteShader = new Shader();
		pSriteShader->CreateShaders(L"jhSpriteVS.hlsl", L"jhSpritePS.hlsl");
		ResourcesManager::Insert<Shader>(SPRITE_SHADER_KEY, pSriteShader);

		Shader* pBattleBGShader = new Shader();
		pBattleBGShader->CreateShaders(L"jhBackGroundVS.hlsl", L"jhBackGroundPS.hlsl");
		ResourcesManager::Insert<Shader>(BATTLE_BG_SHADER_KEY, pBattleBGShader);

	}

	void ResourceMaker::createTextures()
	{
		Texture* pPlayerAtalsTexture = new Texture();
		pPlayerAtalsTexture->Load(L"CharacterAtlas.png");
		ResourcesManager::Insert<Texture>(PLAYER_TEXTURE_ATLAS_KEY, pPlayerAtalsTexture);


		Texture* pZombieAtlasTexture = new Texture();
		pZombieAtlasTexture->Load(L"WildZombie.png");
		ResourcesManager::Insert<Texture>(MONSTER_TEXTURE_ATLAS_KEY, pZombieAtlasTexture);

		Texture* pBattleBGTexture = new Texture();
		pBattleBGTexture->Load(L"Merge.png");
		ResourcesManager::Insert<Texture>(BATTLE_BG_TEXTURE_KEY, pBattleBGTexture);
	}

	void ResourceMaker::createMaterial()
	{
		Material* pPlayerMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(PLAYER_TEXTURE_ATLAS_KEY));
		ResourcesManager::Insert<Material>(PLAYER_MATERIAL_KEY, pPlayerMaterial);
	
		Material* pMonsterMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_ATLAS_KEY));
		ResourcesManager::Insert<Material>(MONSTER_MATERIAL_KEY, pMonsterMaterial);

		Material* pBattleBGMaterial = new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY), ResourcesManager::Find<Texture>(BATTLE_BG_TEXTURE_KEY));
		ResourcesManager::Insert<Material>(BATTLE_BG_MATERIAL_KEY, pBattleBGMaterial);
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
	}

	void ResourceMaker::setSamplerState()
	{
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetSamplers(POINT_SAMPLER_SLOT_NUMBER, 1, mcpPointSampler.GetAddressOf());
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetSamplers(POINT_SAMPLER_SLOT_NUMBER, 1, mcpPointSampler.GetAddressOf());
	}

	void ResourceMaker::createConstantBuffer()
	{
		mspTransformConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::TRANSFORM);
		mspAnimationConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::ANIMATION);
		mspUVTranslationConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::UV_TRANSLATION);
	}


	void ResourceMaker::Release()
	{
		mspUVTranslationConstantBuffer.reset();
		mspAnimationConstantBuffer.reset();
		mspTransformConstantBuffer.reset();
		mcpPointSampler.Reset();
	}

}
