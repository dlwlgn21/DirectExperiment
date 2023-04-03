#include "jhSpriteRenderer.h"
#include "jhTransform.h"

namespace jh
{
	SpriteRenderer::SpriteRenderer(Mesh* pMesh, Material* pMaterial)
		: Renderer(eComponentRendererType::SPRITE_RENDERER, pMesh, pMaterial)
	{
	}

	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::FixedUpdate()
	{
	}

	void SpriteRenderer::Render()
	{
		Transform* pTranform = GetOwner()->GetTransform();
		pTranform->WriteMatrixDataAtContantBuffer();
		SetPipeline();
		mpMesh->Render();
		mpMaterial->Clear();
	}

	void SpriteRenderer::SetPipeline()
	{
		assert(mpMesh != nullptr && mpMaterial != nullptr);
		Transform* pTranform = GetOwner()->GetTransform();
		pTranform->SetPipeline();
		mpMaterial->SetPipeline();
		mpMesh->SetPipeline();
	}

}