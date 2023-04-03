#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "jhMath.h"

static constexpr const UINT TRANSFORM_CB_SLOT_NUMBER = 0;

namespace jh
{
	struct Vertex
	{
		jh::math::Vector3 Position;
		jh::math::Vector2 UV;
	};

	struct TransformBuffer
	{
		jh::math::Matrix WorldMat;
		jh::math::Matrix ViewMat;
		jh::math::Matrix ProjectionMat;
	};

	enum class eShaderStage
	{
		VS,
		PS,
		COUNT
	};
}