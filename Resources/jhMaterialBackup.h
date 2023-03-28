#pragma once
#include "jhResource.h"
#include "jhRenderer.h"

using namespace jh::graphics;
using namespace jh::renderer;

namespace jh
{
	class Texture;
	class Shader;

	// AddedPart At 0327
	// class PaintShader;

	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

		HRESULT Load(const std::wstring& path) override;

		void SetDataAtConstantBuffer(const eGPUPrameterType eGPUParamType, void* pData);
		void BindConstantBufferAndShaderAndSetTextureSRVAtShader();
		void Clear();

		__forceinline void SetShader(Shader* pShader)				{ assert(pShader != nullptr); mpShader = pShader; }
		__forceinline Shader* GetShader() const						{ return mpShader; }
		__forceinline void SetTexture(Texture* pTexture)			{ assert(pTexture != nullptr); mpTexture = pTexture; }
		__forceinline Texture* GetTexture() const					{ return mpTexture; }

		eRenderingMode GetRenderingMode() const						{ return meRenderingMode; }
		void SetRenderingMode(const eRenderingMode eRenderingMode)	{ meRenderingMode = eRenderingMode; }


		// AddedPart At 0327
		// void SetComputeShader(PaintShader* pComputeShader) { assert(pComputeShader != nullptr); mpComputeShader = static_cast<PaintShader*>(pComputeShader); }

	private:
		Shader* mpShader;
		Texture* mpTexture;
		renderer::MaterialConstantBuffer mMaterialConstantBuffer;
		eRenderingMode meRenderingMode;


		// AddedPart At 0327
		//PaintShader* mpComputeShader;
		//float mAccum;
	};
}

