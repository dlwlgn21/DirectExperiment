#pragma once
#include "jhMesh.h"

namespace jh
{

	class NormalMapMesh final : public Mesh
	{
	public:
		NormalMapMesh();
		virtual ~NormalMapMesh() = default;

		void SetPipeline() override;
	};
}