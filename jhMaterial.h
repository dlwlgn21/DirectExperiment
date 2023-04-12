#pragma once
#include "jhResource.h"

namespace jh
{
	class Shader;
	class Texture;
	class Material final : public Resource
	{
	public:
		Material(Shader* pShader, Texture* pTexture);
		virtual ~Material() = default;

		void SetPipeline(const UINT textureSlotNumber);
		void ClearPipeline(const UINT textureSlotNumber);
	private:
		void setPipeline(const UINT textureSlotNumber);


	public:
		static constexpr const UINT DEFAULT_TEXTURE_SLOT_NUMBER_0 = 0;
		static constexpr const UINT ATLAS_TEXTURE_SLOT_NUMBER_12 = 12;

	private:
		Shader*		mpShader;
		Texture*	mpTexture;
	};
}

