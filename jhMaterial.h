#pragma once
#include "jhResource.h"
#include "jhTexture.h"
#include "jhShader.h"

namespace jh
{
	enum class eMaterialType
	{
		NORMAL,
		DEBUG,
		SPRITE_WITH_NORMAL,
		COUNT
	};

	class Material : public Resource
	{
	public:
		Material(Shader* pShader, Texture* pTexture);
		Material(const eMaterialType eType, Shader* pShader, Texture* pTexture);
		virtual ~Material() = default;

		virtual void SetPipeline(const UINT textureSlotNumber);
		virtual void ClearPipeline(const UINT textureSlotNumber);

	public:
		static constexpr const UINT DEFAULT_TEXTURE_SLOT_NUMBER_0 = 0;
		static constexpr const UINT ATLAS_TEXTURE_SLOT_NUMBER_12 = 12;
		static constexpr const UINT NORMAL_MAP_TEXTURE_SLOT_NUMBER_11 = 11;
	protected:
		Shader*			mpShader;
		Texture*		mpTexture;
		eMaterialType	meType;
	};
}

