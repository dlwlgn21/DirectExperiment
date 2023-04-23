#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "jhMath.h"

static constexpr const UINT TRANSFORM_CB_SLOT_NUMBER = 0;
static constexpr const UINT ANINATION_CB_SLOT_NUMBER = 1;
static constexpr const UINT BG_UV_TRANSLATION_CB_SLOT_NUMBER = 2;
static constexpr const UINT COLLIDER_CB_SLOT_NUMBER = 3;
static constexpr const UINT UI_BAR_CB_SLOT_NUMBER = 4;

static constexpr const UINT SIMD_ALIGN_SIZE = 16;

namespace jh
{
	struct Vertex
	{
		jh::math::Vector3 Position;
		jh::math::Vector2 UV;
	};

	struct alignas(SIMD_ALIGN_SIZE) TransformBuffer
	{
		jh::math::Matrix WorldMat;
		jh::math::Matrix ViewMat;
		jh::math::Matrix ProjectionMat;
	};

	struct alignas(SIMD_ALIGN_SIZE) AnimationBuffer
	{
		jh::math::Vector2				LeftTop;
		jh::math::Vector2				Size;
		jh::math::Vector2				Offset;
		jh::math::Vector2				AtlasImageSize;

		UINT							AnimationType;
		UINT							IsFlip;
	};


	struct alignas(SIMD_ALIGN_SIZE) UVTranslatationBuffer
	{
		jh::math::Vector4			    UVPosition;
	};

	struct alignas(SIMD_ALIGN_SIZE) ColliderBuffer
	{
		jh::math::Vector4			    Color;
	};

	struct alignas(SIMD_ALIGN_SIZE) UIBarBuffer
	{
		jh::math::Vector4			    UV;
	};


	struct alignas(SIMD_ALIGN_SIZE) DebugMesh
	{
		eColliderShapeType	EColiiderShapeType;
		jh::math::Vector3	Position;
		jh::math::Vector3	Rotation;
		jh::math::Vector3	Scale;
		float				Radius;
		float				Duration;
		float				Time;
	};


	enum class eShaderStage
	{
		VS,
		PS,
		COUNT
	};

	enum class eAnimatnionType
	{
		NO_ANIMATION,
		SECOND_DIMENTION,
		THIRD_DIMENTION,
		COUNT
	};
}