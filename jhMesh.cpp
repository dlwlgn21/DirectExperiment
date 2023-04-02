#include "jhMesh.h"
#include "jhGraphicDeviceDX11.h"

namespace jh
{
	Mesh::Mesh()
		: Resource(eReousrceType::MESH)
		, mcpVertexBuffer()
		, mBufferDesc()
	{
		ZeroMemory(&mBufferDesc, sizeof(D3D11_BUFFER_DESC));
	}
	Mesh::~Mesh()
	{
		mcpVertexBuffer.Reset();
	}


	bool Mesh::CreateVertexBuffer(void* data, UINT size)
	{
		static const UINT VERTEX_COUNT = 4;
		mBufferDesc.ByteWidth = sizeof(Vertex) * VERTEX_COUNT;
		mBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		mBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		
		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = data;

		HRESULT hr = graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateBuffer(
			&mBufferDesc, 
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
	void Mesh::SetPipeline()
	{
		setVertexBuffer();
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
	void Mesh::Render()
	{
		static const UINT VERTEX_COUNT = 4;
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->Draw(VERTEX_COUNT, 0);
	}
}