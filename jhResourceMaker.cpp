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
#include "jhMonsterUIMaterial.h"
#include "jhMonsterUIMesh.h"

using namespace jh::math;

namespace jh
{
#pragma region KEYS
#pragma region MESH
	const std::wstring ResourceMaker::RECT_MESH_KEY = L"RectMesh";
	const std::wstring ResourceMaker::BATTLE_BG_MESH_KEY = L"BattleBGMesh";
	const std::wstring ResourceMaker::DEBUG_RECT_MESH_KEY = L"DebugRectMesh";

	// Added Part FOR NORMAL_MAP At 2023-05-23 16:40
	const std::wstring ResourceMaker::RECT_NORMAL_MAP_MESH_KEY = L"NormalMapMeshy";

	const std::wstring ResourceMaker::UI_LEVEL_UP_MESH_KEY = L"UILevelUPMesh";

#pragma endregion

#pragma region SHADER
	const std::wstring ResourceMaker::SPRITE_SHADER_KEY = L"SpriteShader";
	const std::wstring ResourceMaker::NORMAL_MAP_SPRITE_SHADER_KEY = L"NormalMapSpriteShader";
	const std::wstring ResourceMaker::BG_NO_LIGHTING_SHADER_KEY = L"BattleBGShader";
	const std::wstring ResourceMaker::DEBUG_SHADER_KEY = L"DebugShader";
	const std::wstring ResourceMaker::UI_HP_SHADER_KEY = L"UIHPShader";
	const std::wstring ResourceMaker::UI_EXP_SHADER_KEY = L"UIEXPShader";
	const std::wstring ResourceMaker::UI_STAMINA_SHADER_KEY = L"UIStaminaShader";
	const std::wstring ResourceMaker::UI_MONSTER_HP_SHADER_KEY = L"UIMonsterShader";
	const std::wstring ResourceMaker::UI_BOSS_MONSTER_HP_SHADER_KEY = L"UIBossHpShader";
	const std::wstring ResourceMaker::UI_LEVEL_UP_SHADER_KEY = L"UILevelUPShader";
#pragma endregion

#pragma region TEXTURE
#pragma region PLAYER_TEXTURE
	const std::wstring ResourceMaker::PLAYER_TEXTURE_ATLAS_KEY = L"PlayerTextureAtlas";
	const std::wstring ResourceMaker::PLAYER_NORMAL_MAP_TEXTURE_ATLAS_KEY = L"PlayerNormalMapTextureAtlas";
#pragma endregion

#pragma region MONSTER_TEXTURE
	const std::wstring ResourceMaker::MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY = L"CagedTextureAtals";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_CAGED_SHOKER_NORMAL_MAP_KEY = L"CagedNormalTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_SWEEPER_ATLAS_KEY = L"SweeperTextureAtals";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_SWEEPER_NORMAL_MAP_KEY = L"SweeperNormalTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_WARDEN_ATLAS_KEY = L"WardenTextureAtals";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_WARDEN_NORMAL_MAP_KEY = L"WardenNormalTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_ZOMBIE_KEY = L"ZombieTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_ZOMBIE_NORMAL_MAP_KEY = L"ZombieNormalTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_HEABY_SLICER_KEY = L"HeabySlicerTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_HEABY_SLICER_NORMAL_MAP_KEY = L"HeabySlicerNormalTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_LIGHT_SLICER_KEY = L"LightSlicerTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_LIGHT_SLICER_NORMAL_MAP_KEY = L"LightSlicerNormalTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_DAGGER_KEY = L"DaggerTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_DAGGER_NORMAL_MAP_KEY = L"DaggerNormalTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_ARCHER_KEY = L"ArcherTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_ARCHER_NORMAL_MAP_KEY = L"ArcherNormalTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_BLASTER_KEY = L"BlasterTexture";
	const std::wstring ResourceMaker::MONSTER_TEXTURE_ACIENT_BOSS_KEY = L"AcientBossTexture";
#pragma endregion

#pragma region SKILL_TEXTURE
	const std::wstring ResourceMaker::SKILL_TEXTURE_ELECTRIC_BEAM_KEY = L"SkillElectricBeamTexture";
	const std::wstring ResourceMaker::SKILL_TEXTURE_ELECTRIC_STRIKE_KEY = L"SkillElectricStrikeTexture";
	const std::wstring ResourceMaker::SKILL_TEXTURE_ELECTRIC_TORNADO_KEY = L"SkillElectricTornadoTexture";
	const std::wstring ResourceMaker::SKILL_SELECT_BOX_TEXTURE_KEY = L"SkillSelectBoxTexture";
#pragma endregion

#pragma region SKILL_ICON_TEXTURE
	const std::wstring ResourceMaker::SKILL_ICON_TEXTURE_ELECTRIC_BEAM_KEY = L"SkillIconElectricBeamTexture";
	const std::wstring ResourceMaker::SKILL_ICON_TEXTURE_ELECTRIC_STRIKE_KEY = L"SkillIconElectricStrikeTexture";
	const std::wstring ResourceMaker::SKILL_ICON_TEXTURE_ELECTRIC_TORNADO_KEY = L"SkillIconElectricTornadoTexture";
	const std::wstring ResourceMaker::SKILL_ICON_TEXTURE_MELLE_ATTACK_KEY = L"SkillIconMelleAttackTexture";
	const std::wstring ResourceMaker::SKILL_ICON_TEXTURE_SPEED_KEY = L"SkillIconaSpeedTexture";
	const std::wstring ResourceMaker::SKILL_ICON_TEXTURE_HEALTH_KEY = L"SkillIconaHealthTexture";
#pragma endregion

#pragma region SKILL_TEXT_TEXTURE
	const std::wstring ResourceMaker::SKILL_TEXT_TEXTURE_ELECTRIC_BEAM_LV_1_KEY = L"SkillTextBeamLv1";
	const std::wstring ResourceMaker::SKILL_TEXT_TEXTURE_ELECTRIC_STRIKE_LV_1_KEY = L"SkillTextStrikeLv1";
	const std::wstring ResourceMaker::SKILL_TEXT_TEXTURE_ELECTRIC_TORANDO_LV_1_KEY = L"SkillTextTornadoLv1";
	const std::wstring ResourceMaker::SKILL_TEXT_TEXTURE_ELECTRIC_DAMAGE_INCREASE_KEY = L"SkillTextElectricDamage";
	const std::wstring ResourceMaker::SKILL_TEXT_TEXTURE_ELECTRIC_SPAWN_SPEED_KEY = L"SkillTextElectricSpawnSpeed";
	const std::wstring ResourceMaker::SKILL_TEXT_TEXTURE_SWORD_DAMAGE_KEY = L"SkillTextSwordDamage";
	const std::wstring ResourceMaker::SKILL_TEXT_TEXTURE_MOVEMENT_SPEED_KEY = L"SkillTextMovementSpeed";
	const std::wstring ResourceMaker::SKILL_TEXT_TEXTURE_RECOVER_HEALTH_KEY = L"SkillTextRecoverHealth";
#pragma endregion

#pragma region UI_TEXTURE
	const std::wstring ResourceMaker::UI_HP_BORDER_TEXTURE_KEY = L"UIHpBorder";
	const std::wstring ResourceMaker::UI_HP_BAR_TEXTURE_KEY = L"UIHpBar";
	const std::wstring ResourceMaker::UI_EXP_BAR_TEXTURE_KEY = L"UIEXPBar";
	const std::wstring ResourceMaker::UI_STAMINA_BAR_TEXTURE_KEY = L"UIStaminaBar";
	const std::wstring ResourceMaker::UI_MONSTER_HP_BAR_TEXTURE_KEY = L"UIMonsterBar";
	const std::wstring ResourceMaker::UI_MONSTER_HP_CIRCLE_TEXTURE_KEY = L"UIMonsterCi";
	const std::wstring ResourceMaker::UI_TEXTURE_LEVEL_UP_BORDER_KEY = L"UILevelUPBorder";
#pragma endregion

#pragma region BG_FG_PARRALAX_TEXTURE
	const std::wstring ResourceMaker::BG_FOREGROUND_TEXTURE_KEY = L"BattleBGTextureKey";
	const std::wstring ResourceMaker::BG_FOREGROUND_NORMAL_MAP_TEXTURE_KEY = L"BattleForegroundNomal";
	const std::wstring ResourceMaker::BG_PARALLAX_TEXTURE_1_KEY = L"Parallax1Texture";
	const std::wstring ResourceMaker::BG_PARALLAX_TEXTURE_2_KEY = L"Parallax2Texture";
	const std::wstring ResourceMaker::BG_PARALLAX_TEXTURE_3_KEY = L"Parallax3Texture";
	const std::wstring ResourceMaker::BG_PARALLAX_TEXTURE_4_KEY = L"Parallax4Texture";
	const std::wstring ResourceMaker::BG_PARALLAX_TEXTURE_5_KEY = L"Parallax5Texture";
	const std::wstring ResourceMaker::BG_PARALLAX_TEXTURE_6_KEY = L"Parallax6Texture";
#pragma endregion

#pragma region BG_ANIMATED_OBJECTS_TEXTURE
	const std::wstring ResourceMaker::BG_OBELISK_TEXTURE_ATLAS_KEY = L"ObeliskTextureAtalsKey";
	const std::wstring ResourceMaker::BG_OBELISK_TEXTURE_NORMAL_MAP_KEY = L"ObeliskNoramlTextureKey";
	const std::wstring ResourceMaker::BG_MOON_ATLAS_TEXTURE_KEY = L"BGMoonTexture";
	const std::wstring ResourceMaker::BG_MOON_NORMAL_MAP_TEXTURE_KEY = L"BGMoonNormalTexture";
	const std::wstring ResourceMaker::BG_TREE_1_TEXTURE_KEY = L"BGTree1Texture";
	const std::wstring ResourceMaker::BG_TREE_1_NORMAL_MAP_TEXTURE_KEY = L"BGTree1NormalTexture";
	const std::wstring ResourceMaker::BG_TREE_2_TEXTURE_KEY = L"BGTree2TextureKey";
	const std::wstring ResourceMaker::BG_TREE_2_NORMAL_MAP_TEXTURE_KEY = L"BGTree2NormalTexture";
	const std::wstring ResourceMaker::BG_FLOWER_TEXTURE_KEY = L"BGFlowerTexture";
	const std::wstring ResourceMaker::BG_FLOWER_NORMAL_MAP_TEXTURE_KEY = L"BGFlowerNormalTexture";
	const std::wstring ResourceMaker::BG_TORCH_TEXTURE_KEY = L"BGTorchTexture";
	const std::wstring ResourceMaker::BG_MUSHROOM_STATUE_TEXTURE_KEY = L"BGMushStatueTexture";
	const std::wstring ResourceMaker::BG_MUSHROOM_STATUE_NORMAL_MAP_TEXTURE_KEY = L"BGMushStatueNormalTexture";
	const std::wstring ResourceMaker::BG_FOREGROUND_GRASS_TEXTURE_KEY = L"BGForeGrassTexture";
	const std::wstring ResourceMaker::BG_LARGE_LIGHTNING_TEXTURE_KEY = L"BGLargeLightningTexture";
	const std::wstring ResourceMaker::BG_LARGE_LIGHTNING_NORMAL_MAP_TEXTURE_KEY = L"BGLargeLightningNormalTexture";
	const std::wstring ResourceMaker::BG_SMALL_LIGHTNING_TEXTURE_KEY = L"BGSmallLightningTexture";
	const std::wstring ResourceMaker::BG_SMALL_LIGHTNING_NORMAL_MAP_TEXTURE_KEY = L"BGSmallLightningNormalTexture";
#pragma endregion

#pragma region EFFECT_TEXTURE
	const std::wstring ResourceMaker::EFFECT_HIT_TEXTURE_ATLAS_KEY = L"HitEffectAtlasTextureKey";
	const std::wstring ResourceMaker::EFFECT_PLAYER_DASH_TEXTURE_KEY = L"PlayerDashEffectTexture";
	const std::wstring ResourceMaker::EFFECT_GREEN_PORTAL_TEXTURE_ATLAS_KEY = L"GreenPortalTexture";
	const std::wstring ResourceMaker::EFFECT_GREEN_PORTAL_NORMAL_MAP_TEXTURE_KEY = L"GreenPortalNormalTexture";
	const std::wstring ResourceMaker::EFFECT_PLAYER_LEVEL_UP_TEXTURE_KEY = L"LevelUpTexture";
#pragma endregion
#pragma region PROTECT_CRYSTAL
	const std::wstring ResourceMaker::PROTECT_CRYSTAL_TEXTURE_KEY = L"ProtectCryTexture";
#pragma endregion

#pragma region OTHER
	const std::wstring ResourceMaker::BRIK_DIFFUSE_TEXTURE_KEY = L"BrickTexture";
	const std::wstring ResourceMaker::BRIK_NORMAL_MAP_TEXTURE_KEY = L"BrickNormalTexture";
#pragma endregion

#pragma endregion

#pragma region MATERIAL
#pragma region PLAYER_MATERIAL
	const std::wstring ResourceMaker::PLAYER_MATERIAL_KEY = L"PlayerMaterial";
	const std::wstring ResourceMaker::PLAYER_NORMAL_MAP_MATERIAL_KEY = L"PlayerNormalMapMaterial";
#pragma endregion

#pragma region MONSTER_MATERIAL
	const std::wstring ResourceMaker::MONSTER_CAGED_SHOKER_MATERIAL_KEY = L"CagedShokerMaterial";
	const std::wstring ResourceMaker::MONSTER_CAGED_SHOKER_NORMAL_MAP_MATERIAL_KEY = L"CagedNormalMaterial";
	
	const std::wstring ResourceMaker::MONSTER_SWEEPER_MATERIAL_KEY = L"SweeperMaterial";
	const std::wstring ResourceMaker::MONSTER_SWEEPER_NORMAL_MAP_MATERIAL_KEY = L"SweeperNormalMaterial";
	
	const std::wstring ResourceMaker::MONSTER_WARDEN_MATERIAL_KEY = L"WardenMaterial";
	const std::wstring ResourceMaker::MONSTER_WARDEN_NORMAL_MAP_MATERIAL_KEY = L"WardenNormalMaterial";
	
	const std::wstring ResourceMaker::MONSTER_ZOMBIE_MATERIAL_KEY = L"ZombieMaterial";
	const std::wstring ResourceMaker::MONSTER_ZOMBIE_NORMAL_MAP_MATERIAL_KEY = L"ZombieNormalMaterial";
	
	const std::wstring ResourceMaker::MONSTER_HEABY_SLICER_MATERIAL_KEY = L"HeabySlicerMaterial";
	const std::wstring ResourceMaker::MONSTER_HEABY_SLICER_NORMAL_MAP_MATERIAL_KEY = L"HeabySlicerNormalMaterial";
	
	const std::wstring ResourceMaker::MONSTER_LIGHT_SLICER_MATERIAL_KEY = L"LightSlicerMaterial";
	const std::wstring ResourceMaker::MONSTER_LIGHT_SLICER_NORMAL_MAP_MATERIAL_KEY = L"LightSlicerNormalMaterial";
	
	const std::wstring ResourceMaker::MONSTER_DAGGER_MATERIAL_KEY = L"DaggerMaterial";
	const std::wstring ResourceMaker::MONSTER_DAGGER_NORMAL_MAP_MATERIAL_KEY = L"DaggerNormalMaterial";
	
	const std::wstring ResourceMaker::MONSTER_ARCHER_MATERIAL_KEY = L"ArcherMaterial";
	const std::wstring ResourceMaker::MONSTER_ARCHER_NORMAL_MAP_MATERIAL_KEY = L"ArcherNormalMaterial";
	
	const std::wstring ResourceMaker::MONSTER_BLASTER_MATERIAL_KEY = L"BlasterMaterial";
	
	const std::wstring ResourceMaker::MONSTER_ACIENT_BOSS_MATERIAL_KEY = L"AcientBossMaterial";



#pragma endregion

#pragma region SKILL_MATERIAL
	const std::wstring ResourceMaker::SKILL_MATERIAL_ELECTRIC_BEAM_KEY = L"SkillElectricBeamMaterial";
	const std::wstring ResourceMaker::SKILL_MATERIAL_ELECTRIC_STRIKE_KEY = L"SkillElectricStrikeMaterial";
	const std::wstring ResourceMaker::SKILL_MATERIAL_ELECTRIC_TORNADO_KEY = L"SkillElectricTornadoMaterial";
	const std::wstring ResourceMaker::SKILL_SELECT_BOX_MATERIAL_KEY = L"SkillSelectBoxMaterial";

#pragma endregion

#pragma region SKILL_ICON_MATERIAL
	const std::wstring ResourceMaker::SKILL_ICON_MATERIAL_ELECTRIC_BEAM_KEY = L"SkillIconElectricBeamMaterial";
	const std::wstring ResourceMaker::SKILL_ICON_MATERIAL_ELECTRIC_STRIKE_KEY = L"SkillIconElectricStrikeMaterial";
	const std::wstring ResourceMaker::SKILL_ICON_MATERIAL_ELECTRIC_TORNADO_KEY = L"SkillIconElectricTornadoMaterial";
	const std::wstring ResourceMaker::SKILL_ICON_MATERIAL_MELLE_ATTACK_KEY = L"SkillIconMelleAttackMaterial";
	const std::wstring ResourceMaker::SKILL_ICON_MATERIAL_SPEED_KEY = L"SkillIconSpeedMaterial";
	const std::wstring ResourceMaker::SKILL_ICON_MATERIAL_HEALTH_KEY = L"SkillIconHealthMaterial";
#pragma endregion

#pragma region SKILL_TEXT_MATERIAL
	const std::wstring ResourceMaker::SKILL_TEXT_MATERIAL_ELECTRIC_BEAM_LV_1_KEY = L"SkillTextBeamLv1Mat";
	const std::wstring ResourceMaker::SKILL_TEXT_MATERIAL_ELECTRIC_STRIKE_LV_1_KEY = L"SkillTextStrikeLv1Mat";
	const std::wstring ResourceMaker::SKILL_TEXT_MATERIAL_ELECTRIC_TORANDO_LV_1_KEY = L"SkillTextTornadoLv1Mat";
	const std::wstring ResourceMaker::SKILL_TEXT_MATERIAL_ELECTRIC_DAMAGE_INCREASE_KEY = L"SkillTextElectricDamageMat";
	const std::wstring ResourceMaker::SKILL_TEXT_MATERIAL_ELECTRIC_SPAWN_SPEED_KEY = L"SkillTextElectricSpawnSpeedMat";
	const std::wstring ResourceMaker::SKILL_TEXT_MATERIAL_SWORD_DAMAGE_KEY = L"SkillTextSwordDamageMat";
	const std::wstring ResourceMaker::SKILL_TEXT_MATERIAL_MOVEMENT_SPEED_KEY = L"SkillTextMovementSpeedMat";
	const std::wstring ResourceMaker::SKILL_TEXT_MATERIAL_RECOVER_HEALTH_KEY = L"SkillTextRecoverHealthMat";
#pragma endregion

#pragma region UI_MATERIAL
	const std::wstring ResourceMaker::UI_HP_BORDER_MATERIAL_KEY = L"UIHPBorderMaterial";
	const std::wstring ResourceMaker::UI_HP_BAR_MATERIAL_KEY = L"UIHpBarMaterial";
	const std::wstring ResourceMaker::UI_EXP_BAR_MATERIAL_KEY = L"UIEXPBarMaterial";
	const std::wstring ResourceMaker::UI_STAMINA_BAR_MATERIAL_KEY = L"UIStaminarBarMaterial";
	const std::wstring ResourceMaker::UI_MONSTER_HP_BAR_MATERIAL_KEY = L"UIMonsterMaterial";
	const std::wstring ResourceMaker::UI_MONSTER_HP_CIRCLE_MATERIAL_KEY = L"UIMonsterCircleMaterial";
	const std::wstring ResourceMaker::UI_MATERIAL_LEVEL_UP_BORDER_KEY = L"UILevelUPMaterial";
#pragma endregion

#pragma region BG_FG_PARRALAX_MATERIAL
	const std::wstring ResourceMaker::BG_FOREGROUND_MATERIAL_KEY = L"BattleBGMaterialKey";
	const std::wstring ResourceMaker::BG_FOREGROUND_NORMALMAP_MATERIAL_KEY = L"BatteForegroundNoramlMapKey";
	const std::wstring ResourceMaker::BG_PARALLAX_MATERIAL_1_KEY = L"ParallaxMaterial1";
	const std::wstring ResourceMaker::BG_PARALLAX_MATERIAL_2_KEY = L"ParallaxMaterial2";
	const std::wstring ResourceMaker::BG_PARALLAX_MATERIAL_3_KEY = L"ParallaxMaterial3";
	const std::wstring ResourceMaker::BG_PARALLAX_MATERIAL_4_KEY = L"ParallaxMaterial4";
	const std::wstring ResourceMaker::BG_PARALLAX_MATERIAL_5_KEY = L"ParallaxMaterial5";
	const std::wstring ResourceMaker::BG_PARALLAX_MATERIAL_6_KEY = L"ParallaxMaterial6";
#pragma endregion

#pragma region BG_ANIMATED_OBJECT_MATERIAL
	const std::wstring ResourceMaker::BG_OBELISK_MATERIAL_KEY = L"ObeliskMaterialKey";
	const std::wstring ResourceMaker::BG_OBELISK_NORMAL_MAP_MATERIAL_KEY = L"ObeliskNormalMaterialKey";
	const std::wstring ResourceMaker::BG_MOON_MATERIAL_KEY = L"BGMoonMaterial";
	const std::wstring ResourceMaker::BG_MOON_NORMAL_MAP_MATERIAL_KEY = L"BGMoonNormalMaterial";
	const std::wstring ResourceMaker::BG_TREE_1_MATERIAL_KEY = L"BGTree1Material";
	const std::wstring ResourceMaker::BG_TREE_1_NORMAL_MAP_MATERIAL_KEY = L"BGTree1NormalMaterial";
	const std::wstring ResourceMaker::BG_TREE_2_MATERIAL_KEY = L"BGTree2Material";
	const std::wstring ResourceMaker::BG_TREE_2_NORMAL_MAP_MATERIAL_KEY = L"BGTree2NormalMaterial";
	const std::wstring ResourceMaker::BG_FLOWER_MATERIAL_KEY = L"BGFlowerMaterial";
	const std::wstring ResourceMaker::BG_FLOWER_NORMAL_MAP_MATERIAL_KEY = L"BGFlowerNormalMaterial";
	const std::wstring ResourceMaker::BG_TORCH_MATERIAL_KEY = L"BGTorchMaterial";
	const std::wstring ResourceMaker::BG_MUSHROOM_STATUE_MATERIAL_KEY = L"BGMushStatueMaterial";
	const std::wstring ResourceMaker::BG_MUSHROOM_STATUE_NORMAL_MAP_MATERIAL_KEY = L"BGMushStatueNormalMaterial";
	const std::wstring ResourceMaker::BG_FOREGROUND_GRASS_MATERIAL_KEY = L"BGForeGrassMaterial";
	const std::wstring ResourceMaker::BG_LARGE_LIGHTNING_MATERIAL_KEY = L"BGLargeLightningMaterial";
	const std::wstring ResourceMaker::BG_LARGE_LIGHTNING_NORMAL_MAP_MATERIAL_KEY = L"BGLargeLightningNormalMaterial";
	const std::wstring ResourceMaker::BG_SMALL_LIGHTNING_MATERIAL_KEY = L"BGSmallLightningMaterial";
	const std::wstring ResourceMaker::BG_SMALL_LIGHTNING_NORMAL_MAP_MATERIAL_KEY = L"BGSmallLightningNormalMaterial";
#pragma endregion

#pragma region EFFECT_MATERIAL
	const std::wstring ResourceMaker::EFFECT_HIT_MATERIAL_KEY = L"HitEffectMaterialKey";
	const std::wstring ResourceMaker::EFFECT_PLAYER_DASH_MATERIAL_KEY = L"PlayerDashEffectMaterialKey";
	const std::wstring ResourceMaker::EFFECT_GREEN_PORTAL_MATERIAL_KEY = L"GreenPortalMaterialKey";
	const std::wstring ResourceMaker::EFFECT_GREEN_PORTAL_NORMAL_MAP_MATERIAL_KEY = L"GreenPortalNormalMaterialKey";
	const std::wstring ResourceMaker::EFFECT_PLAYER_LEVEL_UP_MATERIAL_KEY = L"LevelUpMaterialKey";
#pragma endregion

#pragma region PROTECT_CRYSTAL
	const std::wstring ResourceMaker::PROTECT_CRYSTAL_MATERIAL_KEY = L"ProtectCryMaterial";
#pragma endregion

#pragma region OTHER
	const std::wstring ResourceMaker::DEBUG_MATERIAL_KEY = L"DebugMaterialKey";
	const std::wstring ResourceMaker::BRIK_MATERIAL_KEY = L"BrickMaterialKey";
	const std::wstring ResourceMaker::BRIK_NOT_NORMAL_MATERIAL_KEY = L"BrickNotNormalMaterialKey";
#pragma endregion


#pragma endregion
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
#pragma region CREATE
	void ResourceMaker::createMeshs()
	{
#pragma region INDEX
		std::vector<UINT> rectIndexes;
		rectIndexes.reserve(6);

		rectIndexes.push_back(0);
		rectIndexes.push_back(1);
		rectIndexes.push_back(2);
		rectIndexes.push_back(0);
		rectIndexes.push_back(3);
		rectIndexes.push_back(2);
#pragma endregion

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
		mNormalMapVertex[1].Position = Vector3(-0.5f, 0.5f, 0.0f);
		mNormalMapVertex[2].Position = Vector3(0.5f, 0.5f, 0.0f);
		mNormalMapVertex[3].Position = Vector3(0.5f, -0.5f, 0.0f);

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

#pragma region BG_MESH
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

#pragma region UI_LEVEL_UP
		//Mesh* pUILevelUpMesh = new Mesh();
		//mVertices[0] = { {-0.5f,		0.5f,		0.0f},	{0.0f, 0.0f} };
		//mVertices[1] = { {0.5f,			0.5f,		0.0f},	{1.0f, 0.0f} };
		//mVertices[2] = { {0.5f,			-0.5f,		0.0f},	{1.0f, 1.0f} };
		//mVertices[3] = { {-0.5f,		-0.5f,		0.0f},	{0.0f, 1.0f} };
		//pRectMesh->CreateVertexBuffer(mVertices, sizeof(Vertex) * RECT_VERTEX_COUNT);
		//pRectMesh->CreateIndexBuffer(rectIndexes.data(), static_cast<UINT>(rectIndexes.size()));
		//ResourcesManager::Insert<Mesh>(UI_LEVEL_UP_MESH_KEY, pUILevelUpMesh);

#pragma endregion

	}

	void ResourceMaker::createShaders()
	{

		loadAndInsertShader(SPRITE_SHADER_KEY, L"jhSpriteVS.hlsl", L"jhSpritePS.hlsl");
		loadAndInsertShader(BG_NO_LIGHTING_SHADER_KEY, L"jhBackGroundVS.hlsl", L"jhBackGroundPS.hlsl");
		loadAndInsertShader(UI_HP_SHADER_KEY, L"jhUserInterfaceVS.hlsl", L"jhUserInterfaceHealthPS.hlsl");
		loadAndInsertShader(UI_STAMINA_SHADER_KEY, L"jhUserInterfaceVS.hlsl", L"jhUserIntefaceStaminaPS.hlsl");
		loadAndInsertShader(UI_EXP_SHADER_KEY, L"jhUserInterfaceVS.hlsl", L"jhUserInterfaceExpPS.hlsl");
		loadAndInsertShader(UI_MONSTER_HP_SHADER_KEY, L"jhUserInterfaceVS.hlsl", L"jhUserInterfaceMonsterHealthPS.hlsl");
		loadAndInsertShader(UI_BOSS_MONSTER_HP_SHADER_KEY, L"jhUserInterfaceVS.hlsl", L"jhBackGroundPS.hlsl");
		loadAndInsertShader(UI_LEVEL_UP_SHADER_KEY, L"jhLevelUpVS.hlsl", L"jhLevelUpPS.hlsl");


		Shader* pNormalMapSpriteShader = new NormalMapShader();
		pNormalMapSpriteShader->CreateShaders(L"jhNormalMapSpriteVS.hlsl", L"jhNormalMapSpritePS.hlsl");
		ResourcesManager::Insert<Shader>(NORMAL_MAP_SPRITE_SHADER_KEY, pNormalMapSpriteShader);

		Shader* pDebugShader = new Shader();
		pDebugShader->CreateShaders(L"DebugVS.hlsl", L"DebugPS.hlsl");
		pDebugShader->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		ResourcesManager::Insert<Shader>(DEBUG_SHADER_KEY, pDebugShader);
	}

	void ResourceMaker::createTextures()
	{
#pragma region TEXTURE
#pragma region PLAYER
		loadAndInsertTexture(PLAYER_TEXTURE_ATLAS_KEY, L"PLAYER_SpriteSheet_90x37.png");
		loadAndInsertTexture(PLAYER_NORMAL_MAP_TEXTURE_ATLAS_KEY, L"PLAYER_SpriteSheet_90x37_NM.png");
#pragma endregion

#pragma region MONSTER
		loadAndInsertTexture(MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY, L"MON_CagedShocker_110x42.png");
		loadAndInsertTexture(MONSTER_TEXTURE_CAGED_SHOKER_NORMAL_MAP_KEY, L"MON_CagedShocker_110x42_NM.png");
		loadAndInsertTexture(MONSTER_TEXTURE_SWEEPER_ATLAS_KEY, L"MON_Sweeper_88x30.png");
		loadAndInsertTexture(MONSTER_TEXTURE_SWEEPER_NORMAL_MAP_KEY, L"MON_Sweeper_88x30_NM.png");
		loadAndInsertTexture(MONSTER_TEXTURE_WARDEN_ATLAS_KEY, L"MON_Warden_97x32.png");
		loadAndInsertTexture(MONSTER_TEXTURE_WARDEN_NORMAL_MAP_KEY, L"MON_Warden_97x32_NM.png");
		loadAndInsertTexture(MONSTER_TEXTURE_ZOMBIE_KEY, L"MON_Zombie_130x70.png");
		loadAndInsertTexture(MONSTER_TEXTURE_ZOMBIE_NORMAL_MAP_KEY, L"MON_Zombie_130x70_NM.png");
		loadAndInsertTexture(MONSTER_TEXTURE_HEABY_SLICER_KEY, L"MON_HeabySlicer_192x70.png");
		loadAndInsertTexture(MONSTER_TEXTURE_HEABY_SLICER_NORMAL_MAP_KEY, L"MON_HeabySlicer_192x70_NM.png");
		loadAndInsertTexture(MONSTER_TEXTURE_LIGHT_SLICER_KEY, L"MON_LightSlicer_192x32.png");
		loadAndInsertTexture(MONSTER_TEXTURE_LIGHT_SLICER_NORMAL_MAP_KEY, L"MON_LightSlicer_192x32_NM.png");
		loadAndInsertTexture(MONSTER_TEXTURE_DAGGER_KEY, L"MON_Dagger_144x80.png");
		loadAndInsertTexture(MONSTER_TEXTURE_DAGGER_NORMAL_MAP_KEY, L"MON_Dagger_144x80_NM.png");
		loadAndInsertTexture(MONSTER_TEXTURE_ARCHER_KEY, L"MON_Archer_174x25.png");
		loadAndInsertTexture(MONSTER_TEXTURE_ARCHER_NORMAL_MAP_KEY, L"MON_Archer_174x25_NM.png");
		loadAndInsertTexture(MONSTER_TEXTURE_BLASTER_KEY, L"MON_Blaster_119x34.png");
		loadAndInsertTexture(MONSTER_TEXTURE_ACIENT_BOSS_KEY, L"MON_AcientBoss_201x94.png");
#pragma endregion

#pragma region SKILL
		loadAndInsertTexture(SKILL_TEXTURE_ELECTRIC_BEAM_KEY, L"SKILL_ElectricBeam_375x64.png");
		loadAndInsertTexture(SKILL_TEXTURE_ELECTRIC_STRIKE_KEY, L"SKILL_ElectricStrike_80x176.png");
		loadAndInsertTexture(SKILL_TEXTURE_ELECTRIC_TORNADO_KEY, L"SKILL_ElectricTornado_64x64.png");
		loadAndInsertTexture(SKILL_SELECT_BOX_TEXTURE_KEY, L"SKILL_SELECT_BOX.png");
#pragma endregion

#pragma region SKILL_ICON
		loadAndInsertTexture(SKILL_ICON_TEXTURE_ELECTRIC_BEAM_KEY, L"SKILL_ICON_Beam.png");
		loadAndInsertTexture(SKILL_ICON_TEXTURE_ELECTRIC_STRIKE_KEY, L"SKILL_ICON_Strike.png");
		loadAndInsertTexture(SKILL_ICON_TEXTURE_ELECTRIC_TORNADO_KEY, L"SKILL_ICON_Tornado.png");
		loadAndInsertTexture(SKILL_ICON_TEXTURE_MELLE_ATTACK_KEY, L"SKILL_ICON_MelleAttack.png");
		loadAndInsertTexture(SKILL_ICON_TEXTURE_SPEED_KEY, L"SKILL_ICON_Speed.png");
		loadAndInsertTexture(SKILL_ICON_TEXTURE_HEALTH_KEY, L"SKILL_ICON_Health.png");
#pragma endregion

#pragma region SKILL_TEXT
		loadAndInsertTexture(SKILL_TEXT_TEXTURE_ELECTRIC_BEAM_LV_1_KEY, L"SKILL_MESSAGE_ElectricBeam_LV1.png");
		loadAndInsertTexture(SKILL_TEXT_TEXTURE_ELECTRIC_STRIKE_LV_1_KEY, L"SKILL_MESSAGE_ElectricStrike_LV1.png");
		loadAndInsertTexture(SKILL_TEXT_TEXTURE_ELECTRIC_TORANDO_LV_1_KEY, L"SKILL_MESSAGE_ElectricTornado_LV1.png");
		loadAndInsertTexture(SKILL_TEXT_TEXTURE_ELECTRIC_DAMAGE_INCREASE_KEY, L"SKILL_MESSAGE_ElectricDamage.png");
		loadAndInsertTexture(SKILL_TEXT_TEXTURE_ELECTRIC_SPAWN_SPEED_KEY, L"SKILL_MESSAGE_ElectricSpawnSpeed.png");
		loadAndInsertTexture(SKILL_TEXT_TEXTURE_SWORD_DAMAGE_KEY, L"SKILL_MESSAGE_SwordAttack.png");
		loadAndInsertTexture(SKILL_TEXT_TEXTURE_MOVEMENT_SPEED_KEY, L"SKILL_MESSAGE_MovementSpeed.png");
		loadAndInsertTexture(SKILL_TEXT_TEXTURE_RECOVER_HEALTH_KEY, L"SKILL_MESSAGE_RecoverHelath.png");

#pragma endregion

#pragma region EFFECT
		loadAndInsertTexture(EFFECT_GREEN_PORTAL_TEXTURE_ATLAS_KEY, L"GreenPortalSpriteSheet.png");
		loadAndInsertTexture(EFFECT_GREEN_PORTAL_NORMAL_MAP_TEXTURE_KEY, L"GreenPortalSpriteSheet_NM.png");
		loadAndInsertTexture(EFFECT_HIT_TEXTURE_ATLAS_KEY, L"EffectAtals.png");
		loadAndInsertTexture(EFFECT_PLAYER_DASH_TEXTURE_KEY, L"DASHSMOKE2.png");
		loadAndInsertTexture(EFFECT_PLAYER_LEVEL_UP_TEXTURE_KEY, L"EFFECT_Player_levelUpEffect_48x48.png");
#pragma endregion

#pragma region BG_FG_PARRLAX
		loadAndInsertTexture(BG_FOREGROUND_TEXTURE_KEY, L"ForeGround.png");
		loadAndInsertTexture(BG_FOREGROUND_NORMAL_MAP_TEXTURE_KEY, L"ForeGround_NM.png");
		loadAndInsertTexture(BG_PARALLAX_TEXTURE_1_KEY, L"parallax1.png");
		loadAndInsertTexture(BG_PARALLAX_TEXTURE_2_KEY, L"parallax2.png");
		loadAndInsertTexture(BG_PARALLAX_TEXTURE_3_KEY, L"parallax3.png");
		loadAndInsertTexture(BG_PARALLAX_TEXTURE_4_KEY, L"parallax4.png");
		//loadAndInsertTexture(BG_PARALLAX_TEXTURE_5_KEY, L"parallax5.png");
		//loadAndInsertTexture(BG_PARALLAX_TEXTURE_6_KEY, L"parallax6.png");
#pragma endregion

#pragma region BG_ANIMATED_OBJECT
		loadAndInsertTexture(BG_OBELISK_TEXTURE_ATLAS_KEY, L"ObeliskEffects.png");
		loadAndInsertTexture(BG_OBELISK_TEXTURE_NORMAL_MAP_KEY, L"ObeliskEffects_NM.png");
		loadAndInsertTexture(BG_MOON_ATLAS_TEXTURE_KEY, L"MoonSprite.png");
		loadAndInsertTexture(BG_MOON_NORMAL_MAP_TEXTURE_KEY, L"MoonSprite_NM.png");
		loadAndInsertTexture(BG_TREE_1_TEXTURE_KEY, L"BG_Tree_1_112x128.png");
		loadAndInsertTexture(BG_TREE_1_NORMAL_MAP_TEXTURE_KEY, L"BG_Tree_1_112x128_NM.png");
		loadAndInsertTexture(BG_TREE_2_TEXTURE_KEY, L"BG_Tree_2_128x96.png");
		loadAndInsertTexture(BG_TREE_2_NORMAL_MAP_TEXTURE_KEY, L"BG_Tree_2_128x96_NM.png");
		loadAndInsertTexture(BG_FLOWER_TEXTURE_KEY, L"BG_Flower_16x16.png");
		loadAndInsertTexture(BG_FLOWER_NORMAL_MAP_TEXTURE_KEY, L"BG_Flower_16x16_NM.png");
		loadAndInsertTexture(BG_TORCH_TEXTURE_KEY, L"BG_Torch_16x16.png");
		loadAndInsertTexture(BG_MUSHROOM_STATUE_TEXTURE_KEY, L"BG_MushRoomStatue_192x192.png");
		loadAndInsertTexture(BG_MUSHROOM_STATUE_NORMAL_MAP_TEXTURE_KEY, L"BG_MushRoomStatue_192x192_NM.png");
		loadAndInsertTexture(BG_FOREGROUND_GRASS_TEXTURE_KEY, L"BG_FOREGROUND_Grass_212x11.png");
		loadAndInsertTexture(BG_LARGE_LIGHTNING_TEXTURE_KEY, L"BG_Large_Lightning_64x48.png");
		loadAndInsertTexture(BG_LARGE_LIGHTNING_NORMAL_MAP_TEXTURE_KEY, L"BG_Large_Lightning_64x48_NM.png");
		loadAndInsertTexture(BG_SMALL_LIGHTNING_TEXTURE_KEY, L"BG_SmallLightning_32x32.png");
		loadAndInsertTexture(BG_SMALL_LIGHTNING_NORMAL_MAP_TEXTURE_KEY, L"BG_SmallLightning_32x32_NM.png");
#pragma endregion

#pragma region UI
		loadAndInsertTexture(UI_HP_BORDER_TEXTURE_KEY, L"UI_Border.png");
		loadAndInsertTexture(UI_HP_BAR_TEXTURE_KEY, L"UI_Player_HpBar.png");
		loadAndInsertTexture(UI_EXP_BAR_TEXTURE_KEY, L"UI_Player_ExpBar.png");
		loadAndInsertTexture(UI_STAMINA_BAR_TEXTURE_KEY, L"UI_Player_StaminarBar.png");
		loadAndInsertTexture(UI_MONSTER_HP_BAR_TEXTURE_KEY, L"UI_MON_HpBar.png");
		loadAndInsertTexture(UI_MONSTER_HP_CIRCLE_TEXTURE_KEY, L"UI_MON_Circle_64x64.png");
		loadAndInsertTexture(UI_TEXTURE_LEVEL_UP_BORDER_KEY, L"UI_Level_UP_Border_256x256.png");
#pragma endregion

#pragma region PROTECT_CRYSTAL
		loadAndInsertTexture(PROTECT_CRYSTAL_TEXTURE_KEY, L"PROTECT_Object_64x64.png");
#pragma endregion

#pragma region OTHER
		loadAndInsertTexture(BRIK_DIFFUSE_TEXTURE_KEY, L"brickwall.jpg");
		loadAndInsertTexture(BRIK_NORMAL_MAP_TEXTURE_KEY, L"brickwall_normal.jpg");
#pragma endregion
#pragma endregion
	}

	void ResourceMaker::createMaterial()
	{
#pragma region MATERIAL
#pragma region PLAYER
		insertMaterial(PLAYER_MATERIAL_KEY, SPRITE_SHADER_KEY, PLAYER_TEXTURE_ATLAS_KEY);
		insertNormalMapMaterial(PLAYER_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, PLAYER_TEXTURE_ATLAS_KEY, PLAYER_NORMAL_MAP_TEXTURE_ATLAS_KEY);
#pragma endregion

#pragma region MONSTER
		insertMaterial(MONSTER_CAGED_SHOKER_MATERIAL_KEY, SPRITE_SHADER_KEY, MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY);
		insertNormalMapMaterial(MONSTER_CAGED_SHOKER_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY, MONSTER_TEXTURE_CAGED_SHOKER_NORMAL_MAP_KEY);
		
		insertMaterial(MONSTER_SWEEPER_MATERIAL_KEY, SPRITE_SHADER_KEY, MONSTER_TEXTURE_SWEEPER_ATLAS_KEY);
		insertNormalMapMaterial(MONSTER_SWEEPER_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, MONSTER_TEXTURE_SWEEPER_ATLAS_KEY, MONSTER_TEXTURE_SWEEPER_NORMAL_MAP_KEY);
		
		insertMaterial(MONSTER_WARDEN_MATERIAL_KEY, SPRITE_SHADER_KEY, MONSTER_TEXTURE_WARDEN_ATLAS_KEY);
		insertNormalMapMaterial(MONSTER_WARDEN_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, MONSTER_TEXTURE_WARDEN_ATLAS_KEY, MONSTER_TEXTURE_WARDEN_NORMAL_MAP_KEY);
		
		insertMaterial(MONSTER_ZOMBIE_MATERIAL_KEY, SPRITE_SHADER_KEY, MONSTER_TEXTURE_ZOMBIE_KEY);
		insertNormalMapMaterial(MONSTER_ZOMBIE_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, MONSTER_TEXTURE_ZOMBIE_KEY, MONSTER_TEXTURE_ZOMBIE_NORMAL_MAP_KEY);
		
		insertMaterial(MONSTER_HEABY_SLICER_MATERIAL_KEY, SPRITE_SHADER_KEY, MONSTER_TEXTURE_HEABY_SLICER_KEY);
		insertNormalMapMaterial(MONSTER_HEABY_SLICER_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, MONSTER_TEXTURE_HEABY_SLICER_KEY, MONSTER_TEXTURE_HEABY_SLICER_NORMAL_MAP_KEY);
		
		insertMaterial(MONSTER_LIGHT_SLICER_MATERIAL_KEY, SPRITE_SHADER_KEY, MONSTER_TEXTURE_LIGHT_SLICER_KEY);
		insertNormalMapMaterial(MONSTER_LIGHT_SLICER_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, MONSTER_TEXTURE_LIGHT_SLICER_KEY, MONSTER_TEXTURE_LIGHT_SLICER_NORMAL_MAP_KEY);
		
		insertMaterial(MONSTER_DAGGER_MATERIAL_KEY, SPRITE_SHADER_KEY, MONSTER_TEXTURE_DAGGER_KEY);
		insertNormalMapMaterial(MONSTER_DAGGER_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, MONSTER_TEXTURE_DAGGER_KEY, MONSTER_TEXTURE_DAGGER_NORMAL_MAP_KEY);
		
		insertMaterial(MONSTER_ARCHER_MATERIAL_KEY, SPRITE_SHADER_KEY, MONSTER_TEXTURE_ARCHER_KEY);
		insertNormalMapMaterial(MONSTER_ARCHER_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, MONSTER_TEXTURE_ARCHER_KEY, MONSTER_TEXTURE_ARCHER_NORMAL_MAP_KEY);
		
		insertMaterial(MONSTER_BLASTER_MATERIAL_KEY, SPRITE_SHADER_KEY, MONSTER_TEXTURE_BLASTER_KEY);
		
		insertMaterial(MONSTER_ACIENT_BOSS_MATERIAL_KEY, SPRITE_SHADER_KEY, MONSTER_TEXTURE_ACIENT_BOSS_KEY);

#pragma endregion

#pragma region SKILL
		insertMaterial(SKILL_MATERIAL_ELECTRIC_BEAM_KEY, SPRITE_SHADER_KEY, SKILL_TEXTURE_ELECTRIC_BEAM_KEY);
		insertMaterial(SKILL_MATERIAL_ELECTRIC_STRIKE_KEY, SPRITE_SHADER_KEY, SKILL_TEXTURE_ELECTRIC_STRIKE_KEY);
		insertMaterial(SKILL_MATERIAL_ELECTRIC_TORNADO_KEY, SPRITE_SHADER_KEY, SKILL_TEXTURE_ELECTRIC_TORNADO_KEY);
		insertMaterial(SKILL_SELECT_BOX_MATERIAL_KEY, SPRITE_SHADER_KEY, SKILL_SELECT_BOX_TEXTURE_KEY);
#pragma endregion

#pragma region SKILL_ICON
		insertMaterial(SKILL_ICON_MATERIAL_ELECTRIC_BEAM_KEY, SPRITE_SHADER_KEY, SKILL_ICON_TEXTURE_ELECTRIC_BEAM_KEY);
		insertMaterial(SKILL_ICON_MATERIAL_ELECTRIC_STRIKE_KEY, SPRITE_SHADER_KEY, SKILL_ICON_TEXTURE_ELECTRIC_STRIKE_KEY);
		insertMaterial(SKILL_ICON_MATERIAL_ELECTRIC_TORNADO_KEY, SPRITE_SHADER_KEY, SKILL_ICON_TEXTURE_ELECTRIC_TORNADO_KEY);
		insertMaterial(SKILL_ICON_MATERIAL_MELLE_ATTACK_KEY, SPRITE_SHADER_KEY, SKILL_ICON_TEXTURE_MELLE_ATTACK_KEY);
		insertMaterial(SKILL_ICON_MATERIAL_SPEED_KEY, SPRITE_SHADER_KEY, SKILL_ICON_TEXTURE_SPEED_KEY);
		insertMaterial(SKILL_ICON_MATERIAL_HEALTH_KEY, SPRITE_SHADER_KEY, SKILL_ICON_TEXTURE_HEALTH_KEY);

#pragma endregion

#pragma region SKILL_TEXT
		insertMaterial(SKILL_TEXT_MATERIAL_ELECTRIC_BEAM_LV_1_KEY, SPRITE_SHADER_KEY, SKILL_TEXT_TEXTURE_ELECTRIC_BEAM_LV_1_KEY);
		insertMaterial(SKILL_TEXT_MATERIAL_ELECTRIC_STRIKE_LV_1_KEY, SPRITE_SHADER_KEY, SKILL_TEXT_TEXTURE_ELECTRIC_STRIKE_LV_1_KEY);
		insertMaterial(SKILL_TEXT_MATERIAL_ELECTRIC_TORANDO_LV_1_KEY, SPRITE_SHADER_KEY, SKILL_TEXT_TEXTURE_ELECTRIC_TORANDO_LV_1_KEY);
		insertMaterial(SKILL_TEXT_MATERIAL_ELECTRIC_DAMAGE_INCREASE_KEY, SPRITE_SHADER_KEY, SKILL_TEXT_TEXTURE_ELECTRIC_DAMAGE_INCREASE_KEY);
		insertMaterial(SKILL_TEXT_MATERIAL_ELECTRIC_SPAWN_SPEED_KEY, SPRITE_SHADER_KEY, SKILL_TEXT_TEXTURE_ELECTRIC_SPAWN_SPEED_KEY);

		insertMaterial(SKILL_TEXT_MATERIAL_MOVEMENT_SPEED_KEY, SPRITE_SHADER_KEY, SKILL_TEXT_TEXTURE_MOVEMENT_SPEED_KEY);
		insertMaterial(SKILL_TEXT_MATERIAL_SWORD_DAMAGE_KEY, SPRITE_SHADER_KEY, SKILL_TEXT_TEXTURE_SWORD_DAMAGE_KEY);
		insertMaterial(SKILL_TEXT_MATERIAL_RECOVER_HEALTH_KEY, SPRITE_SHADER_KEY, SKILL_TEXT_TEXTURE_RECOVER_HEALTH_KEY);
#pragma endregion

#pragma region BG_FG_PARRALAX
		insertMaterial(BG_FOREGROUND_MATERIAL_KEY, BG_NO_LIGHTING_SHADER_KEY, BG_FOREGROUND_TEXTURE_KEY);
		insertNormalMapMaterial(BG_FOREGROUND_NORMALMAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, BG_FOREGROUND_TEXTURE_KEY, BG_FOREGROUND_NORMAL_MAP_TEXTURE_KEY);
		insertMaterial(BG_PARALLAX_MATERIAL_1_KEY, BG_NO_LIGHTING_SHADER_KEY, BG_PARALLAX_TEXTURE_1_KEY);
		insertMaterial(BG_PARALLAX_MATERIAL_2_KEY, BG_NO_LIGHTING_SHADER_KEY, BG_PARALLAX_TEXTURE_2_KEY);
		insertMaterial(BG_PARALLAX_MATERIAL_3_KEY, BG_NO_LIGHTING_SHADER_KEY, BG_PARALLAX_TEXTURE_3_KEY);
		insertMaterial(BG_PARALLAX_MATERIAL_4_KEY, BG_NO_LIGHTING_SHADER_KEY, BG_PARALLAX_TEXTURE_4_KEY);
		//insertMaterial(BG_PARALLAX_MATERIAL_5_KEY, BG_NO_LIGHTING_SHADER_KEY, BG_PARALLAX_TEXTURE_5_KEY);
		//insertMaterial(BG_PARALLAX_MATERIAL_6_KEY, BG_NO_LIGHTING_SHADER_KEY, BG_PARALLAX_TEXTURE_6_KEY);
#pragma endregion

#pragma region BG_ANIMATED_OBJECT
		insertMaterial(BG_OBELISK_MATERIAL_KEY, SPRITE_SHADER_KEY, BG_OBELISK_TEXTURE_NORMAL_MAP_KEY);
		insertNormalMapMaterial(BG_OBELISK_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, BG_OBELISK_TEXTURE_NORMAL_MAP_KEY, BG_OBELISK_TEXTURE_NORMAL_MAP_KEY);
		insertMaterial(BG_TREE_1_MATERIAL_KEY, SPRITE_SHADER_KEY, BG_TREE_1_TEXTURE_KEY);
		insertNormalMapMaterial(BG_TREE_1_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, BG_TREE_1_TEXTURE_KEY, BG_TREE_1_NORMAL_MAP_TEXTURE_KEY);
		insertMaterial(BG_TREE_2_MATERIAL_KEY, SPRITE_SHADER_KEY, BG_TREE_2_TEXTURE_KEY);
		insertNormalMapMaterial(BG_TREE_2_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, BG_TREE_2_TEXTURE_KEY, BG_TREE_2_NORMAL_MAP_TEXTURE_KEY);
		insertMaterial(BG_FLOWER_MATERIAL_KEY, SPRITE_SHADER_KEY, BG_FLOWER_TEXTURE_KEY);
		insertNormalMapMaterial(BG_FLOWER_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, BG_FLOWER_TEXTURE_KEY, BG_FLOWER_NORMAL_MAP_TEXTURE_KEY);
		insertMaterial(BG_TORCH_MATERIAL_KEY, SPRITE_SHADER_KEY, BG_TORCH_TEXTURE_KEY);
		insertMaterial(BG_MUSHROOM_STATUE_MATERIAL_KEY, SPRITE_SHADER_KEY, BG_MUSHROOM_STATUE_TEXTURE_KEY);
		insertNormalMapMaterial(BG_MUSHROOM_STATUE_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, BG_MUSHROOM_STATUE_TEXTURE_KEY, BG_MUSHROOM_STATUE_NORMAL_MAP_TEXTURE_KEY);
		insertMaterial(BG_FOREGROUND_GRASS_MATERIAL_KEY, SPRITE_SHADER_KEY, BG_FOREGROUND_GRASS_TEXTURE_KEY);
		insertMaterial(BG_LARGE_LIGHTNING_MATERIAL_KEY, SPRITE_SHADER_KEY, BG_LARGE_LIGHTNING_TEXTURE_KEY);
		insertNormalMapMaterial(BG_LARGE_LIGHTNING_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, BG_LARGE_LIGHTNING_TEXTURE_KEY, BG_LARGE_LIGHTNING_NORMAL_MAP_TEXTURE_KEY);
		insertMaterial(BG_SMALL_LIGHTNING_MATERIAL_KEY, SPRITE_SHADER_KEY, BG_SMALL_LIGHTNING_TEXTURE_KEY);
		insertNormalMapMaterial(BG_SMALL_LIGHTNING_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, BG_SMALL_LIGHTNING_TEXTURE_KEY, BG_SMALL_LIGHTNING_NORMAL_MAP_TEXTURE_KEY);
		insertMaterial(BG_MOON_MATERIAL_KEY, SPRITE_SHADER_KEY, BG_MOON_ATLAS_TEXTURE_KEY);
		insertNormalMapMaterial(BG_MOON_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, BG_MOON_ATLAS_TEXTURE_KEY, BG_MOON_NORMAL_MAP_TEXTURE_KEY);
#pragma endregion

#pragma region EFFECT
		insertMaterial(EFFECT_HIT_MATERIAL_KEY, SPRITE_SHADER_KEY, EFFECT_HIT_TEXTURE_ATLAS_KEY);
		insertMaterial(EFFECT_PLAYER_DASH_MATERIAL_KEY, SPRITE_SHADER_KEY, EFFECT_PLAYER_DASH_TEXTURE_KEY);
		insertMaterial(EFFECT_GREEN_PORTAL_MATERIAL_KEY, SPRITE_SHADER_KEY, EFFECT_GREEN_PORTAL_TEXTURE_ATLAS_KEY);
		insertMaterial(EFFECT_PLAYER_LEVEL_UP_MATERIAL_KEY, SPRITE_SHADER_KEY, EFFECT_PLAYER_LEVEL_UP_TEXTURE_KEY);
		insertNormalMapMaterial(EFFECT_GREEN_PORTAL_NORMAL_MAP_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, EFFECT_GREEN_PORTAL_TEXTURE_ATLAS_KEY, EFFECT_GREEN_PORTAL_NORMAL_MAP_TEXTURE_KEY);
#pragma endregion

#pragma region UI
		insertMaterial(UI_HP_BORDER_MATERIAL_KEY, BG_NO_LIGHTING_SHADER_KEY, UI_HP_BORDER_TEXTURE_KEY);
		insertMaterial(UI_HP_BAR_MATERIAL_KEY, UI_HP_SHADER_KEY, UI_HP_BAR_TEXTURE_KEY);
		insertMaterial(UI_EXP_BAR_MATERIAL_KEY, UI_EXP_SHADER_KEY, UI_EXP_BAR_TEXTURE_KEY);
		insertMaterial(UI_STAMINA_BAR_MATERIAL_KEY, UI_STAMINA_SHADER_KEY, UI_STAMINA_BAR_TEXTURE_KEY);

#pragma region MONSTER_UI
		ResourcesManager::Insert<Material>(
			UI_MONSTER_HP_BAR_MATERIAL_KEY,
			new MonsterUIMaterial(
				ResourcesManager::Find<Shader>(UI_MONSTER_HP_SHADER_KEY),
				ResourcesManager::Find<Texture>(UI_MONSTER_HP_BAR_TEXTURE_KEY))
			);
#pragma endregion

		insertMaterial(UI_MONSTER_HP_CIRCLE_MATERIAL_KEY, SPRITE_SHADER_KEY, UI_MONSTER_HP_CIRCLE_TEXTURE_KEY);
		insertMaterial(UI_MATERIAL_LEVEL_UP_BORDER_KEY, SPRITE_SHADER_KEY, UI_TEXTURE_LEVEL_UP_BORDER_KEY);
#pragma endregion

#pragma region DEBUG
		Material* pDebugMaterial = new Material(ResourcesManager::Find<Shader>(DEBUG_SHADER_KEY), nullptr);
		ResourcesManager::Insert<Material>(DEBUG_MATERIAL_KEY, pDebugMaterial);
#pragma endregion

#pragma region PROTECT_CRYSTAL
		insertMaterial(PROTECT_CRYSTAL_MATERIAL_KEY, SPRITE_SHADER_KEY, PROTECT_CRYSTAL_TEXTURE_KEY);
#pragma endregion

#pragma region OTHER
		insertMaterial(BRIK_NOT_NORMAL_MATERIAL_KEY, SPRITE_SHADER_KEY, BRIK_DIFFUSE_TEXTURE_KEY);
		insertNormalMapMaterial(BRIK_MATERIAL_KEY, NORMAL_MAP_SPRITE_SHADER_KEY, BRIK_DIFFUSE_TEXTURE_KEY, BRIK_NORMAL_MAP_TEXTURE_KEY);

#pragma endregion
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

	void ResourceMaker::createConstantBuffer()
	{
		mspTransformConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::TRANSFORM);
		mspAnimationConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::ANIMATION);
		mspUVTranslationConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::UV_TRANSLATION);
		//mspColliderConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::COLLIDER_COLOR);
		mspUIBarConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::UI_BAR);
	}
#pragma endregion

#pragma region SET
	void ResourceMaker::setSamplerState()
	{
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetSamplers(POINT_BORDER_SAMPLER_SLOT_NUMBER, 1, mcpPointBorderSampler.GetAddressOf());
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetSamplers(POINT_BORDER_SAMPLER_SLOT_NUMBER, 1, mcpPointBorderSampler.GetAddressOf());

		//graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetSamplers(POINT_WRAP_SAMPLER_SLOT_NUMBER, 1, mcpPointWrapSampler.GetAddressOf());
		//graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetSamplers(POINT_WRAP_SAMPLER_SLOT_NUMBER, 1, mcpPointWrapSampler.GetAddressOf());
	}
#pragma endregion

#pragma region LOAD_INSERT
	void ResourceMaker::loadAndInsertShader(const std::wstring& key, const std::wstring& VSFileName, const std::wstring& PSFileName)
	{
		Shader* pShader = new Shader();
		assert(pShader != nullptr);
		pShader->CreateShaders(VSFileName, PSFileName);
		ResourcesManager::Insert<Shader>(key, pShader);
	}
	void ResourceMaker::loadAndInsertTexture(const std::wstring& key, const std::wstring& fileName)
	{
		Texture* pTexture = new Texture();
		assert(pTexture != nullptr);
		pTexture->Load(fileName);
		ResourcesManager::Insert<Texture>(key, pTexture);
	}
	void ResourceMaker::insertMaterial(const std::wstring& key, const std::wstring& shaderKey, const std::wstring& textureKey)
	{
		ResourcesManager::Insert<Material>(
			key,
			new Material(
				ResourcesManager::Find<Shader>(shaderKey),
				ResourcesManager::Find<Texture>(textureKey))
			);
	}
	void ResourceMaker::insertNormalMapMaterial(const std::wstring& key, const std::wstring& shaderKey, const std::wstring& textureKey, const std::wstring& normalMapKey)
	{
		ResourcesManager::Insert<Material>(
			key,
			new NormalMapMaterial(
				ResourcesManager::Find<Shader>(shaderKey),
				ResourcesManager::Find<Texture>(textureKey),
				ResourcesManager::Find<Texture>(normalMapKey))
			);
	}

#pragma endregion


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