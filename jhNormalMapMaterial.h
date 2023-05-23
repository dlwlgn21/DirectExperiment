#pragma once
#include "jhMaterial.h"

namespace jh
{
	class NormalMapMaterial final : public Material
	{
	public:
		NormalMapMaterial(Shader* pShader, Texture* pAtlasTexture, Texture* pNormalMapTexture);
		virtual ~NormalMapMaterial() = default;

		void SetPipeline(const UINT textureSlotNumber) override;
		void ClearPipeline(const UINT textureSlotNumber) override;

	private:
		Texture* mpNormalMapTexture;
	};
}