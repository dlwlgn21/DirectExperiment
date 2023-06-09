#include "jhConstantBuffer.h"

namespace jh
{
	ConstantBuffer::ConstantBuffer(const eConstantBufferType eType)
		: mcpConstantBuffer()
		, mBufferDesc{}
		, meType(eType)
	{
		ZeroMemory(&mBufferDesc, sizeof(D3D11_BUFFER_DESC));
		switch (eType)
		{
		case eConstantBufferType::TRANSFORM:
		{
			mBufferDesc.ByteWidth = sizeof(TransformBuffer);
			break;
		}
		case eConstantBufferType::MATERIAL:
			assert(false);
			break;
		case eConstantBufferType::GRID:
			assert(false);
			break;
		case eConstantBufferType::ANIMATION:
		{
			mBufferDesc.ByteWidth = sizeof(AnimationBuffer);
			break;
		}
		case eConstantBufferType::UI_STAGE_TIME:
		{
			mBufferDesc.ByteWidth = sizeof(UITimeBuffer);
			break;
		}
		case eConstantBufferType::UI_BAR:
		{
			mBufferDesc.ByteWidth = sizeof(UIBarBuffer);
			break;
		}
		case eConstantBufferType::LIGHT:
		{
			mBufferDesc.ByteWidth = sizeof(NumberOfLight);
			break;
		}
		case eConstantBufferType::MONSTER_UI:
		{
			mBufferDesc.ByteWidth = sizeof(MonsterUIBuffer);
			break;
		}
		default:
			assert(false);
			break;
		}
		mBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		mBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		mBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		mBufferDesc.MiscFlags = 0;
		mBufferDesc.StructureByteStride = 0;
		HRESULT hr = graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateBuffer(
			&mBufferDesc,
			nullptr,
			mcpConstantBuffer.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr)) { assert(false); }
	}
	ConstantBuffer::~ConstantBuffer()
	{
		mcpConstantBuffer.Reset();
	}
	void ConstantBuffer::WirteDataAtBuffer(ID3D11Resource* pResource, const void* pData, const size_t dataSize)
	{
		graphics::GraphicDeviceDX11::GetInstance().WriteDataAtBuffer(pResource, pData, dataSize);
	}

	void ConstantBuffer::WirteDataAtBuffer(const void* pData, const size_t dataSize)
	{
		graphics::GraphicDeviceDX11::GetInstance().WriteDataAtBuffer(mcpConstantBuffer.Get(), pData, dataSize);
	}
	void ConstantBuffer::SetPipeline()
	{
		switch (meType)
		{
		case eConstantBufferType::TRANSFORM:
		{
			graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetConstantBuffers(TRANSFORM_CB_SLOT_NUMBER, 1, mcpConstantBuffer.GetAddressOf());
			break;
		}
		case eConstantBufferType::MATERIAL:
			assert(false);
			break;
		case eConstantBufferType::GRID:
			assert(false);
			break;
		case eConstantBufferType::ANIMATION:
		{
			graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetConstantBuffers(ANINATION_CB_SLOT_NUMBER, 1, mcpConstantBuffer.GetAddressOf());
			graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetConstantBuffers(ANINATION_CB_SLOT_NUMBER, 1, mcpConstantBuffer.GetAddressOf());
			break;
		}
		case eConstantBufferType::UI_STAGE_TIME:
		{
			graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetConstantBuffers(UI_TIME_CB_SLOT_NUMBER, 1, mcpConstantBuffer.GetAddressOf());
			break;
			//case eConstantBufferType::COLLIDER_COLOR:
			//	graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetConstantBuffers(COLLIDER_CB_SLOT_NUMBER, 1, mcpConstantBuffer.GetAddressOf());
			//	break;
		}
		case eConstantBufferType::UI_BAR:
		{
			graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetConstantBuffers(UI_BAR_CB_SLOT_NUMBER, 1, mcpConstantBuffer.GetAddressOf());
			graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetConstantBuffers(UI_BAR_CB_SLOT_NUMBER, 1, mcpConstantBuffer.GetAddressOf());
			break;
		}
		case eConstantBufferType::LIGHT:
		{
			graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetConstantBuffers(LIGHT_CB_SLOT_NUMBER, 1, mcpConstantBuffer.GetAddressOf());
			break;
		}
		case eConstantBufferType::MONSTER_UI:
		{
			graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->PSSetConstantBuffers(MONSTER_UI_CB_SLOT_NUMBER, 1, mcpConstantBuffer.GetAddressOf());
			break;
		}
		default:
			assert(false);
			break;
		}
	}
}