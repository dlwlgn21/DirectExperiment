#pragma once
#include "jhResource.h"


namespace jh
{
	class Mesh : public Resource
	{
	public:
		Mesh();
		virtual ~Mesh();
		bool CreateVertexBuffer(void* pData, UINT size);
		bool CreateIndexBuffer(void* pData, UINT indexCount);
		virtual void SetPipeline();
		virtual void Render();

	protected:
		void setVertexBuffer();
		void setIndexBuffer();

	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer>	mcpVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>	mcpIndexBuffer;
		D3D11_BUFFER_DESC						mVertexBufferDesc;
		D3D11_BUFFER_DESC						mIndexBufferDesc;
		UINT									mIndexCount;
	};
}

