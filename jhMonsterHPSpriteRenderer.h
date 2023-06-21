#pragma once
#include "jhRenderer.h"

namespace jh
{
	class Transform;
	class MonsterHPRenderer final : public Renderer
	{
	public:
		MonsterHPRenderer(Mesh* pMesh, Material* pMaterial);
		virtual ~MonsterHPRenderer() = default;

		void Initialize() override;
		void Render() override;

	private:
		void setPipeline();
		void clearPipeline();
	private:
		Transform* mpTransform;
	};

}

