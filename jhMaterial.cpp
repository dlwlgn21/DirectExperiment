#include "jhMaterial.h"


namespace jh
{
	Material::Material(Shader* pShader, Texture* pTexture)
		: Resource(eReousrceType::MATERIAL)
		, mpShader(pShader)
		, mpTexture(pTexture)
		, meType(eMaterialType::NORMAL)
	{
		if (pTexture == nullptr)
		{
			meType = eMaterialType::DEBUG;
		}
	}

	Material::Material(const eMaterialType eType, Shader* pShader, Texture* pTexture)
		: Resource(eReousrceType::MATERIAL)
		, mpShader(pShader)
		, mpTexture(pTexture)
		, meType(eType)
	{
	}

	void Material::SetPipeline(const UINT textureSlotNumber)
	{
		assert(mpShader != nullptr);
		mpShader->SetPipeline();
		if (meType == eMaterialType::NORMAL)
		{
			mpTexture->SetPipeline(textureSlotNumber);
		}
	}

	void Material::ClearPipeline(const UINT textureSlotNumber)
	{
		if (meType == eMaterialType::NORMAL)
		{
			mpTexture->ClearSRV(textureSlotNumber);
		}
	}

}