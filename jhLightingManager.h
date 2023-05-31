#pragma once
#include "jhEngine.h"
#include "jhGraphics.h"
#include "jhStructuredBuffer.h"
#include "jhConstantBuffer.h"

namespace jh
{
	class LightingManager final
	{
	public:
		static LightingManager& GetInstance()
		{
			static LightingManager instance;
			return instance;
		}
		LightingManager(const LightingManager& other) = delete;
		LightingManager& operator=(const LightingManager& other) = delete;


		void Initialize();
		__forceinline std::vector<LightAttribute>& GetLights() { return mLights; }
		__forceinline void PushLightAttribute(LightAttribute lightAttribute) { mLights.push_back(lightAttribute); }
		__forceinline void ClearLightAttribute() { mLights.clear(); }

		void WriteLightDataAtBuffer();
		void SetPipeline();

		static LightAttribute makeLightAttribute(const eLightType eType, const jh::math::Vector4& diffuse, const float radius);

	private:
		LightingManager() = default;
		~LightingManager()
		{
			mspLightConstantBuffer.reset();
			mspLightStructuredBuffer.reset();
		}
	private:
		std::vector<LightAttribute>			mLights;
		std::unique_ptr<StructuredBuffer>	mspLightStructuredBuffer;
		std::unique_ptr<ConstantBuffer>		mspLightConstantBuffer;
	};
}