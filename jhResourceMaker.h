#pragma once
#include "jhGraphicDeviceDX11.h"
#include "jhConstantBuffer.h"

constexpr const UINT RECT_VERTEX_COUNT = 4;
constexpr const UINT POINT_WRAP_SAMPLER_SLOT_NUMBER = 0;

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

		ConstantBuffer* GetTransformCBOrNull() const		{ return mspTransformConstantBuffer.get(); }
		ConstantBuffer* GetAnimationCBOrNull() const		{ return mspAnimationConstantBuffer.get(); }
		ConstantBuffer* GetUVTranslationCBOrNull() const	{ return mspUVTranslationConstantBuffer.get(); }


	public:
		static const std::wstring RECT_MESH_KEY;
		static const std::wstring BATTLE_BG_MESH_KEY;

		static const std::wstring SPRITE_SHADER_KEY;
		static const std::wstring BATTLE_BG_SHADER_KEY;

		static const std::wstring PLAYER_TEXTURE_ATLAS_KEY;
		static const std::wstring MONSTER_TEXTURE_ATLAS_KEY;
		static const std::wstring BATTLE_BG_TEXTURE_KEY;
		static const std::wstring BATTLE_PARRARELL_BG_TEXTURE_KEY;
		static const std::wstring WEAPON_SWORD_TEXTURE_KEY;
		static const std::wstring EFFECT_SWORD_TEXTURE_KEY;

		static const std::wstring PLAYER_MATERIAL_KEY;
		static const std::wstring MONSTER_MATERIAL_KEY;
		static const std::wstring BATTLE_BG_MATERIAL_KEY;
		static const std::wstring BATTLE_PARRARELL_BG_MATERIAL_KEY;
		static const std::wstring WEAPON_SWORD_MATERIAL_KEY;
		static const std::wstring EFFECT_SWORD_MATERIAL_KEY;


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
			, mcpPointWrapSampler()
			, mspTransformConstantBuffer()
			, mspAnimationConstantBuffer()
			, mspUVTranslationConstantBuffer()
		{

		}
		~ResourceMaker() = default;

	private:
		Vertex											mVertices[RECT_VERTEX_COUNT];
		Microsoft::WRL::ComPtr<ID3D11SamplerState>		mcpPointWrapSampler;
		std::unique_ptr<ConstantBuffer>					mspTransformConstantBuffer;
		std::unique_ptr<ConstantBuffer>					mspAnimationConstantBuffer;
		std::unique_ptr<ConstantBuffer>					mspUVTranslationConstantBuffer;
	};
}

