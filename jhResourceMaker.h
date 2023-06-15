#pragma once
#include "jhGraphicDeviceDX11.h"
#include "jhConstantBuffer.h"

constexpr const UINT RECT_VERTEX_COUNT = 4;
constexpr const UINT POINT_BORDER_SAMPLER_SLOT_NUMBER = 0;
constexpr const UINT POINT_WRAP_SAMPLER_SLOT_NUMBER = 1;


namespace jh
{
	class Texture;
	class ResourceMaker final
	{
	public:
		static ResourceMaker& GetInstance()
		{
			static ResourceMaker instance;
			return instance;
		}

		ResourceMaker(const ResourceMaker& other) = delete;
		ResourceMaker& operator=(const ResourceMaker& other) = delete;

		void Initialize();
		void Release();

		ConstantBuffer* GetTransformCBOrNull() const { return mspTransformConstantBuffer.get(); }
		ConstantBuffer* GetAnimationCBOrNull() const { return mspAnimationConstantBuffer.get(); }
		ConstantBuffer* GetUVTranslationCBOrNull() const { return mspUVTranslationConstantBuffer.get(); }
		//ConstantBuffer* GetColliderCBOrNull() const { return mspColliderConstantBuffer.get(); }
		ConstantBuffer* GetUIBarCBOrNull() const { return mspUIBarConstantBuffer.get(); }

		void PushBackDebugMesh(DebugMesh debugMesh) { mDebugMeshs.push_back(debugMesh); }
		std::vector<DebugMesh>& GetDebugMeshs() { return mDebugMeshs; }


	public:
#pragma region MESH
		static const std::wstring RECT_MESH_KEY;
		static const std::wstring RECT_NORMAL_MAP_MESH_KEY;
		static const std::wstring BATTLE_BG_MESH_KEY;
		static const std::wstring DEBUG_RECT_MESH_KEY;
		static const std::wstring UI_LEVEL_UP_MESH_KEY;
#pragma endregion
		
#pragma region SHADER
		static const std::wstring SPRITE_SHADER_KEY;
		static const std::wstring BG_NO_LIGHTING_SHADER_KEY;
		static const std::wstring DEBUG_SHADER_KEY;
		static const std::wstring UI_HP_SHADER_KEY;
		static const std::wstring UI_STAMINA_SHADER_KEY;
		static const std::wstring UI_MONSTER_HP_SHADER_KEY;
		static const std::wstring NORMAL_MAP_SPRITE_SHADER_KEY;
		static const std::wstring UI_LEVEL_UP_SHADER_KEY;
#pragma endregion

#pragma region TEXTURE
#pragma region PLAYER_TEXTURE
		static const std::wstring PLAYER_TEXTURE_ATLAS_KEY;
		static const std::wstring PLAYER_NORMAL_MAP_TEXTURE_ATLAS_KEY;
#pragma endregion

#pragma region MONSTER_TEXTURE
		static const std::wstring MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY;
		static const std::wstring MONSTER_TEXTURE_CAGED_SHOKER_NORMAL_MAP_KEY;
		static const std::wstring MONSTER_TEXTURE_SWEEPER_ATLAS_KEY;
		static const std::wstring MONSTER_TEXTURE_SWEEPER_NORMAL_MAP_KEY;
		static const std::wstring MONSTER_TEXTURE_WARDEN_ATLAS_KEY;
		static const std::wstring MONSTER_TEXTURE_WARDEN_NORMAL_MAP_KEY;
		static const std::wstring MONSTER_TEXTURE_ZOMBIE_KEY;
		static const std::wstring MONSTER_TEXTURE_ZOMBIE_NORMAL_MAP_KEY;
		static const std::wstring MONSTER_TEXTURE_HEABY_SLICER_KEY;
		static const std::wstring MONSTER_TEXTURE_HEABY_SLICER_NORMAL_MAP_KEY;
		static const std::wstring MONSTER_TEXTURE_LIGHT_SLICER_KEY;
		static const std::wstring MONSTER_TEXTURE_LIGHT_SLICER_NORMAL_MAP_KEY;
		static const std::wstring MONSTER_TEXTURE_DAGGER_KEY;
		static const std::wstring MONSTER_TEXTURE_DAGGER_NORMAL_MAP_KEY;
		static const std::wstring MONSTER_TEXTURE_ARCHER_KEY;
		static const std::wstring MONSTER_TEXTURE_ARCHER_NORMAL_MAP_KEY;
		static const std::wstring MONSTER_TEXTURE_BLASTER_KEY;
		static const std::wstring MONSTER_TEXTURE_ACIENT_BOSS_KEY;
#pragma endregion

#pragma region SKILL
		static const std::wstring SKILL_SELECT_BOX_TEXTURE_KEY;

#pragma region SKILL_ICON_TEXTURE
		static const std::wstring SKILL_TEXTURE_ELECTRIC_BEAM_KEY;
		static const std::wstring SKILL_TEXTURE_ELECTRIC_STRIKE_KEY;
		static const std::wstring SKILL_TEXTURE_ELECTRIC_TORNADO_KEY;
		static const std::wstring SKILL_ICON_TEXTURE_ELECTRIC_BEAM_KEY;
		static const std::wstring SKILL_ICON_TEXTURE_ELECTRIC_STRIKE_KEY;
		static const std::wstring SKILL_ICON_TEXTURE_ELECTRIC_TORNADO_KEY;
		static const std::wstring SKILL_ICON_TEXTURE_MELLE_ATTACK_KEY;
		static const std::wstring SKILL_ICON_TEXTURE_SPEED_KEY;
		static const std::wstring SKILL_ICON_TEXTURE_HEALTH_KEY;
#pragma endregion

#pragma region SKILL_TEXT_TEXTURE
		static const std::wstring SKILL_TEXT_TEXTURE_ELECTRIC_BEAM_LV_1_KEY;
		static const std::wstring SKILL_TEXT_TEXTURE_ELECTRIC_STRIKE_LV_1_KEY;
		static const std::wstring SKILL_TEXT_TEXTURE_ELECTRIC_TORANDO_LV_1_KEY;
		static const std::wstring SKILL_TEXT_TEXTURE_ELECTRIC_DAMAGE_INCREASE_KEY;
		static const std::wstring SKILL_TEXT_TEXTURE_ELECTRIC_SPAWN_SPEED_KEY;

		static const std::wstring SKILL_TEXT_TEXTURE_SWORD_DAMAGE_KEY;
		static const std::wstring SKILL_TEXT_TEXTURE_MOVEMENT_SPEED_KEY;
		static const std::wstring SKILL_TEXT_TEXTURE_RECOVER_HEALTH_KEY;

#pragma endregion
#pragma endregion

#pragma region BG_FG_PARRALAX_TEXTURE
		static const std::wstring BG_FOREGROUND_TEXTURE_KEY;
		static const std::wstring BG_FOREGROUND_NORMAL_MAP_TEXTURE_KEY;
		static const std::wstring BG_PARALLAX_TEXTURE_1_KEY;
		static const std::wstring BG_PARALLAX_TEXTURE_2_KEY;
		static const std::wstring BG_PARALLAX_TEXTURE_3_KEY;
		static const std::wstring BG_PARALLAX_TEXTURE_4_KEY;
		static const std::wstring BG_PARALLAX_TEXTURE_5_KEY;
		static const std::wstring BG_PARALLAX_TEXTURE_6_KEY;
#pragma endregion

#pragma region UI_TEXTURE
		static const std::wstring UI_HP_BORDER_TEXTURE_KEY;
		static const std::wstring UI_HP_BAR_TEXTURE_KEY;
		static const std::wstring UI_STAMINA_BAR_TEXTURE_KEY;
		static const std::wstring UI_MONSTER_HP_BAR_TEXTURE_KEY;
		static const std::wstring UI_MONSTER_HP_BORDER_BAR_TEXTURE_KEY;
		static const std::wstring UI_TEXTURE_LEVEL_UP_BORDER_KEY;
#pragma endregion

#pragma region EFFECT_TEXTRUE
		static const std::wstring EFFECT_HIT_TEXTURE_ATLAS_KEY;
		static const std::wstring EFFECT_GREEN_PORTAL_TEXTURE_ATLAS_KEY;
		static const std::wstring EFFECT_GREEN_PORTAL_NORMAL_MAP_TEXTURE_KEY;
		static const std::wstring EFFECT_PLAYER_DASH_TEXTURE_KEY;
#pragma endregion

#pragma region BG_ANIMATED_OBJECT_TEXTURE
		static const std::wstring BG_OBELISK_TEXTURE_ATLAS_KEY;
		static const std::wstring BG_OBELISK_TEXTURE_NORMAL_MAP_KEY;
		static const std::wstring BG_TREE_1_TEXTURE_KEY;
		static const std::wstring BG_TREE_1_NORMAL_MAP_TEXTURE_KEY;
		static const std::wstring BG_TREE_2_TEXTURE_KEY;
		static const std::wstring BG_TREE_2_NORMAL_MAP_TEXTURE_KEY;
		static const std::wstring BG_FLOWER_TEXTURE_KEY;
		static const std::wstring BG_FLOWER_NORMAL_MAP_TEXTURE_KEY;
		static const std::wstring BG_TORCH_TEXTURE_KEY;
		static const std::wstring BG_MUSHROOM_STATUE_TEXTURE_KEY;
		static const std::wstring BG_MUSHROOM_STATUE_NORMAL_MAP_TEXTURE_KEY;
		static const std::wstring BG_FOREGROUND_GRASS_TEXTURE_KEY;
		static const std::wstring BG_LARGE_LIGHTNING_TEXTURE_KEY;
		static const std::wstring BG_LARGE_LIGHTNING_NORMAL_MAP_TEXTURE_KEY;
		static const std::wstring BG_SMALL_LIGHTNING_TEXTURE_KEY;
		static const std::wstring BG_SMALL_LIGHTNING_NORMAL_MAP_TEXTURE_KEY;
#pragma endregion

#pragma region OTHER
		static const std::wstring BG_MOON_ATLAS_TEXTURE_KEY;
		static const std::wstring BG_MOON_NORMAL_MAP_TEXTURE_KEY;
		static const std::wstring BRIK_DIFFUSE_TEXTURE_KEY;
		static const std::wstring BRIK_NORMAL_MAP_TEXTURE_KEY;
#pragma endregion
#pragma endregion

#pragma region MATERIAL
#pragma region PLAYER_MATERIAL
		static const std::wstring PLAYER_MATERIAL_KEY;
		static const std::wstring PLAYER_NORMAL_MAP_MATERIAL_KEY;
#pragma endregion

#pragma region MONSTER_MATERIAL
		static const std::wstring MONSTER_CAGED_SHOKER_MATERIAL_KEY;
		static const std::wstring MONSTER_CAGED_SHOKER_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring MONSTER_SWEEPER_MATERIAL_KEY;
		static const std::wstring MONSTER_SWEEPER_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring MONSTER_WARDEN_MATERIAL_KEY;
		static const std::wstring MONSTER_WARDEN_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring MONSTER_ZOMBIE_MATERIAL_KEY;
		static const std::wstring MONSTER_ZOMBIE_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring MONSTER_HEABY_SLICER_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring MONSTER_LIGHT_SLICER_MATERIAL_KEY;
		static const std::wstring MONSTER_LIGHT_SLICER_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring MONSTER_DAGGER_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring MONSTER_ARCHER_MATERIAL_KEY;
		static const std::wstring MONSTER_ARCHER_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring MONSTER_BLASTER_MATERIAL_KEY;
		static const std::wstring MONSTER_ACIENT_BOSS_MATERIAL_KEY;
#pragma endregion

#pragma region SKILL
		static const std::wstring SKILL_SELECT_BOX_MATERIAL_KEY;

#pragma region SKILL_ICON_MATERIAL
		static const std::wstring SKILL_MATERIAL_ELECTRIC_BEAM_KEY;
		static const std::wstring SKILL_MATERIAL_ELECTRIC_STRIKE_KEY;
		static const std::wstring SKILL_MATERIAL_ELECTRIC_TORNADO_KEY;
		static const std::wstring SKILL_ICON_MATERIAL_ELECTRIC_BEAM_KEY;
		static const std::wstring SKILL_ICON_MATERIAL_ELECTRIC_STRIKE_KEY;
		static const std::wstring SKILL_ICON_MATERIAL_ELECTRIC_TORNADO_KEY;
		static const std::wstring SKILL_ICON_MATERIAL_MELLE_ATTACK_KEY;
		static const std::wstring SKILL_ICON_MATERIAL_SPEED_KEY;
		static const std::wstring SKILL_ICON_MATERIAL_HEALTH_KEY;
#pragma endregion

#pragma region SKILL_TEXT_MATERIAL
		static const std::wstring SKILL_TEXT_MATERIAL_ELECTRIC_BEAM_LV_1_KEY;
		static const std::wstring SKILL_TEXT_MATERIAL_ELECTRIC_STRIKE_LV_1_KEY;
		static const std::wstring SKILL_TEXT_MATERIAL_ELECTRIC_TORANDO_LV_1_KEY;
		static const std::wstring SKILL_TEXT_MATERIAL_ELECTRIC_DAMAGE_INCREASE_KEY;
		static const std::wstring SKILL_TEXT_MATERIAL_ELECTRIC_SPAWN_SPEED_KEY;

		static const std::wstring SKILL_TEXT_MATERIAL_SWORD_DAMAGE_KEY;
		static const std::wstring SKILL_TEXT_MATERIAL_MOVEMENT_SPEED_KEY;
		static const std::wstring SKILL_TEXT_MATERIAL_RECOVER_HEALTH_KEY;
#pragma endregion

#pragma endregion


#pragma region UI_MATERIAL
		static const std::wstring UI_HP_BORDER_MATERIAL_KEY;
		static const std::wstring UI_HP_BAR_MATERIAL_KEY;
		static const std::wstring UI_STAMINA_BAR_MATERIAL_KEY;
		static const std::wstring UI_MONSTER_HP_BAR_MATERIAL_KEY;
		static const std::wstring UI_MONSTER_BORDER_HP_BAR_MATERIAL_KEY;
		static const std::wstring UI_MONSTER_BORDER_HP_BAR_MATERIAL_KEY;
		static const std::wstring UI_MATERIAL_LEVEL_UP_BORDER_KEY;
#pragma endregion

#pragma region EFFECT_MATERIAL
		static const std::wstring EFFECT_HIT_MATERIAL_KEY;
		static const std::wstring EFFECT_GREEN_PORTAL_MATERIAL_KEY;
		static const std::wstring EFFECT_GREEN_PORTAL_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring EFFECT_PLAYER_DASH_MATERIAL_KEY;
#pragma endregion

#pragma region BG_ANIMATED_OBJECTS_MATERIAL
		static const std::wstring BG_MOON_MATERIAL_KEY;
		static const std::wstring BG_MOON_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring BG_OBELISK_MATERIAL_KEY;
		static const std::wstring BG_OBELISK_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring BG_TREE_1_MATERIAL_KEY;
		static const std::wstring BG_TREE_1_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring BG_TREE_2_MATERIAL_KEY;
		static const std::wstring BG_TREE_2_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring BG_FLOWER_MATERIAL_KEY;
		static const std::wstring BG_FLOWER_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring BG_TORCH_MATERIAL_KEY;
		static const std::wstring BG_MUSHROOM_STATUE_MATERIAL_KEY;
		static const std::wstring BG_MUSHROOM_STATUE_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring BG_FOREGROUND_GRASS_MATERIAL_KEY;
		static const std::wstring BG_LARGE_LIGHTNING_MATERIAL_KEY;
		static const std::wstring BG_LARGE_LIGHTNING_NORMAL_MAP_MATERIAL_KEY;
		static const std::wstring BG_SMALL_LIGHTNING_MATERIAL_KEY;
		static const std::wstring BG_SMALL_LIGHTNING_NORMAL_MAP_MATERIAL_KEY;

#pragma endregion

#pragma region BG_PARALLAX_MATERIAL
		static const std::wstring BG_FOREGROUND_MATERIAL_KEY;
		static const std::wstring BG_FOREGROUND_NORMALMAP_MATERIAL_KEY;
		static const std::wstring BG_PARALLAX_MATERIAL_1_KEY;
		static const std::wstring BG_PARALLAX_MATERIAL_2_KEY;
		static const std::wstring BG_PARALLAX_MATERIAL_3_KEY;
		static const std::wstring BG_PARALLAX_MATERIAL_4_KEY;
		static const std::wstring BG_PARALLAX_MATERIAL_5_KEY;
		static const std::wstring BG_PARALLAX_MATERIAL_6_KEY;
#pragma endregion



#pragma region OTHER
		static const std::wstring BRIK_MATERIAL_KEY;
		static const std::wstring BRIK_NOT_NORMAL_MATERIAL_KEY;
		static const std::wstring DEBUG_MATERIAL_KEY;
#pragma endregion


#pragma endregion

	private:
		void createMeshs();
		void createShaders();
		void createTextures();
		void createMaterial();
		void createSamplerState();
		void createConstantBuffer();

		void setSamplerState();

		void loadAndInsertShader(const std::wstring& key, const std::wstring& VSFileName, const std::wstring& PSFileName);
		void loadAndInsertTexture(const std::wstring& key, const std::wstring& fileName);
		void insertMaterial(const std::wstring& key, const std::wstring& shaderKey, const std::wstring& textureKey);
		void insertNormalMapMaterial(const std::wstring& key, const std::wstring& shaderKey, const std::wstring& textureKey, const std::wstring& normalMapKey);
	private:
		ResourceMaker()
			: mVertices{}
			, mNormalMapVertex{}
			, mcpPointBorderSampler()
			//, mcpPointWrapSampler()
			, mspTransformConstantBuffer()
			, mspAnimationConstantBuffer()
			, mspUVTranslationConstantBuffer()
			, mspColliderConstantBuffer()
			, mspUIBarConstantBuffer()
			, mDebugMeshs()
		{
			mDebugMeshs.reserve(128);
		}
		~ResourceMaker() = default;

	private:
		Vertex											mVertices[RECT_VERTEX_COUNT];
		NormalMapShaderVertex							mNormalMapVertex[RECT_VERTEX_COUNT];

		Microsoft::WRL::ComPtr<ID3D11SamplerState>		mcpPointBorderSampler;
		//Microsoft::WRL::ComPtr<ID3D11SamplerState>		mcpPointWrapSampler;

		std::unique_ptr<ConstantBuffer>					mspTransformConstantBuffer;
		std::unique_ptr<ConstantBuffer>					mspAnimationConstantBuffer;
		std::unique_ptr<ConstantBuffer>					mspUVTranslationConstantBuffer;
		std::unique_ptr<ConstantBuffer>					mspColliderConstantBuffer;
		std::unique_ptr<ConstantBuffer>					mspUIBarConstantBuffer;

		std::vector<DebugMesh>							mDebugMeshs;
	};
}