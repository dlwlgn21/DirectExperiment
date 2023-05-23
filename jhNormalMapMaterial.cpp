#include "jhNormalMapMaterial.h"

namespace jh
{
	NormalMapMaterial::NormalMapMaterial(Shader* pShader, Texture* pAtlasTexture, Texture* pNormalMapTexture)
		: Material(eMaterialType::SPRITE_WITH_NORMAL, pShader, pAtlasTexture)
		, mpNormalMapTexture(pNormalMapTexture)
	{
		assert(mpNormalMapTexture != nullptr);
	}
	void NormalMapMaterial::SetPipeline(const UINT textureSlotNumber)
	{
		mpShader->SetPipeline();
		mpTexture->SetPipeline(textureSlotNumber);
		mpNormalMapTexture->SetPipeline(Material::NORMAL_MAP_TEXTURE_SLOT_NUMBER_11);
	}
	void NormalMapMaterial::ClearPipeline(const UINT textureSlotNumber)
	{
		mpTexture->ClearSRV(textureSlotNumber);
		mpNormalMapTexture->ClearSRV(Material::NORMAL_MAP_TEXTURE_SLOT_NUMBER_11);
	}
}