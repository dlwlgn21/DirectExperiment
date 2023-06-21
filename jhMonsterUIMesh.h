#pragma once
#include "jhMesh.h"

namespace jh
{
	class MonsterUIMesh final : public Mesh
	{
	public:
		MonsterUIMesh();
		virtual ~MonsterUIMesh() = default;
		void Render() override;
	};

}