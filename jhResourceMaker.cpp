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
	const std::wstring ResourceMaker::DEBUG_RECT_MESH_KEY = L"DebugRectMeshKey";



#pragma endregion

#pragma region SHADER
	const std::wstring ResourceMaker::SPRITE_SHADER_KEY = L"SpriteShaderKey";
	const std::wstring ResourceMaker::BATTLE_BG_SHADER_KEY = L"BattleBGShaderKey";
	const std::wstring ResourceMaker::DEBUG_SHADER_KEY = L"DebugShaderKey";
	const std::wstring ResourceMaker::UI_HP_SHADER_KEY = L"UIHPShaderKey";
	const std::wstring ResourceMaker::UI_STAMINA_SHADER_KEY = L"UIStaminaShaderKey";


#pragma endregion

#pragma region TEXTURE
	const std::wstring ResourceMaker::PLAYER_TEXTURE_ATLAS_KEY = L"PlayerTextureAtlasKey";


	const std::wstring ResourceMaker::MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY = L"CagedTextureAtalsKey";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_SWEEPER_ATLAS_KEY = L"SweeperTextureAtalsKey";


	const std::wstring ResourceMaker::BATTLE_BG_TEXTURE_KEY = L"BattleBGTextureKey";
	const std::wstring ResourceMaker::BATTLE_PARRARELL_BG_TEXTURE_KEY = L"BattleParrarellBGTextureKey";

	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_1_KEY = L"Parallax1TextureKey";
	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_2_KEY = L"Parallax2TextureKey";
	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_3_KEY = L"Parallax3TextureKey";
	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_4_KEY = L"Parallax4TextureKey";
	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_5_KEY = L"Parallax5TextureKey";
	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_6_KEY = L"Parallax6TextureKey";


	const std::wstring ResourceMaker::WEAPON_SWORD_TEXTURE_KEY = L"WeaponSwordTextureKey";
	const std::wstring ResourceMaker::EFFECT_BLOOD_TEXTURE_KEY = L"EffectBloodTextureKey";

	const std::wstring ResourceMaker::UI_HP_BORDER_TEXTURE_KEY = L"UIHpBorderKey";
	const std::wstring ResourceMaker::UI_HP_BAR_TEXTURE_KEY = L"UIHpBarKey";
	const std::wstring ResourceMaker::UI_STAMINA_BAR_TEXTURE_KEY = L"UIStaminaBarKey";

	const std::wstring ResourceMaker::BG_MOON_ATLAS_TEXTURE_KEY = L"BGMoonTextureKey";

	const std::wstring ResourceMaker::PLAYER_DASH_EFFECT_TEXTURE_KEY = L"PlayerDashEffectTextureKey";

#pragma endregion

#pragma region MATERIAL
	const std::wstring ResourceMaker::PLAYER_MATERIAL_KEY = L"PlayerMaterialKey";

	const std::wstring ResourceMaker::MONSTER_CAGED_SHOKER_MATERIAL_KEY = L"CagedShokerMaterialKey";
	const std::wstring ResourceMaker::MONSTER_SWEEPER_MATERIAL_KEY = L"SweeperMaterialKey";

	const std::wstring ResourceMaker::BATTLE_BG_MATERIAL_KEY = L"BattleBGMaterialKey";
	const std::wstring ResourceMaker::BATTLE_PARRARELL_BG_MATERIAL_KEY = L"BattleParralrellBGMaterialKey";
	const std::wstring ResourceMaker::WEAPON_SWORD_MATERIAL_KEY = L"WeaponSwordMaterialKey";


	const std::wstring ResourceMaker::EFFECT_BLOOD_MATERIAL_KEY = L"EffectBloodMaterialKey";


	const std::wstring ResourceMaker::DEBUG_MATERIAL_KEY = L"DebugMaterialKey";

	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_1_KEY = L"ParallaxMaterial1Key";
	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_2_KEY = L"ParallaxMaterial2Key";
	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_3_KEY = L"ParallaxMaterial3Key";
	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_4_KEY = L"ParallaxMaterial4Key";
	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_5_KEY = L"ParallaxMaterial5Key";
	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_6_KEY = L"ParallaxMaterial6Key";
	const std::wstring ResourceMaker::BG_MOON_MATERIAL_KEY = L"BGMoonMaterialKey";


	const std::wstring ResourceMaker::UI_HP_BORDER_MATERIAL_KEY = L"UIHPBorderMaterialKey";
	const std::wstring ResourceMaker::UI_HP_BAR_MATERIAL_KEY = L"UIHpBarMaterialKey";
	const std::wstring ResourceMaker::UI_STAMINA_BAR_MATERIAL_KEY = L"UIStaminarBarMaterialKey";

	const std::wstring ResourceMaker::PLAYER_DASH_EFFECT_MATERIAL_KEY = L"PlayerDashEffectMaterialKey";

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
		std::vector<UINT> rectIndexes;
		rectIndexes.reserve(32);
		rectIndexes.push_back(0);
		rectIndexes.push_back(1);
		rectIndexes.push_back(2);
		rectIndexes.push_back(0);
		rectIndexes.push_back(2);
		rectIndexes.push_back(3);
		rectIndexes.push_back(0);

#pragma region SPRITE_RECT_MESH
		Mesh* pRectMesh = new Mesh();
		mVertices[0] = { {-0.5f,		0.5f,		0.0f},	{0.0f, 0.0f} };
		mVertices[1] = { {0.5f,			0.5f,		0.0f},	{1.0f, 0.0f} };
		mVertices[2] = { {0.5f,			-0.5f,		0.0f},	{1.0f, 1.0f} };
		mVertices[3] = { {-0.5f,		-0.5f,		0.0f},	{0.0f, 1.0f} };
		pRectMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * RECT_VERTEX_COUNT);



		pRectMesh->CreateIndexBuffer(rectIndexes.data(), static_cast<UINT>(rectIndexes.size()));
		ResourcesManager::Insert<Mesh>(RECT_MESH_KEY, pRectMesh);

#pragma endregion

#pragma region BATTLE_BG_MESH
		const UINT MAGNIFICATION_VALUE = 8;
		Mesh* pBattleBGMesh = new Mesh();
		pBattleBGMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * RECT_VERTEX_COUNT);
		pBattleBGMesh->CreateIndexBuffer(rectIndexes.data(), static_cast<UINT>(rectIndexes.size()));
		ResourcesManager::Insert<Mesh>(BATTLE_BG_MESH_KEY, pBattleBGMesh);
#pragma endregion

#pragma region DEBUG_MESH
		mVertices[0] = { {-0.5f,		0.5f,		-0.1f},	{0.0f, 0.0f} };
		mVertices[1] = { {0.5f,			0.5f,		-0.1f},	{1.0f, 0.0f} };
		mVertices[2] = { {0.5f,			-0.5f,		-0.1f},	{1.0f, 1.0f} };
		mVertices[3] = { {-0.5f,		-0.5f,		-0.1f},	{0.0f, 1.0f} };

		Mesh* pDebugRectMesh = new Mesh();
		pDebugRectMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * RECT_VERTEX_COUNT);
		pDebugRectMesh->CreateIndexBuffer(rectIndexes.data(), static_cast<UINT>(rectIndexes.size()));

		ResourcesManager::Insert<Mesh>(DEBUG_RECT_MESH_KEY, pDebugRectMesh);
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

		Shader* pDebugShader = new Shader();
		pDebugShader->CreateShaders(L"DebugVS.hlsl", L"DebugPS.hlsl");
		pDebugShader->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		ResourcesManager::Insert<Shader>(DEBUG_SHADER_KEY, pDebugShader);


		Shader* pUIHPShader = new Shader();
		pUIHPShader->CreateShaders(L"jhUserInterfaceVS.hlsl", L"jhUserInterfaceHealthPS.hlsl");
		ResourcesManager::Insert<Shader>(UI_HP_SHADER_KEY, pUIHPShader);

		Shader* pUIStaminaShader = new Shader();
		pUIStaminaShader->CreateShaders(L"jhUserInterfaceVS.hlsl", L"jhUserIntefaceStaminaPS.hlsl");
		ResourcesManager::Insert<Shader>(UI_STAMINA_SHADER_KEY, pUIStaminaShader);
	}

	void ResourceMaker::createTextures()
	{
		Texture* pPlayerAtalsTexture = new Texture();
		pPlayerAtalsTexture->Load(L"Sword Master Sprite Sheet 90x37(2).png");
		ResourcesManager::Insert<Texture>(PLAYER_TEXTURE_ATLAS_KEY, pPlayerAtalsTexture);

		Texture* pCagedShokerAtlasTexture = new Texture();
		pCagedShokerAtlasTexture->Load(L"caged shocker 110x42.png");
		ResourcesManager::Insert<Texture>(MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY, pCagedShokerAtlasTexture);

		Texture* pSweeperAtlasTexture = new Texture();
		pSweeperAtlasTexture->Load(L"Sweeper.png");
		ResourcesManager::Insert<Texture>(MONSTER_TEXTURE_SWEEPER_ATLAS_KEY, pSweeperAtlasTexture);


		Texture* pBattleBGTexture = new Texture();
		pBattleBGTexture->Load(L"ForeGround23(1).png");
		ResourcesManager::Insert<Texture>(BATTLE_BG_TEXTURE_KEY, pBattleBGTexture);

		Texture* pBattleParrarellBGTxtrue = new Texture();
		pBattleParrarellBGTxtrue->Load(L"SkyMerge.png");
		ResourcesManager::Insert<Texture>(BATTLE_PARRARELL_BG_TEXTURE_KEY, pBattleParrarellBGTxtrue);


		Texture* pWeaponSwordTxtrue = new Texture();
		pWeaponSwordTxtrue->Load(L"SwordSwingTopDown.png");
		ResourcesManager::Insert<Texture>(WEAPON_SWORD_TEXTURE_KEY, pWeaponSwordTxtrue);

		Texture* pEffectSwordTxtrue = new Texture();
		pEffectSwordTxtrue->Load(L"BloodEffect.png");
		ResourcesManager::Insert<Texture>(EFFECT_BLOOD_TEXTURE_KEY, pEffectSwordTxtrue);

		Texture* pParralaxTxtrue = new Texture();
		pParralaxTxtrue->Load(L"parallax1.png");
		ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_1_KEY, pParralaxTxtrue);

		pParralaxTxtrue = new Texture();
		pParralaxTxtrue->Load(L"parallax2.png");
		ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_2_KEY, pParralaxTxtrue);

		pParralaxTxtrue = new Texture();
		pParralaxTxtrue->Load(L"parallax3.png");
		ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_3_KEY, pParralaxTxtrue);

		pParralaxTxtrue = new Texture();
		pParralaxTxtrue->Load(L"parallax4.png");
		ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_4_KEY, pParralaxTxtrue);

		pParralaxTxtrue = new Texture();
		pParralaxTxtrue->Load(L"parallax5.png");
		ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_5_KEY, pParralaxTxtrue);

		pParralaxTxtrue = new Texture();
		pParralaxTxtrue->Load(L"parallax6.png");
		ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_6_KEY, pParralaxTxtrue);

		Texture* pBGMoonTexture = new Texture();
		pBGMoonTexture->Load(L"MoonSprite.png");
		ResourcesManager::Insert<Texture>(BG_MOON_ATLAS_TEXTURE_KEY, pBGMoonTexture);


		Texture* pUITextrue = new Texture();
		pUITextrue->Load(L"HpBarBorder.png");
		ResourcesManager::Insert<Texture>(UI_HP_BORDER_TEXTURE_KEY, pUITextrue);

		Texture* pUIHPBarTextrue = new Texture();
		pUIHPBarTextrue->Load(L"HPBar.png");
		ResourcesManager::Insert<Texture>(UI_HP_BAR_TEXTURE_KEY, pUIHPBarTextrue);


		Texture* pStaminaBarTextrue = new Texture();
		pStaminaBarTextrue->Load(L"StaminarBar.png");
		ResourcesManager::Insert<Texture>(UI_STAMINA_BAR_TEXTURE_KEY, pStaminaBarTextrue);

		Texture* pPlayerDashDustEffectTexture = new Texture();
		pPlayerDashDustEffectTexture->Load(L"DASHSMOKE2.png");
		ResourcesManager::Insert<Texture>(PLAYER_DASH_EFFECT_TEXTURE_KEY, pPlayerDashDustEffectTexture);
	}

	void ResourceMaker::createMaterial()
	{
		Material* pPlayerMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(PLAYER_TEXTURE_ATLAS_KEY));
		ResourcesManager::Insert<Material>(PLAYER_MATERIAL_KEY, pPlayerMaterial);

		Material* pCagedMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY));
		ResourcesManager::Insert<Material>(MONSTER_CAGED_SHOKER_MATERIAL_KEY, pCagedMaterial);

		Material* pSweeperMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_SWEEPER_ATLAS_KEY));
		ResourcesManager::Insert<Material>(MONSTER_SWEEPER_MATERIAL_KEY, pSweeperMaterial);


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

		ResourcesManager::Insert<Material>(EFFECT_BLOOD_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(EFFECT_BLOOD_TEXTURE_KEY))
			);

		ResourcesManager::Insert<Material>(PARALLAX_BG_MATERIAL_1_KEY,
			new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY),
				ResourcesManager::Find<Texture>(PARALLAX_BG_TEXTURE_1_KEY))
			);

		ResourcesManager::Insert<Material>(PARALLAX_BG_MATERIAL_2_KEY,
			new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY),
				ResourcesManager::Find<Texture>(PARALLAX_BG_TEXTURE_2_KEY))
			);
		ResourcesManager::Insert<Material>(PARALLAX_BG_MATERIAL_3_KEY,
			new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY),
				ResourcesManager::Find<Texture>(PARALLAX_BG_TEXTURE_3_KEY))
			);
		ResourcesManager::Insert<Material>(PARALLAX_BG_MATERIAL_4_KEY,
			new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY),
				ResourcesManager::Find<Texture>(PARALLAX_BG_TEXTURE_4_KEY))
			);
		ResourcesManager::Insert<Material>(PARALLAX_BG_MATERIAL_5_KEY,
			new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY),
				ResourcesManager::Find<Texture>(PARALLAX_BG_TEXTURE_5_KEY))
			);
		ResourcesManager::Insert<Material>(PARALLAX_BG_MATERIAL_6_KEY,
			new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY),
				ResourcesManager::Find<Texture>(PARALLAX_BG_TEXTURE_6_KEY))
			);

		ResourcesManager::Insert<Material>(UI_HP_BORDER_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY),
				ResourcesManager::Find<Texture>(UI_HP_BORDER_TEXTURE_KEY))
			);

		ResourcesManager::Insert<Material>(UI_HP_BAR_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(UI_HP_SHADER_KEY),
				ResourcesManager::Find<Texture>(UI_HP_BAR_TEXTURE_KEY))
			);

		ResourcesManager::Insert<Material>(UI_STAMINA_BAR_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(UI_STAMINA_SHADER_KEY),
				ResourcesManager::Find<Texture>(UI_STAMINA_BAR_TEXTURE_KEY))
			);

		ResourcesManager::Insert<Material>(BG_MOON_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(BG_MOON_ATLAS_TEXTURE_KEY))
			);


		ResourcesManager::Insert<Material>(PLAYER_DASH_EFFECT_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(PLAYER_DASH_EFFECT_TEXTURE_KEY))
			);

#pragma region DEBUG
		Material* pDebugMaterial = new Material(ResourcesManager::Find<Shader>(DEBUG_SHADER_KEY), nullptr);
		ResourcesManager::Insert<Material>(DEBUG_MATERIAL_KEY, pDebugMaterial);

#pragma endregion

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
		//mspColliderConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::COLLIDER_COLOR);
		mspUIBarConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::UI_BAR);
	}

	void ResourceMaker::Release()
	{
		//mspColliderConstantBuffer.reset();
		mspUVTranslationConstantBuffer.reset();
		mspAnimationConstantBuffer.reset();
		mspTransformConstantBuffer.reset();
		mspUIBarConstantBuffer.reset();
		mcpPointBorderSampler.Reset();
		//mcpPointWrapSampler.Reset();
	}

}