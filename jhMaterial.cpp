#include "jhMaterial.h"
#include "jhShader.h"
#include "jhTexture.h"

static constexpr UINT DEFAULT_TEXTURE_SLOT_NUMBER = 0;

namespace jh
{
	Material::Material(Shader* pShader, Texture* pTexture)
		: mpShader(pShader)
		, mpTexture(pTexture)
	{
	}

	void Material::setPipeline()
	{
		assert(mpShader != nullptr && mpTexture != nullptr);
		mpShader->SetPipeline();
		mpTexture->SetPipeline(DEFAULT_TEXTURE_SLOT_NUMBER);
	}

	void Material::SetPipeline()
	{
		setPipeline();
	}

	void Material::Clear()
	{
		assert(mpTexture != nullptr);
		mpTexture->ClearSRV(DEFAULT_TEXTURE_SLOT_NUMBER);
	}

}