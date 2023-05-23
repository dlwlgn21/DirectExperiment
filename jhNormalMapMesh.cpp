#include "jhNormalMapMesh.h"
#include "jhGraphicDeviceDX11.h"\


namespace jh
{
	NormalMapMesh::NormalMapMesh()
		: Mesh()
	{

	}
	void NormalMapMesh::SetPipeline()
	{
		UINT stride = sizeof(NormalMapShaderVertex);
		UINT offset = 0;
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->IASetVertexBuffers(
			0,
			1,
			mcpVertexBuffer.GetAddressOf(),
			&stride,
			&offset
		);
		setIndexBuffer();
	}
}