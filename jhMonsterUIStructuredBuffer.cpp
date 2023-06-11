#include "jhMonsterUIStructuredBuffer.h"

static const constexpr UINT MONSTER_UI_STRUCTURED_BUFFER_SLOT_NUMBER = 14;

namespace jh
{
	MonsterUIStructuredBuffer::MonsterUIStructuredBuffer()
		: StructuredBuffer()
	{

	}
	void MonsterUIStructuredBuffer::SetPipeline()
	{
		assert(mcpStructuredBuffer != nullptr && mcpSRV != nullptr);
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetShaderResources(MONSTER_UI_STRUCTURED_BUFFER_SLOT_NUMBER, 1, mcpSRV.GetAddressOf());
	}
}

