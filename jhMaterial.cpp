#include "jhMaterial.h"


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
	}

	void Material::Render()
	{
	}

}