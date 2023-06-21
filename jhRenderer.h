#pragma once
#include "jhComponent.h"
#include "jhMesh.h"
#include "jhNormalMapMaterial.h"

namespace jh
{
	enum class eComponentRendererType
	{
		SPRITE_RENDERER,
		MESH_RENDERER,
		MONSTER_HP_RENDERER,
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

		eComponentRendererType GetType() const { return meRendererType; }

	protected:
		const eComponentRendererType meRendererType;
		Mesh* mpMesh;
		Material* mpMaterial;
	};
}

