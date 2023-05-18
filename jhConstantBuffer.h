#pragma once
#include "jhGraphicDeviceDX11.h"


namespace jh
{
	class ConstantBuffer final
	{
	public:
		ConstantBuffer(const eConstantBufferType eType);
		virtual ~ConstantBuffer();

		ID3D11Buffer* GetBuffer() const { return mcpConstantBuffer.Get(); }

		void WirteDataAtBuffer(ID3D11Resource* pResource, const void* pData, const size_t dataSize);
		void WirteDataAtBuffer(const void* pData, const size_t dataSize);
		
		void SetPipeline();

	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer>		mcpConstantBuffer;
		D3D11_BUFFER_DESC							mBufferDesc;
		eConstantBufferType							meType;
	};
}

