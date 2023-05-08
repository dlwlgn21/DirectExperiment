#pragma once
#include "jhGraphicDeviceDX11.h"
#include "jhConstantBuffer.h"

constexpr const UINT RECT_VERTEX_COUNT = 4;
constexpr const UINT POINT_BORDER_SAMPLER_SLOT_NUMBER = 0;
constexpr const UINT POINT_WRAP_SAMPLER_SLOT_NUMBER = 1;

namespace jh
{

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
		static const std::wstring RECT_MESH_KEY;
		static const std::wstring BATTLE_BG_MESH_KEY;
		static const std::wstring DEBUG_RECT_MESH_KEY;

		static const std::wstring SPRITE_SHADER_KEY;
		static const std::wstring BATTLE_BG_SHADER_KEY;
		static const std::wstring DEBUG_SHADER_KEY;
		static const std::wstring UI_HP_SHADER_KEY;
		static const std::wstring UI_STAMINA_SHADER_KEY;


		static const std::wstring PLAYER_TEXTURE_ATLAS_KEY;
		static const std::wstring MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY;
		static const std::wstring MONSTER_TEXTURE_SWEEPER_ATLAS_KEY;
		static const std::wstring OBELISK_TEXTURE_ATLAS_KEY;
		static const std::wstring BATTLE_BG_TEXTURE_KEY;
		static const std::wstring BATTLE_PARRARELL_BG_TEXTURE_KEY;
		static const std::wstring PARALLAX_BG_TEXTURE_1_KEY;
		static const std::wstring PARALLAX_BG_TEXTURE_2_KEY;
		static const std::wstring PARALLAX_BG_TEXTURE_3_KEY;
		static const std::wstring PARALLAX_BG_TEXTURE_4_KEY;
		static const std::wstring PARALLAX_BG_TEXTURE_5_KEY;
		static const std::wstring PARALLAX_BG_TEXTURE_6_KEY;
		static const std::wstring UI_HP_BORDER_TEXTURE_KEY;
		static const std::wstring UI_HP_BAR_TEXTURE_KEY;
		static const std::wstring UI_STAMINA_BAR_TEXTURE_KEY;
		static const std::wstring WEAPON_SWORD_TEXTURE_KEY;
		static const std::wstring EFFECT_BLOOD_TEXTURE_KEY;
		static const std::wstring BG_MOON_ATLAS_TEXTURE_KEY;
		static const std::wstring PLAYER_DASH_EFFECT_TEXTURE_KEY;

		static const std::wstring PLAYER_MATERIAL_KEY;
		static const std::wstring MONSTER_CAGED_SHOKER_MATERIAL_KEY;
		static const std::wstring MONSTER_SWEEPER_MATERIAL_KEY;
		static const std::wstring BATTLE_BG_MATERIAL_KEY;
		static const std::wstring BATTLE_PARRARELL_BG_MATERIAL_KEY;
		static const std::wstring WEAPON_SWORD_MATERIAL_KEY;
		static const std::wstring EFFECT_BLOOD_MATERIAL_KEY;
		static const std::wstring DEBUG_MATERIAL_KEY;
		static const std::wstring UI_HP_BORDER_MATERIAL_KEY;
		static const std::wstring UI_HP_BAR_MATERIAL_KEY;
		static const std::wstring UI_STAMINA_BAR_MATERIAL_KEY;
		static const std::wstring BG_MOON_MATERIAL_KEY;
		static const std::wstring PLAYER_DASH_EFFECT_MATERIAL_KEY;
		static const std::wstring OBELISK_MATERIAL_KEY;

		static const std::wstring PARALLAX_BG_MATERIAL_1_KEY;
		static const std::wstring PARALLAX_BG_MATERIAL_2_KEY;
		static const std::wstring PARALLAX_BG_MATERIAL_3_KEY;
		static const std::wstring PARALLAX_BG_MATERIAL_4_KEY;
		static const std::wstring PARALLAX_BG_MATERIAL_5_KEY;
		static const std::wstring PARALLAX_BG_MATERIAL_6_KEY;


	private:
		void createMeshs();
		void createShaders();
		void createTextures();
		void createMaterial();
		void createSamplerState();
		void createConstantBuffer();

		void setSamplerState();

	private:
		ResourceMaker()
			: mVertices{}
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