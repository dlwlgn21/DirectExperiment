#include "jhMonsterHPSpriteRenderer.h"
#include "jhTransform.h"
#include "jhMesh.h"

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
	}

	void MonsterHPRenderer::clearPipeline()
	{
		mpMaterial->ClearPipeline(Material::DEFAULT_TEXTURE_SLOT_NUMBER_0);
	}

}