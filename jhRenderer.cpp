#include "jhRenderer.h"



namespace jh
{
	Renderer::Renderer(const eComponentRendererType eRendererType, Mesh* pMesh, Material* pMaterial)
		: Component(eComponentType::RENDERER)
		, meRendererType(eRendererType)
		, mpMesh(pMesh)
		, mpMaterial(pMaterial)
	{
	}
	Renderer::~Renderer()
	{
	}
	void Renderer::Initialize()
	{
	}
	void Renderer::Update()
	{
	}
	void Renderer::FixedUpdate()
	{
	}
	void Renderer::Render()
	{
	}
	void Renderer::SetPipeline()
	{
	}
}