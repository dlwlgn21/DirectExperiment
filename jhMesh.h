#pragma once
#include "jhGraphics.h"

namespace jh
{
	class Mesh final
	{
	public:
		Mesh();
		~Mesh();

		bool CreateVertexBuffer(void* data, UINT size);
		
		void SetVertexBuffer();
		void Render();
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer>	mcpVertexBuffer;
		D3D11_BUFFER_DESC						mBufferDesc;
	};
}

