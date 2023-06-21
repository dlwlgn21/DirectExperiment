#include "jhMesh.h"
#include "jhGraphicDeviceDX11.h"

namespace jh
{
	Mesh::Mesh()
		: Resource(eReousrceType::MESH)
		, mcpVertexBuffer()
		, mcpIndexBuffer()
		, mVertexBufferDesc()
		, mIndexBufferDesc()
		, mIndexCount(0)
	{
		ZeroMemory(&mVertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
		ZeroMemory(&mIndexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	}
	Mesh::~Mesh()
	{
		mcpIndexBuffer.Reset();
		mcpVertexBuffer.Reset();
	}

	bool Mesh::CreateVertexBuffer(void* pData, UINT size)
	{
		mVertexBufferDesc.ByteWidth = size;
		mVertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		mVertexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		
		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = pData;

		HRESULT hr = graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateBuffer(
			&mVertexBufferDesc,
			&subData,
			mcpVertexBuffer.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr))
		{
			assert(false);
			return false;
		}


		return true;
	}
	bool Mesh::CreateIndexBuffer(void* pData, UINT indexCount)
	{
		mIndexCount = indexCount;
		mIndexBufferDesc.ByteWidth = sizeof(UINT) * mIndexCount;
		mIndexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		mIndexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mIndexBufferDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = pData;

		HRESULT hr = graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateBuffer(
			&mIndexBufferDesc,
			&subData,
			mcpIndexBuffer.ReleaseAndGetAddressOf()
		);
		if (FAILED(hr))
		{
			assert(false);
			return false;
		}
		return true;
	}
	void Mesh::SetPipeline()
	{
		setVertexBuffer();
		setIndexBuffer();
	}
	void Mesh::setVertexBuffer()
	{
		assert(mcpVertexBuffer != nullptr);

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->IASetVertexBuffers(
			0,
			1,
			mcpVertexBuffer.GetAddressOf(),
			&stride,
			&offset
		);
	}
	void Mesh::setIndexBuffer()
	{
		assert(mcpIndexBuffer != nullptr);
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->IASetIndexBuffer(
			mcpIndexBuffer.Get(),
			DXGI_FORMAT_R32_UINT,
			0
		);
	}
	void Mesh::Render()
	{
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->DrawIndexed(mIndexCount, 0, 0);
	}
}