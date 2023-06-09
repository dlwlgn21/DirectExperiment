#pragma once
#include "jhGraphicDeviceDX11.h"


namespace jh
{
	class StructuredBuffer
	{
	public:
		StructuredBuffer();
		~StructuredBuffer();

		bool Create(const UINT size, const UINT stride, void* pData);

		ID3D11Buffer* GetBuffer() const { return mcpStructuredBuffer.Get(); }
		void WirteDataAtBuffer(void* pData, const UINT bufferCount);
		virtual void SetPipeline() = 0;

	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer>				mcpStructuredBuffer;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mcpSRV;
		D3D11_BUFFER_DESC									mBufferDesc;
		UINT												mSize;
		UINT												mStride;
	};
}