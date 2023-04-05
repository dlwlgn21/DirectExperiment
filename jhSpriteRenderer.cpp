#include "jhSpriteRenderer.h"
#include "jhTransform.h"
#include "jhAnimator.h"

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
		clearPipeline();
	}

	void SpriteRenderer::clearPipeline()
	{
		mpMaterial->ClearPipeline();
		Animator* pAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		if (pAnimator != nullptr) { pAnimator->ClearPipeline(); }
	}

	void SpriteRenderer::SetPipeline()
	{
		assert(mpMesh != nullptr && mpMaterial != nullptr);
		Transform* pTranform = GetOwner()->GetTransform();
		pTranform->SetPipeline();
		mpMaterial->SetPipeline();
		mpMesh->SetPipeline();
		Animator* pAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		if (pAnimator != nullptr)	{pAnimator->SetPipeline();}
	}

}