#pragma once
#include "jhRenderer.h"

namespace jh
{
	class Transform;
	class MeshRenderer final : public Renderer
	{
	public:
		MeshRenderer(Mesh* pMesh, Material* pMaterial);
		virtual ~MeshRenderer() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		void setPipeline();
		void clearPipeline();
	private:
		Transform*	mpTransform;
	};

}

