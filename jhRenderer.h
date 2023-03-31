#pragma once
#include "jhComponent.h"

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
		Renderer(const eComponentRendererType eRendererType);
		virtual ~Renderer();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	protected:
		const eComponentRendererType meRendererType;
	};
}

