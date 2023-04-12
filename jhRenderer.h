#pragma once
#include "jhComponent.h"
#include "jhMesh.h"
#include "jhMaterial.h"
namespace jh
{
	enum class eComponentRendererType
	{
		SPRITE_RENDERER,
		MESH_RENDERER,
		COUNT
	};
	class Renderer : public Component
	{
	public:
		Renderer(const eComponentRendererType eRendererType, Mesh* pMesh, Material* pMaterial);
		virtual ~Renderer();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;


	protected:
		const eComponentRendererType meRendererType;
		Mesh* mpMesh;
		Material* mpMaterial;
	};
}

