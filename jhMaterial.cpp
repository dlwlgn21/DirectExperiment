#include "jhMaterial.h"
#include "jhTexture.h"
#include "jhShader.h"



namespace jh
{
	Material::Material(Shader* pShader, Texture* pTexture)
		: Resource(eReousrceType::MATERIAL)
		, mpShader(pShader)
		, mpTexture(pTexture)
	{
	}

	void Material::SetPipeline(const UINT textureSlotNumber)
	{
		setPipeline(textureSlotNumber);
	}

	void Material::setPipeline(const UINT textureSlotNumber)
	{
		assert(mpShader != nullptr && mpTexture != nullptr);
		mpShader->SetPipeline();
		mpTexture->SetPipeline(textureSlotNumber);
	}

	void Material::ClearPipeline(const UINT textureSlotNumber)
	{
		assert(mpTexture != nullptr);
		mpTexture->ClearSRV(textureSlotNumber);
	}

}