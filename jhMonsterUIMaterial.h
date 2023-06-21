#pragma once
#include "jhMaterial.h"

namespace jh
{
	class MonsterUIMaterial final : public Material
	{
	public:
		MonsterUIMaterial(Shader* pShader, Texture* pTexture);
		virtual ~MonsterUIMaterial() = default;

		void SetPipeline(const UINT textureSlotNumber) override;
		void ClearPipeline(const UINT textureSlotNumber) override;
	};
}
