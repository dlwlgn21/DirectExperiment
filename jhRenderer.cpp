#include "jhRenderer.h"


namespace jh
{
	Renderer::Renderer(const eComponentRendererType eRendererType)
		: Component(eComponentType::RENDERER)
		, meRendererType(eRendererType)
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
}