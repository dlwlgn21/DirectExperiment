#include "jhStructuredBuffer.h"

static const constexpr UINT STRUCTURED_BUFFER_SLOT_NUMBER = 13;

namespace jh
{
	StructuredBuffer::StructuredBuffer()
		: mcpStructuredBuffer(nullptr)
		, mcpSRV(nullptr)
		, mBufferDesc{}
		, mSize(0)
		, mStride(0)
	{
		
	}
	StructuredBuffer::~StructuredBuffer()
	{
		mcpSRV.Reset();
		mcpStructuredBuffer.Reset();
	}
	bool StructuredBuffer::Create(const UINT size, const UINT stride, void* pData)
	{
		mSize = size;
		mStride = stride;
		ZeroMemory(&mBufferDesc, sizeof(D3D11_BUFFER_DESC));

		mBufferDesc.ByteWidth = mSize * mStride;
		mBufferDesc.StructureByteStride = mSize;
		mBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		mBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		mBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		mBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		
		if (pData != nullptr)
		{
			D3D11_SUBRESOURCE_DATA subresouceData = {};
			subresouceData.pSysMem = pData;
			if (FAILED(graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateBuffer(&mBufferDesc, &subresouceData, mcpStructuredBuffer.ReleaseAndGetAddressOf())))
			{
				assert(false);
				return false;
			}
		}
		else
		{
			if (FAILED(graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateBuffer(&mBufferDesc, nullptr, mcpStructuredBuffer.ReleaseAndGetAddressOf())))
			{
				assert(false);
				return false;
			}
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;

		if (FAILED(graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateShaderResourceView(mcpStructuredBuffer.Get(), &srvDesc, mcpSRV.ReleaseAndGetAddressOf())))
		{
			assert(false);
			return false;
		}
		return true;
	}
	void StructuredBuffer::WirteDataAtBuffer(void* pData, const UINT bufferCount)
	{
		if (mStride < bufferCount)
		{
			assert(false);
			if (!Create(mSize, bufferCount, pData))
			{
				assert(false);
			}
		}
		else
		{
			assert(mcpStructuredBuffer != nullptr && mcpSRV != nullptr);
			graphics::GraphicDeviceDX11::GetInstance().WriteDataAtBuffer(mcpStructuredBuffer.Get(), pData, static_cast<size_t>(mSize * bufferCount));
		}
	}
	void StructuredBuffer::SetPipeline()
	{
		assert(mcpStructuredBuffer != nullptr && mcpSRV != nullptr);
		//graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetShaderResources();
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetShaderResources(STRUCTURED_BUFFER_SLOT_NUMBER, 1, mcpSRV.GetAddressOf());
	}
}
