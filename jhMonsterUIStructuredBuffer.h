#pragma once
#include "jhStructuredBuffer.h"

namespace jh
{
	class MonsterUIStructuredBuffer final : public StructuredBuffer
	{
	public:
		MonsterUIStructuredBuffer();
		virtual ~MonsterUIStructuredBuffer() = default;

		void SetPipeline();
	};

}
