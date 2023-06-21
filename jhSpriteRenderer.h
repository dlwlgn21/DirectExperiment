#pragma once
#include "jhRenderer.h"

namespace jh
{
	class Transform;
	class Animator;
	class SpriteRenderer final : public Renderer
	{
	public:
		SpriteRenderer(Mesh* pMesh, Material* pMaterial);
		virtual ~SpriteRenderer() = default;

		void Initialize() override;
		void Render() override;

	private:
		void setPipeline(Animator* pAnimator);
		void clearPipeline(Animator* pAnimator);

	private:
		Transform* mpTransform;
	};

}

