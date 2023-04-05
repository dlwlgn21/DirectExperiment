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

		void SetPipeline();
		void ClearPipeline();
	private:
		void setPipeline();
	private:
		Shader*		mpShader;
		Texture*	mpTexture;
	};
}

