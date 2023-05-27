#include "jhResourceMaker.h"
#include "jhResourcesManager.h"
#include "jhMesh.h"
#include "jhShader.h"
#include "jhTexture.h"
#include "jhMaterial.h"
#include "jhMath.h"
#include "jhNormalMapMaterial.h"
#include "jhNormalMapShader.h"
#include "jhNormalMapMesh.h"

using namespace jh::math;

namespace jh
{
#pragma region MESH
	const std::wstring ResourceMaker::RECT_MESH_KEY = L"RectMeshKey";
	const std::wstring ResourceMaker::BATTLE_BG_MESH_KEY = L"BattleBGMeshKey";
	const std::wstring ResourceMaker::DEBUG_RECT_MESH_KEY = L"DebugRectMeshKey";

	// Added Part FOR NORMAL_MAP At 2023-05-23 16:40
	const std::wstring ResourceMaker::RECT_NORMAL_MAP_MESH_KEY = L"NormalMapMeshKey";
#pragma endregion

#pragma region SHADER
	const std::wstring ResourceMaker::SPRITE_SHADER_KEY = L"SpriteShaderKey";
	const std::wstring ResourceMaker::NORMAL_MAP_SPRITE_SHADER_KEY = L"NormalMapSpriteShaderKey";
	const std::wstring ResourceMaker::BATTLE_BG_SHADER_KEY = L"BattleBGShaderKey";
	const std::wstring ResourceMaker::DEBUG_SHADER_KEY = L"DebugShaderKey";
	const std::wstring ResourceMaker::UI_HP_SHADER_KEY = L"UIHPShaderKey";
	const std::wstring ResourceMaker::UI_STAMINA_SHADER_KEY = L"UIStaminaShaderKey";


#pragma endregion

#pragma region TEXTURE
	const std::wstring ResourceMaker::PLAYER_TEXTURE_ATLAS_KEY = L"PlayerTextureAtlasKey";
	const std::wstring ResourceMaker::PLAYER_NORMAL_MAP_TEXTURE_ATLAS_KEY = L"PlayerNormalMapTextureAtlasKey";


	const std::wstring ResourceMaker::MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY = L"CagedTextureAtalsKey";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_CAGED_SHOKER_NORMAL_MAP_KEY = L"CagedNormalTextureKey";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_SWEEPER_ATLAS_KEY = L"SweeperTextureAtalsKey";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_SWEEPER_NORMAL_MAP_KEY = L"SweeperNormalTextureKey";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_WARDEN_ATLAS_KEY = L"WardenTextureAtalsKey";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_WARDEN_NORMAL_MAP_KEY = L"WardenNormalTextureKey";
	const std::wstring ResourceMaker::OBELISK_TEXTURE_ATLAS_KEY = L"ObeliskTextureAtalsKey";
	const std::wstring ResourceMaker::OBELISK_TEXTURE_NORMAL_MAP_KEY = L"ObeliskNoramlTextureKey";


	const std::wstring ResourceMaker::BATTLE_FOREGROUND_TEXTURE_KEY = L"BattleBGTextureKey";
	const std::wstring ResourceMaker::BATTLE_FOREGROUND_NORMAL_MAP_TEXTURE_KEY = L"BattleForegroundNomal";
	const std::wstring ResourceMaker::BATTLE_PARRARELL_BG_TEXTURE_KEY = L"BattleParrarellBGTextureKey";

	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_1_KEY = L"Parallax1TextureKey";
	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_2_KEY = L"Parallax2TextureKey";
	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_3_KEY = L"Parallax3TextureKey";
	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_4_KEY = L"Parallax4TextureKey";
	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_5_KEY = L"Parallax5TextureKey";
	const std::wstring ResourceMaker::PARALLAX_BG_TEXTURE_6_KEY = L"Parallax6TextureKey";


	const std::wstring ResourceMaker::WEAPON_SWORD_TEXTURE_KEY = L"WeaponSwordTextureKey";
	const std::wstring ResourceMaker::HIT_EFFECT_TEXTURE_ATLAS_KEY = L"HitEffectAtlasTextureKey";

	const std::wstring ResourceMaker::UI_HP_BORDER_TEXTURE_KEY = L"UIHpBorder";
	const std::wstring ResourceMaker::UI_HP_BAR_TEXTURE_KEY = L"UIHpBar";
	const std::wstring ResourceMaker::UI_STAMINA_BAR_TEXTURE_KEY = L"UIStaminaBar";

	const std::wstring ResourceMaker::BG_MOON_ATLAS_TEXTURE_KEY = L"BGMoonTexture";
	const std::wstring ResourceMaker::BG_MOON_NORMAL_MAP_TEXTURE_KEY = L"BGMoonNormalTexture";
	const std::wstring ResourceMaker::BG_TREE_1_TEXTURE_KEY = L"BGTree1Texture";
	const std::wstring ResourceMaker::BG_TREE_1_NORMAL_MAP_TEXTURE_KEY = L"BGTree1NormalTexture";
	const std::wstring ResourceMaker::BG_TREE_2_TEXTURE_KEY = L"BGTree2TextureKey";
	const std::wstring ResourceMaker::BG_TREE_2_NORMAL_MAP_TEXTURE_KEY = L"BGTree2NormalTexture";

	const std::wstring ResourceMaker::PLAYER_DASH_EFFECT_TEXTURE_KEY = L"PlayerDashEffectTexture";
	const std::wstring ResourceMaker::GREEN_PORTAL_EFFECT_TEXTURE_ATLAS_KEY = L"GreenPortalTexture";
	const std::wstring ResourceMaker::GREEN_PORTAL_EFFECT_NORMAL_MAP_TEXTURE_KEY = L"GreenPortalNormalTexture";

	const std::wstring ResourceMaker::BRIK_DIFFUSE_TEXTURE_KEY = L"BrickTexture";
	const std::wstring ResourceMaker::BRIK_NORMAL_MAP_TEXTURE_KEY = L"BrickNormalTexture";

#pragma endregion

#pragma region MATERIAL
	const std::wstring ResourceMaker::PLAYER_MATERIAL_KEY = L"PlayerMaterialKey";
	const std::wstring ResourceMaker::PLAYER_NORMAL_MAP_MATERIAL_KEY = L"PlayerNormalMapMaterialKey";

	const std::wstring ResourceMaker::MONSTER_CAGED_SHOKER_MATERIAL_KEY = L"CagedShokerMaterialKey";
	const std::wstring ResourceMaker::MONSTER_CAGED_SHOKER_NORMAL_MAP_MATERIAL_KEY = L"CagedNormalMaterialKey";
	const std::wstring ResourceMaker::MONSTER_SWEEPER_MATERIAL_KEY = L"SweeperMaterialKey";
	const std::wstring ResourceMaker::MONSTER_SWEEPER_NORMAL_MAP_MATERIAL_KEY = L"SweeperNormalMaterialKey";
	const std::wstring ResourceMaker::MONSTER_WARDEN_MATERIAL_KEY = L"WardenMaterialKey";
	const std::wstring ResourceMaker::MONSTER_WARDEN_NORMAL_MAP_MATERIAL_KEY = L"WardenNormalMaterialKey";
	const std::wstring ResourceMaker::OBELISK_MATERIAL_KEY = L"ObeliskMaterialKey";
	const std::wstring ResourceMaker::OBELISK_NORMAL_MAP_MATERIAL_KEY = L"ObeliskNormalMaterialKey";

	const std::wstring ResourceMaker::BATTLE_BG_MATERIAL_KEY = L"BattleBGMaterialKey";
	const std::wstring ResourceMaker::BATTLE_FOREGROUND_NORMALMAP_MATERIAL_KEY = L"BatteForegroundNoramlMapKey";
	const std::wstring ResourceMaker::BATTLE_PARRARELL_BG_MATERIAL_KEY = L"BattleParralrellBGMaterialKey";
	const std::wstring ResourceMaker::WEAPON_SWORD_MATERIAL_KEY = L"WeaponSwordMaterialKey";


	const std::wstring ResourceMaker::HIT_EFFECT_MATERIAL_KEY = L"HitEffectMaterialKey";


	const std::wstring ResourceMaker::DEBUG_MATERIAL_KEY = L"DebugMaterialKey";

	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_1_KEY = L"ParallaxMaterial1";
	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_2_KEY = L"ParallaxMaterial2";
	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_3_KEY = L"ParallaxMaterial3";
	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_4_KEY = L"ParallaxMaterial4";
	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_5_KEY = L"ParallaxMaterial5";
	const std::wstring ResourceMaker::PARALLAX_BG_MATERIAL_6_KEY = L"ParallaxMaterial6";
	const std::wstring ResourceMaker::BG_MOON_MATERIAL_KEY = L"BGMoonMaterial";
	const std::wstring ResourceMaker::BG_MOON_NORMAL_MAP_MATERIAL_KEY = L"BGMoonNormalMaterial";
	const std::wstring ResourceMaker::BG_TREE_1_MATERIAL_KEY = L"BGTree1Material";
	const std::wstring ResourceMaker::BG_TREE_1_NORMAL_MAP_MATERIAL_KEY = L"BGTree1NormalMaterial";
	const std::wstring ResourceMaker::BG_TREE_2_MATERIAL_KEY = L"BGTree2Material";
	const std::wstring ResourceMaker::BG_TREE_2_NORMAL_MAP_MATERIAL_KEY = L"BGTree2NormalMaterial";


	const std::wstring ResourceMaker::UI_HP_BORDER_MATERIAL_KEY = L"UIHPBorderMaterialKey";
	const std::wstring ResourceMaker::UI_HP_BAR_MATERIAL_KEY = L"UIHpBarMaterialKey";
	const std::wstring ResourceMaker::UI_STAMINA_BAR_MATERIAL_KEY = L"UIStaminarBarMaterialKey";

	const std::wstring ResourceMaker::PLAYER_DASH_EFFECT_MATERIAL_KEY = L"PlayerDashEffectMaterialKey";
	const std::wstring ResourceMaker::GREEN_PORTAL_EFFECT_MATERIAL_KEY = L"GreenPortalMaterialKey";
	const std::wstring ResourceMaker::GREEN_PORTAL_EFFECT_NORMAL_MAP_MATERIAL_KEY = L"GreenPortalNormalMaterialKey";

	const std::wstring ResourceMaker::BRIK_MATERIAL_KEY = L"BrickMaterialKey";
	const std::wstring ResourceMaker::BRIK_NOT_NORMAL_MATERIAL_KEY = L"BrickNotNormalMaterialKey";


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
		rectIndexes.reserve(6);
		//rectIndexes.push_back(0);
		//rectIndexes.push_back(1);
		//rectIndexes.push_back(2);
		//rectIndexes.push_back(0);
		//rectIndexes.push_back(2);
		//rectIndexes.push_back(3);
		//rectIndexes.push_back(0);

		rectIndexes.push_back(0);
		rectIndexes.push_back(1);
		rectIndexes.push_back(2);
		rectIndexes.push_back(0);
		rectIndexes.push_back(3);
		rectIndexes.push_back(2);

#pragma region SPRITE_RECT_MESH
		Mesh* pRectMesh = new Mesh();
		mVertices[0] = { {-0.5f,		0.5f,		0.0f},	{0.0f, 0.0f} };
		mVertices[1] = { {0.5f,			0.5f,		0.0f},	{1.0f, 0.0f} };
		mVertices[2] = { {0.5f,			-0.5f,		0.0f},	{1.0f, 1.0f} };
		mVertices[3] = { {-0.5f,		-0.5f,		0.0f},	{0.0f, 1.0f} };
		pRectMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * RECT_VERTEX_COUNT);
		pRectMesh->CreateIndexBuffer(rectIndexes.data(), static_cast<UINT>(rectIndexes.size()));
		ResourcesManager::Insert<Mesh>(RECT_MESH_KEY, pRectMesh);

#pragma region TANGENT_SPACE_FOR_NORMAL_MAPPING
		// FOR TANGENT SPACE Added At 2023-05-23 12:33
		Mesh* pNormalMesh = new NormalMapMesh();

		mNormalMapVertex[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
		mNormalMapVertex[1].Position = Vector3(-0.5f,  0.5f, 0.0f);
		mNormalMapVertex[2].Position = Vector3( 0.5f,  0.5f, 0.0f);
		mNormalMapVertex[3].Position = Vector3( 0.5f, -0.5f, 0.0f);

		std::vector<XMFLOAT3> tempNormal;
		UINT indices[6]
		{
			0, 1, 2,
			0, 3, 2
		};

		mNormalMapVertex[0].UV = Vector2(0.0f, 1.0f);
		mNormalMapVertex[1].UV = Vector2(0.0f, 0.0f);
		mNormalMapVertex[2].UV = Vector2(1.0f, 0.0f);
		mNormalMapVertex[3].UV = Vector2(1.0f, 1.0f);

		//normalized and unnormalized normals
		XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

		///////////////**************new**************////////////////////
		//tangent stuff
		std::vector<XMFLOAT3> tempTangent;
		XMFLOAT3 tangent = XMFLOAT3(0.0f, 0.0f, 0.0f);
		float tcU1, tcV1, tcU2, tcV2;
		///////////////**************new**************////////////////////

		//Used to get vectors (sides) from the position of the verts
		float vecX, vecY, vecZ;

		//Two edges of our triangle
		XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		//Compute face normals
		//And Tangents
		for (int i = 0; i < 2; ++i)
		{
			//Get the vector describing one edge of our triangle (edge 0,2)
			vecX = mNormalMapVertex[indices[(i * 3)]].Position.x - mNormalMapVertex[indices[(i * 3) + 2]].Position.x;
			vecY = mNormalMapVertex[indices[(i * 3)]].Position.y - mNormalMapVertex[indices[(i * 3) + 2]].Position.y;
			vecZ = mNormalMapVertex[indices[(i * 3)]].Position.z - mNormalMapVertex[indices[(i * 3) + 2]].Position.z;
			edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //Create our first edge

			//Get the vector describing another edge of our triangle (edge 2,1)
			vecX = mNormalMapVertex[indices[(i * 3) + 2]].Position.x - mNormalMapVertex[indices[(i * 3) + 1]].Position.x;
			vecY = mNormalMapVertex[indices[(i * 3) + 2]].Position.y - mNormalMapVertex[indices[(i * 3) + 1]].Position.y;
			vecZ = mNormalMapVertex[indices[(i * 3) + 2]].Position.z - mNormalMapVertex[indices[(i * 3) + 1]].Position.z;
			edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //Create our second edge

			//Cross multiply the two edge vectors to get the un-normalized face normal
			XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));

			tempNormal.push_back(unnormalized);

			///////////////**************new**************////////////////////
			//Find first texture coordinate edge 2d vector
			tcU1 = mNormalMapVertex[indices[(i * 3)]].UV.x - mNormalMapVertex[indices[(i * 3) + 2]].UV.x;
			tcV1 = mNormalMapVertex[indices[(i * 3)]].UV.y - mNormalMapVertex[indices[(i * 3) + 2]].UV.y;

			//Find second texture coordinate edge 2d vector
			tcU2 = mNormalMapVertex[indices[(i * 3) + 2]].UV.x - mNormalMapVertex[indices[(i * 3) + 1]].UV.x;
			tcV2 = mNormalMapVertex[indices[(i * 3) + 2]].UV.y - mNormalMapVertex[indices[(i * 3) + 1]].UV.y;

			//Find tangent using both tex coord edges and position edges
			tangent.x = (tcV1 * XMVectorGetX(edge1) - tcV2 * XMVectorGetX(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
			tangent.y = (tcV1 * XMVectorGetY(edge1) - tcV2 * XMVectorGetY(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
			tangent.z = (tcV1 * XMVectorGetZ(edge1) - tcV2 * XMVectorGetZ(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));

			tempTangent.push_back(tangent);
			///////////////**************new**************////////////////////
		}

		//Compute vertex normals (normal Averaging)
		XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		int facesUsing = 0;
		float tX, tY, tZ;    //temp axis variables

		//Go through each vertex
		for (int i = 0; i < RECT_VERTEX_COUNT; ++i)
		{
			//Check which triangles use this vertex
			for (int j = 0; j < 2; ++j)
			{
				if (indices[j * 3] == i ||
					indices[(j * 3) + 1] == i ||
					indices[(j * 3) + 2] == i)
				{
					tX = XMVectorGetX(normalSum) + tempNormal[j].x;
					tY = XMVectorGetY(normalSum) + tempNormal[j].y;
					tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;

					normalSum = XMVectorSet(tX, tY, tZ, 0.0f);    //If a face is using the vertex, add the unormalized face normal to the normalSum

					///////////////**************new**************////////////////////        
					//We can reuse tX, tY, tZ to sum up tangents
					tX = XMVectorGetX(tangentSum) + tempTangent[j].x;
					tY = XMVectorGetY(tangentSum) + tempTangent[j].y;
					tZ = XMVectorGetZ(tangentSum) + tempTangent[j].z;

					tangentSum = XMVectorSet(tX, tY, tZ, 0.0f); //sum up face tangents using this vertex
					///////////////**************new**************////////////////////

					facesUsing++;
				}
			}

			//Get the actual normal by dividing the normalSum by the number of faces sharing the vertex
			normalSum = normalSum / static_cast<float>(facesUsing);
			///////////////**************new**************////////////////////
			tangentSum = tangentSum / static_cast<float>(facesUsing);
			///////////////**************new**************////////////////////

			//Normalize the normalSum vector and tangent
			normalSum = XMVector3Normalize(normalSum);
			///////////////**************new**************////////////////////
			tangentSum = XMVector3Normalize(tangentSum);
			///////////////**************new**************////////////////////

			//Store the normal and tangent in our current vertex
			//mNormalMapVertex[i].Normal.x = XMVectorGetX(normalSum);
			//mNormalMapVertex[i].Normal.y = XMVectorGetY(normalSum);
			//mNormalMapVertex[i].Normal.z = XMVectorGetZ(normalSum);
			
			mNormalMapVertex[i].Normal.x = 0.0f;
			mNormalMapVertex[i].Normal.y = 0.0f;
			mNormalMapVertex[i].Normal.z = -1.0f;

			///////////////**************new**************////////////////////
			mNormalMapVertex[i].Tangent.x = XMVectorGetX(tangentSum);
			mNormalMapVertex[i].Tangent.y = XMVectorGetY(tangentSum);
			mNormalMapVertex[i].Tangent.z = XMVectorGetZ(tangentSum);
			///////////////**************new**************////////////////////

			//Clear normalSum, tangentSum and facesUsing for next vertex
			normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			///////////////**************new**************////////////////////
			tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			///////////////**************new**************////////////////////
			facesUsing = 0;

		}


		pNormalMesh->CreateVertexBuffer(mNormalMapVertex, sizeof(NormalMapShaderVertex) * RECT_VERTEX_COUNT);
		pNormalMesh->CreateIndexBuffer(indices, 6);
		ResourcesManager::Insert<Mesh>(RECT_NORMAL_MAP_MESH_KEY, pNormalMesh);

#pragma endregion


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

		Shader* pNormalMapSpriteShader = new NormalMapShader();
		pNormalMapSpriteShader->CreateShaders(L"jhNormalMapSpriteVS.hlsl", L"jhNormalMapSpritePS.hlsl");
		ResourcesManager::Insert<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY, pNormalMapSpriteShader);


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

		Texture* pPlayerNormalMapAtalsTexture = new Texture();
		pPlayerNormalMapAtalsTexture->Load(L"Sword Master Sprite Sheet 90x37_NM.png");
		ResourcesManager::Insert<Texture>(PLAYER_NORMAL_MAP_TEXTURE_ATLAS_KEY, pPlayerNormalMapAtalsTexture);


		Texture* pCagedShokerAtlasTexture = new Texture();
		pCagedShokerAtlasTexture->Load(L"caged shocker 110x42.png");
		ResourcesManager::Insert<Texture>(MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY, pCagedShokerAtlasTexture);

		Texture* pCagedShokerNormalMapTexture = new Texture();
		pCagedShokerNormalMapTexture->Load(L"caged shocker 110x42_NM.png");
		ResourcesManager::Insert<Texture>(MONSTER_TEXTURE_CAGED_SHOKER_NORMAL_MAP_KEY, pCagedShokerNormalMapTexture);

		Texture* pSweeperAtlasTexture = new Texture();
		pSweeperAtlasTexture->Load(L"Sweeper.png");
		ResourcesManager::Insert<Texture>(MONSTER_TEXTURE_SWEEPER_ATLAS_KEY, pSweeperAtlasTexture);

		Texture* pSweeperNormalMapTexture = new Texture();
		pSweeperNormalMapTexture->Load(L"Sweeper_NM.png");
		ResourcesManager::Insert<Texture>(MONSTER_TEXTURE_SWEEPER_NORMAL_MAP_KEY, pSweeperNormalMapTexture);


		Texture* pWardenAtlasTexture = new Texture();
		pWardenAtlasTexture->Load(L"TheDarkWarden97x32.png");
		ResourcesManager::Insert<Texture>(MONSTER_TEXTURE_WARDEN_ATLAS_KEY, pWardenAtlasTexture);

		Texture* pWardenNormalMapTexture = new Texture();
		pWardenNormalMapTexture->Load(L"TheDarkWarden97x32_NM.png");
		ResourcesManager::Insert<Texture>(MONSTER_TEXTURE_WARDEN_NORMAL_MAP_KEY, pWardenNormalMapTexture);


		Texture* pObeliskAtlasTexture = new Texture();
		// ObeliskEffects.png
		// Obelisk.png
		pObeliskAtlasTexture->Load(L"ObeliskEffects.png");
		ResourcesManager::Insert<Texture>(OBELISK_TEXTURE_ATLAS_KEY, pObeliskAtlasTexture);
		Texture* pObeliskNormalMapTexture = new Texture();
		pObeliskNormalMapTexture->Load(L"ObeliskEffects_NM.png");
		ResourcesManager::Insert<Texture>(OBELISK_TEXTURE_NORMAL_MAP_KEY, pObeliskNormalMapTexture);


		Texture* pGreenPortalTextureAtlas = new Texture();
		pGreenPortalTextureAtlas->Load(L"GreenPortalSpriteSheet.png");
		ResourcesManager::Insert<Texture>(GREEN_PORTAL_EFFECT_TEXTURE_ATLAS_KEY, pGreenPortalTextureAtlas);

		Texture* pGreenPortalNormalMapTextureAtlas = new Texture();
		pGreenPortalNormalMapTextureAtlas->Load(L"GreenPortalSpriteSheet_NM.png");
		ResourcesManager::Insert<Texture>(GREEN_PORTAL_EFFECT_NORMAL_MAP_TEXTURE_KEY, pGreenPortalNormalMapTextureAtlas);



		Texture* pBattleBGTexture = new Texture();
		pBattleBGTexture->Load(L"ForeGround.png");
		ResourcesManager::Insert<Texture>(BATTLE_FOREGROUND_TEXTURE_KEY, pBattleBGTexture);
		
		Texture* pBattleForegroundNormalMapTexture = new Texture();
		pBattleForegroundNormalMapTexture->Load(L"ForeGround_NM.png");
		ResourcesManager::Insert<Texture>(BATTLE_FOREGROUND_NORMAL_MAP_TEXTURE_KEY, pBattleForegroundNormalMapTexture);



		Texture* pBattleParrarellBGTxtrue = new Texture();
		pBattleParrarellBGTxtrue->Load(L"SkyMerge.png");
		ResourcesManager::Insert<Texture>(BATTLE_PARRARELL_BG_TEXTURE_KEY, pBattleParrarellBGTxtrue);


		Texture* pWeaponSwordTxtrue = new Texture();
		pWeaponSwordTxtrue->Load(L"SwordSwingTopDown.png");
		ResourcesManager::Insert<Texture>(WEAPON_SWORD_TEXTURE_KEY, pWeaponSwordTxtrue);

		Texture* pEffectSwordTxtrue = new Texture();
		pEffectSwordTxtrue->Load(L"EffectAtals.png");
		ResourcesManager::Insert<Texture>(HIT_EFFECT_TEXTURE_ATLAS_KEY, pEffectSwordTxtrue);

		Texture* pParralaxTxtrue = new Texture();
		pParralaxTxtrue->Load(L"parallax1.png");
		ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_1_KEY, pParralaxTxtrue);

		pParralaxTxtrue = new Texture();
		pParralaxTxtrue->Load(L"parallax2.png");
		ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_2_KEY, pParralaxTxtrue);

		//pParralaxTxtrue = new Texture();
		//pParralaxTxtrue->Load(L"parallax3.png");
		//ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_3_KEY, pParralaxTxtrue);

		//pParralaxTxtrue = new Texture();
		//pParralaxTxtrue->Load(L"parallax4.png");
		//ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_4_KEY, pParralaxTxtrue);

		//pParralaxTxtrue = new Texture();
		//pParralaxTxtrue->Load(L"parallax5.png");
		//ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_5_KEY, pParralaxTxtrue);

		//pParralaxTxtrue = new Texture();
		//pParralaxTxtrue->Load(L"parallax6.png");
		//ResourcesManager::Insert<Texture>(PARALLAX_BG_TEXTURE_6_KEY, pParralaxTxtrue);

		Texture* pBGMoonTexture = new Texture();
		pBGMoonTexture->Load(L"MoonSprite.png");
		ResourcesManager::Insert<Texture>(BG_MOON_ATLAS_TEXTURE_KEY, pBGMoonTexture);

		Texture* pBGMoonNormalMapTexture = new Texture();
		pBGMoonNormalMapTexture->Load(L"MoonSprite_NM.png");
		ResourcesManager::Insert<Texture>(BG_MOON_NORMAL_MAP_TEXTURE_KEY, pBGMoonNormalMapTexture);

		Texture* pTree1Texture = new Texture();
		pTree1Texture->Load(L"Tree 1 Sprite Sheet 112x128.png");
		ResourcesManager::Insert<Texture>(BG_TREE_1_TEXTURE_KEY, pTree1Texture);

		Texture* pTree1NormalTexture = new Texture();
		pTree1NormalTexture->Load(L"Tree 1 Sprite Sheet 112x128_NM.png");
		ResourcesManager::Insert<Texture>(BG_TREE_1_NORMAL_MAP_TEXTURE_KEY, pTree1NormalTexture);

		
		Texture* pTree2Texture = new Texture();
		pTree2Texture->Load(L"Tree 2 Sprite Sheet 128x96.png");
		ResourcesManager::Insert<Texture>(BG_TREE_2_TEXTURE_KEY, pTree2Texture);

		Texture* pTree2NormalTexture = new Texture();
		pTree2NormalTexture->Load(L"Tree 2 Sprite Sheet 128x96_NM.png");
		ResourcesManager::Insert<Texture>(BG_TREE_2_NORMAL_MAP_TEXTURE_KEY, pTree2NormalTexture);

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

		Texture* pBrickDiffuse = new Texture();
		pBrickDiffuse->Load(L"brickwall.jpg");
		ResourcesManager::Insert<Texture>(BRIK_DIFFUSE_TEXTURE_KEY, pBrickDiffuse);

		Texture* pBrickNormal = new Texture();
		pBrickNormal->Load(L"brickwall_normal.jpg");
		ResourcesManager::Insert<Texture>(BRIK_NORMAL_MAP_TEXTURE_KEY, pBrickNormal);
	}

	void ResourceMaker::createMaterial()
	{
		Material* pPlayerMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(PLAYER_TEXTURE_ATLAS_KEY));
		ResourcesManager::Insert<Material>(PLAYER_MATERIAL_KEY, pPlayerMaterial);

		Material* pPlayerNormalMaterial = new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(PLAYER_TEXTURE_ATLAS_KEY), ResourcesManager::Find<Texture>(PLAYER_NORMAL_MAP_TEXTURE_ATLAS_KEY));
		ResourcesManager::Insert<Material>(PLAYER_NORMAL_MAP_MATERIAL_KEY, pPlayerNormalMaterial);

		Material* pBrickNormalTexture = new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(BRIK_DIFFUSE_TEXTURE_KEY), ResourcesManager::Find<Texture>(BRIK_NORMAL_MAP_TEXTURE_KEY));
		ResourcesManager::Insert<Material>(BRIK_MATERIAL_KEY, pBrickNormalTexture);

		Material* pBrickNotNormalMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(BRIK_DIFFUSE_TEXTURE_KEY));
		ResourcesManager::Insert<Material>(BRIK_NOT_NORMAL_MATERIAL_KEY, pBrickNotNormalMaterial);

		Material* pCagedMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY));
		ResourcesManager::Insert<Material>(MONSTER_CAGED_SHOKER_MATERIAL_KEY, pCagedMaterial);

		Material* pCagedNormalMapMaterial = new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_CAGED_SHOKER_NORMAL_MAP_KEY));
		ResourcesManager::Insert<Material>(MONSTER_CAGED_SHOKER_NORMAL_MAP_MATERIAL_KEY, pCagedNormalMapMaterial);

		Material* pSweeperMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_SWEEPER_ATLAS_KEY));
		ResourcesManager::Insert<Material>(MONSTER_SWEEPER_MATERIAL_KEY, pSweeperMaterial);

		Material* pSweeperNormalMapMaterial = new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_SWEEPER_ATLAS_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_SWEEPER_NORMAL_MAP_KEY));
		ResourcesManager::Insert<Material>(MONSTER_SWEEPER_NORMAL_MAP_MATERIAL_KEY, pSweeperNormalMapMaterial);


		Material* pWardenMaterial = new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_WARDEN_ATLAS_KEY));
		ResourcesManager::Insert<Material>(MONSTER_WARDEN_MATERIAL_KEY, pWardenMaterial);

		Material* pWardenNormalMapMaterial = new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_WARDEN_ATLAS_KEY), ResourcesManager::Find<Texture>(MONSTER_TEXTURE_WARDEN_NORMAL_MAP_KEY));
		ResourcesManager::Insert<Material>(MONSTER_WARDEN_NORMAL_MAP_MATERIAL_KEY, pWardenNormalMapMaterial);

		ResourcesManager::Insert<Material>(OBELISK_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(OBELISK_TEXTURE_ATLAS_KEY))
			);

		ResourcesManager::Insert<Material>(OBELISK_NORMAL_MAP_MATERIAL_KEY,
			new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(OBELISK_TEXTURE_ATLAS_KEY),
				ResourcesManager::Find<Texture>(OBELISK_TEXTURE_NORMAL_MAP_KEY))
			);


		Material* pBattleBGMaterial = new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY), ResourcesManager::Find<Texture>(BATTLE_FOREGROUND_TEXTURE_KEY));
		ResourcesManager::Insert<Material>(BATTLE_BG_MATERIAL_KEY, pBattleBGMaterial);

		ResourcesManager::Insert<Material>(BATTLE_FOREGROUND_NORMALMAP_MATERIAL_KEY,
			new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(BATTLE_FOREGROUND_TEXTURE_KEY),
				ResourcesManager::Find<Texture>(BATTLE_FOREGROUND_NORMAL_MAP_TEXTURE_KEY))
			);


		ResourcesManager::Insert<Material>(BG_TREE_1_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(BG_TREE_1_TEXTURE_KEY))
			);
		
		ResourcesManager::Insert<Material>(BG_TREE_1_NORMAL_MAP_MATERIAL_KEY,
			new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(BG_TREE_1_TEXTURE_KEY), 
				ResourcesManager::Find<Texture>(BG_TREE_1_NORMAL_MAP_TEXTURE_KEY))
			);


		ResourcesManager::Insert<Material>(BG_TREE_2_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(BG_TREE_2_TEXTURE_KEY))
			);

		ResourcesManager::Insert<Material>(BG_TREE_2_NORMAL_MAP_MATERIAL_KEY,
			new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(BG_TREE_2_TEXTURE_KEY),
				ResourcesManager::Find<Texture>(BG_TREE_2_NORMAL_MAP_TEXTURE_KEY))
			);


		ResourcesManager::Insert<Material>(BATTLE_PARRARELL_BG_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(BATTLE_BG_SHADER_KEY),
				ResourcesManager::Find<Texture>(BATTLE_PARRARELL_BG_TEXTURE_KEY))
			);

		ResourcesManager::Insert<Material>(WEAPON_SWORD_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(WEAPON_SWORD_TEXTURE_KEY))
			);

		ResourcesManager::Insert<Material>(HIT_EFFECT_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(HIT_EFFECT_TEXTURE_ATLAS_KEY))
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
		ResourcesManager::Insert<Material>(BG_MOON_NORMAL_MAP_MATERIAL_KEY,
			new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(BG_MOON_ATLAS_TEXTURE_KEY),
				ResourcesManager::Find<Texture>(BG_MOON_NORMAL_MAP_TEXTURE_KEY))
			);


		ResourcesManager::Insert<Material>(PLAYER_DASH_EFFECT_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(PLAYER_DASH_EFFECT_TEXTURE_KEY))
			);

		ResourcesManager::Insert<Material>(GREEN_PORTAL_EFFECT_MATERIAL_KEY,
			new Material(ResourcesManager::Find<Shader>(SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(GREEN_PORTAL_EFFECT_TEXTURE_ATLAS_KEY))
			);

		ResourcesManager::Insert<Material>(GREEN_PORTAL_EFFECT_NORMAL_MAP_MATERIAL_KEY,
			new NormalMapMaterial(ResourcesManager::Find<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY),
				ResourcesManager::Find<Texture>(GREEN_PORTAL_EFFECT_TEXTURE_ATLAS_KEY),
				ResourcesManager::Find<Texture>(GREEN_PORTAL_EFFECT_NORMAL_MAP_TEXTURE_KEY))
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