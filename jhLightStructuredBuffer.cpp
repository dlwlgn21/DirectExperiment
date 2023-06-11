#include "jhLightStructuredBuffer.h"

static const constexpr UINT LIGHT_STRUCTURED_BUFFER_SLOT_NUMBER = 13;

namespace jh
{
	LightStructuredBuffer::LightStructuredBuffer()
		: StructuredBuffer()
	{

	}
	void LightStructuredBuffer::SetPipeline()
	{		
		assert(mcpStructuredBuffer != nullptr && mcpSRV != nullptr);
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetShaderResources(LIGHT_STRUCTURED_BUFFER_SLOT_NUMBER, 1, mcpSRV.GetAddressOf());
	}


}
