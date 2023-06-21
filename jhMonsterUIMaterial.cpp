#include "jhMonsterUIMaterial.h"

namespace jh
{
	MonsterUIMaterial::MonsterUIMaterial(Shader* pShader, Texture* pTexture)
		: Material(pShader, pTexture)
	{
	}

	void MonsterUIMaterial::SetPipeline(const UINT textureSlotNumber)
	{
		assert(mpShader != nullptr);
		mpShader->SetPipeline();
		//MonsterUIManager::GetInstance().SetPipeline();
		mpTexture->SetPipeline(textureSlotNumber);
	}

	void MonsterUIMaterial::ClearPipeline(const UINT textureSlotNumber)
	{
		mpTexture->ClearSRV(textureSlotNumber);
	}
}