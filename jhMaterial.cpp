#include "jhMaterial.h"
#include "jhTexture.h"
#include "jhShader.h"


static constexpr const UINT DEFAULT_TEXTURE_SLOT_NUMBER_0 = 0;

namespace jh
{
	Material::Material(Shader* pShader, Texture* pTexture)
		: Resource(eReousrceType::MATERIAL)
		, mpShader(pShader)
		, mpTexture(pTexture)
	{
	}

	void Material::setPipeline()
	{
		assert(mpShader != nullptr && mpTexture != nullptr);
		mpShader->SetPipeline();
		mpTexture->SetPipeline(DEFAULT_TEXTURE_SLOT_NUMBER_0);
	}

	void Material::SetPipeline()
	{
		setPipeline();
	}

	void Material::ClearPipeline()
	{
		assert(mpTexture != nullptr);
		mpTexture->ClearSRV(DEFAULT_TEXTURE_SLOT_NUMBER_0);
	}

}