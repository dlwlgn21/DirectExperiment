#include "jhMeshRenderer.h"
#include "jhTransform.h"

namespace jh
{
	MeshRenderer::MeshRenderer(Mesh* pMesh, Material* pMaterial)
		: Renderer(eComponentRendererType::MESH_RENDERER, pMesh, pMaterial)
		, mpTransform(nullptr)
	{
	}

	void MeshRenderer::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::FixedUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		mpTransform->WriteMatrixDataAtContantBuffer();

		setPipeline();

		mpMesh->Render();

		clearPipeline();
	}

	void MeshRenderer::clearPipeline()
	{
		mpMaterial->ClearPipeline(Material::DEFAULT_TEXTURE_SLOT_NUMBER_0);
	}

	void MeshRenderer::setPipeline()
	{
		assert(mpMesh != nullptr && mpMaterial != nullptr);
		mpTransform->SetPipeline();
		mpMaterial->SetPipeline(Material::DEFAULT_TEXTURE_SLOT_NUMBER_0);
		mpMesh->SetPipeline();
	}
}