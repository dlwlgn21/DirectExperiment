#pragma once
#include "jhRenderer.h"

namespace jh
{
	class Transform;
	class SpriteRenderer final : public Renderer
	{
	public:
		SpriteRenderer(Mesh* pMesh, Material* pMaterial);
		virtual ~SpriteRenderer() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void SetPipeline() override;
		void Render() override;

	};

}

