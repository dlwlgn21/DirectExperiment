#include "jhMonsterHPSpriteRenderer.h"
#include "jhTransform.h"
#include "jhMesh.h"
#include "jhMonsterUIManager.h"
#include "jhMonsterScript.h"
#include "jhMonsterUIScript.h"

namespace jh
{
	MonsterHPRenderer::MonsterHPRenderer(Mesh* pMesh, Material* pMaterial)
		: Renderer(eComponentRendererType::MONSTER_HP_RENDERER, pMesh, pMaterial)
		, mpTransform(nullptr)
	{
	}

	void MonsterHPRenderer::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}


	void MonsterHPRenderer::Render()
	{
		mpTransform->WriteMatrixDataAtContantBuffer();

		setPipeline();

		mpMesh->Render();

		clearPipeline();
	}

	void MonsterHPRenderer::setPipeline()
	{
		assert(mpMesh != nullptr && mpMaterial != nullptr);
		mpTransform->SetPipeline();
		mpMaterial->SetPipeline(Material::DEFAULT_TEXTURE_SLOT_NUMBER_0);
		mpMesh->SetPipeline();
		MonsterUIScript* pUIScript = static_cast<MonsterUIScript*>(GetOwner()->GetScriptOrNull());
		const MonsterHPstatus monHpStat = pUIScript->GetMonsterScript()->GetCurrentHPStatus();
		const float hpRatio = static_cast<float>(monHpStat.CurrHP) / monHpStat.MaxHP;
		MonsterUIManager::GetInstance().WriteMonsterUIDataAtBuffer(hpRatio);
		MonsterUIManager::GetInstance().SetPipeline();
	}

	void MonsterHPRenderer::clearPipeline()
	{
		mpMaterial->ClearPipeline(Material::DEFAULT_TEXTURE_SLOT_NUMBER_0);
	}

}