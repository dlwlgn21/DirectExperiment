#include "jhSpriteRenderer.h"
#include "jhTransform.h"
#include "jhAnimator.h"

namespace jh
{
	SpriteRenderer::SpriteRenderer(Mesh* pMesh, Material* pMaterial)
		: Renderer(eComponentRendererType::SPRITE_RENDERER, pMesh, pMaterial)
		, mpTransform(nullptr)
	{
	}

	void SpriteRenderer::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::FixedUpdate()
	{
	}

	void SpriteRenderer::Render()
	{
		// Added Part At 2023-04-11
		Animator* pAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		if (pAnimator != nullptr)
		{
			if (!pAnimator->IsActive())	
			{
				return;
			}
		}

		mpTransform->WriteMatrixDataAtContantBuffer();

		setPipeline(pAnimator);

		mpMesh->Render();

		clearPipeline(pAnimator);
	}

	void SpriteRenderer::clearPipeline(Animator* pAnimator)
	{
		if (pAnimator != nullptr)
		{
			mpMaterial->ClearPipeline(Material::ATLAS_TEXTURE_SLOT_NUMBER_12);
			if (pAnimator->IsActive())	{pAnimator->ClearPipeline();}
		}
		else
		{
			mpMaterial->ClearPipeline(Material::DEFAULT_TEXTURE_SLOT_NUMBER_0);
		}

	}

	void SpriteRenderer::setPipeline(Animator* pAnimator)
	{
		assert(mpMesh != nullptr && mpMaterial != nullptr);
		mpTransform->SetPipeline();

		if (pAnimator != nullptr)
		{
			mpMaterial->SetPipeline(Material::ATLAS_TEXTURE_SLOT_NUMBER_12);
			if (pAnimator->IsActive())
			{
				pAnimator->SetPipeline();
			}
		}
		else
		{
			mpMaterial->SetPipeline(Material::DEFAULT_TEXTURE_SLOT_NUMBER_0);
		}

		mpMesh->SetPipeline();
	}
}