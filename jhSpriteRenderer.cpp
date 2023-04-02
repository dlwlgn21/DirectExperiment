#include "jhSpriteRenderer.h"

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
		SetPipeline();
		mpMesh->Render();
		mpMaterial->Clear();
	}

	void SpriteRenderer::SetPipeline()
	{
		assert(mpMesh != nullptr && mpMaterial != nullptr);
		mpMaterial->SetPipeline();
		mpMesh->SetPipeline();
	}

}