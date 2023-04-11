#include "jhResourceMaker.h"
#include "jhResourcesManager.h"
#include "jhMesh.h"
#include "jhShader.h"
#include "jhTexture.h"
#include "jhMaterial.h"
#include "jhMath.h"

using namespace jh::math;

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
	const std::wstring ResourceMaker::BATTLE_PARRARELL_BG_TEXTURE_KEY = L"BattleParrarellBGTextureKey";


	const std::wstring ResourceMaker::WEAPON_SWORD_TEXTURE_KEY = L"WeaponSwordTextureKey";
	const std::wstring ResourceMaker::EFFECT_SWORD_TEXTURE_KEY = L"EffectSwordTextureKey";


#pragma endregion

#pragma region MATERIAL
	const std::wstring ResourceMaker::PLAYER_MATERIAL_KEY = L"PlayerMaterialKey";
	const std::wstring ResourceMaker::MONSTER_MATERIAL_KEY = L"MonsterMaterialKey";
	const std::wstring ResourceMaker::BATTLE_BG_MATERIAL_KEY = L"BattleBGMaterialKey";
	const std::wstring ResourceMaker::BATTLE_PARRARELL_BG_MATERIAL_KEY = L"BattleParralrellBGMaterialKey";
	const std::wstring ResourceMaker::WEAPON_SWORD_MATERIAL_KEY = L"WeaponSwordMaterialKey";


	const std::wstring ResourceMaker::EFFECT_SWORD_MATERIAL_KEY = L"EffectSwordMaterialKey";


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
#pragma region SPRITE_RECT_MESH
		Mesh* pRectMesh = new Mesh();
		mVertices[0] = { {-0.5f,		0.5f,		0.0f},	{0.0f, 0.0f} };
		mVertices[1] = { {0.5f,			0.5f,		0.0f},	{1.0f, 0.0f} };
		mVertices[2] = { {-0.5f,		-0.5f,		0.0f},	{0.0f, 1.0f} };
		mVertices[3] = { {0.5f,			-0.5f,		0.0f},	{1.0f, 1.0f} };
		pRectMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * RECT_VERTEX_COUNT);
		ResourcesManager::Insert<Mesh>(RECT_MESH_KEY, pRectMesh);

#pragma endregion

#pragma region BATTLE_BG_MESH
		const UINT MAGNIFICATION_VALUE = 8;
		Mesh* pBattleBGMesh = new Mesh();
		const float LEFT_U = 0.15f;
		const float RIGHT_U = 0.95f;
		const float HIGH_V = 0.15f;
		const float LOW_V = 0.95f;
		const Vector2 UV_LEFT_TOP(LEFT_U, HIGH_V);
		const Vector2 UV_RIGHT_TOP(RIGHT_U, HIGH_V);
		const Vector2 UV_LEFT_BOTTOM(LEFT_U, LOW_V);
		const Vector2 UV_RIGHT_BOTTOM(RIGHT_U, LOW_V);
		mVertices[0] = { {-0.5f,	0.5f,	0.0f},	UV_LEFT_TOP };
		mVertices[1] = { {0.5f,		0.5f,	0.0f},	UV_RIGHT_TOP };
		mVertices[2] = { {-0.5f,	-0.5f,	0.0f},	UV_LEFT_BOTTOM };
		mVertices[3] = { {0.5f,		-0.5f,	0.0f},	UV_RIGHT_BOTTOM };

		pBattleBGMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * RECT_VERTEX_COUNT);
		ResourcesManager::Insert<Mesh>(BATTLE_BG_MESH_KEY, pBattleBGMesh);
#pragma endregion
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
		pBattleBGTexture->Load(L"Cataclysm_Street_2.png");
		ResourcesManager::Insert<Texture>(BATTLE_BG_TEXTURE_KEY, pBattleBGTexture);

		Texture* pBattleParrarellBGTxtrue = new Texture();
		pBattleParrarellBGTxtrue->Load(L"SkyMerge.png");
		ResourcesManager::Insert<Texture>(BATTLE_PARRARELL_BG_TEXTURE_KEY, pBattleParrarellBGTxtrue);


		Texture* pWeaponSwordTxtrue = new Texture();
		pWeaponSwordTxtrue->Load(L"SwordSwingTopDown.png");
		ResourcesManager::Insert<Texture>(WEAPON_SWORD_TEXTURE_KEY, pWeaponSwordTxtrue);

		Texture* pEffectSwordTxtrue = new Texture();
		pEffectSwordTxtrue->Load(L"SIDEPUFF.png");
		ResourcesManager::Insert<Texture>(EFFECT_SWORD_TEXTURE_KEY, pEffectSwordTxtrue);
	}

	void ResourceMaker::createMaterial()
	{
		Material* pPlayerMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(PLAYER_TEXTURE_ATLAS_KEY));
		ResourcesManager::Insert<Material>(PLAYER_MATERIAL_KEY, pPlayerMaterial);
	
		Material* pMonsterMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_ATLAS_KEY));
		ResourcesManager::Insert<Material>(MONSTER_MATERIAL_KEY, pMonsterMaterial);

		Material* pBattleBGMaterial = new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY), ResourcesManager::Find<Texture>(BATTLE_BG_TEXTURE_KEY));
		ResourcesManager::Insert<Material>(BATTLE_BG_MATERIAL_KEY, pBattleBGMaterial);

		ResourcesManager::Insert<Material>(BATTLE_PARRARELL_BG_MATERIAL_KEY, 
			new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY), 
				ResourcesManager::Find<Texture>(BATTLE_PARRARELL_BG_TEXTURE_KEY))
		);

		ResourcesManager::Insert<Material>(WEAPON_SWORD_MATERIAL_KEY, 
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), 
				ResourcesManager::Find<Texture>(WEAPON_SWORD_TEXTURE_KEY))
		);

		ResourcesManager::Insert<Material>(EFFECT_SWORD_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(EFFECT_SWORD_TEXTURE_KEY))
		);
	}

	void ResourceMaker::createSamplerState()
	{
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = 0;
		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 1.0f;
		graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateSamplerState(
			&samplerDesc,
			mcpPointBorderSampler.ReleaseAndGetAddressOf()
		);

		//samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		//samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		//samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		//graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateSamplerState(
		//	&samplerDesc,
		//	mcpPointWrapSampler.ReleaseAndGetAddressOf()
		//);
	}

	void ResourceMaker::setSamplerState()
	{
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetSamplers(POINT_BORDER_SAMPLER_SLOT_NUMBER, 1, mcpPointBorderSampler.GetAddressOf());
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetSamplers(POINT_BORDER_SAMPLER_SLOT_NUMBER, 1, mcpPointBorderSampler.GetAddressOf());
	
		//graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetSamplers(POINT_WRAP_SAMPLER_SLOT_NUMBER, 1, mcpPointWrapSampler.GetAddressOf());
		//graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetSamplers(POINT_WRAP_SAMPLER_SLOT_NUMBER, 1, mcpPointWrapSampler.GetAddressOf());

	
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
		mcpPointBorderSampler.Reset();
		//mcpPointWrapSampler.Reset();
	}

}

