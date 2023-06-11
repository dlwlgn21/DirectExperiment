#include "jhStructuredBuffer.h"

namespace jh
{
	class LightStructuredBuffer final : public StructuredBuffer
	{
	public:
		LightStructuredBuffer();
		virtual ~LightStructuredBuffer() = default;

		void SetPipeline() override;
	};


}