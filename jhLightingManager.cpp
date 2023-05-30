#include "jhLightingManager.h"

static const constexpr UINT INIT_LIGHT_COUNT = 16;

namespace jh
{
	void LightingManager::Initialize()
	{
		mspLightStructuredBuffer = std::make_unique<StructuredBuffer>();
		mspLightStructuredBuffer->Create(sizeof(LightAttribute), INIT_LIGHT_COUNT, nullptr);
		mLights.reserve(INIT_LIGHT_COUNT);
		mspLightConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::LIGHT);
	}
	void LightingManager::WriteLightDataAtBuffer()
	{
		assert(mspLightStructuredBuffer != nullptr && mspLightConstantBuffer != nullptr);
		mspLightStructuredBuffer->WirteDataAtBuffer(mLights.data(), static_cast<UINT>(mLights.size()));
		NumberOfLight lightNumber;
		ZeroMemory(&lightNumber, sizeof(NumberOfLight));
		lightNumber.NumberOfLight = static_cast<UINT>(mLights.size());
		mspLightConstantBuffer->WirteDataAtBuffer(&lightNumber, sizeof(NumberOfLight));
	}
	void LightingManager::SetPipeline()
	{
		assert(mspLightStructuredBuffer != nullptr && mspLightConstantBuffer != nullptr);
		mspLightStructuredBuffer->SetPipeline();
		mspLightConstantBuffer->SetPipeline();
	}

}