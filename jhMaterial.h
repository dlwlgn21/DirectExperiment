#pragma once
#include "jhEngine.h"

namespace jh
{
	class Shader;
	class Texture;
	class Material final
	{
	public:
		Material(Shader* pShader, Texture* pTexture);
		~Material() = default;
		void Render();

	private:
		void setPipeline();
	private:
		Shader*		mpShader;
		Texture*	mpTexture;
	};
}

