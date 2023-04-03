#pragma once
#include "jhGraphicDeviceDX11.h"
#include "jhConstantBuffer.h"

constexpr const UINT RECT_VERTEX_COUNT = 4;
constexpr const UINT POINT_SAMPLER_SLOT_NUMBER = 0;

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

	public:
		static const std::wstring RECT_MESH_KEY;

		static const std::wstring SPRITE_SHADER_KEY;

		static const std::wstring LOGO_TEXTURE_KEY;

		static const std::wstring LOGO_MATERIAL_KEY;


	private:
		void createMeshs();
		void createShaders();
		void createTextures();
		void createMaterial();
		void createSamplerState();
		void createConstantBuffer();


	private:
		ResourceMaker()
			: mVertices{}
			, mcpPointSampler()
			, mspTransformConstantBuffer()
		{

		}
		~ResourceMaker() = default;

	private:
		Vertex											mVertices[RECT_VERTEX_COUNT];
		Microsoft::WRL::ComPtr<ID3D11SamplerState>		mcpPointSampler;
		std::unique_ptr<ConstantBuffer>					mspTransformConstantBuffer;
	};
}

