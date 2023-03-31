#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace jh
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT2 UV;
	};

	struct MatrixBuffer
	{
		DirectX::XMMATRIX worldMat;
	};

	enum class eShaderStage
	{
		VS,
		PS,
		COUNT
	};
}