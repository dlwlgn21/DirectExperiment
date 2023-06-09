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
static constexpr const UINT UI_TIME_CB_SLOT_NUMBER = 2;
static constexpr const UINT COLLIDER_CB_SLOT_NUMBER = 3;
static constexpr const UINT UI_BAR_CB_SLOT_NUMBER = 3;
static constexpr const UINT LIGHT_CB_SLOT_NUMBER = 4;
static constexpr const UINT MONSTER_UI_CB_SLOT_NUMBER = 5;
static constexpr const UINT SIMD_ALIGN_SIZE = 16;

namespace jh
{
	struct Vertex
	{
		jh::math::Vector3 Position;
		jh::math::Vector2 UV;
	};

	struct NormalMapShaderVertex
	{
		jh::math::Vector3 Position;
		jh::math::Vector2 UV;
		jh::math::Vector3 Normal;
		jh::math::Vector3 Tangent;
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
		AnimationBuffer()
			: LeftTop()
			, Size()
			, Offset()
			, AtlasImageSize()
			, AnimationType()
			, IsFlip()
		{
			static_assert(sizeof(AnimationBuffer) % SIMD_ALIGN_SIZE == 0);
		}
	};


	struct alignas(SIMD_ALIGN_SIZE) UITimeBuffer
	{
		jh::math::Vector4			    Time;
		UITimeBuffer()
			: Time(jh::math::Vector4::Zero)
		{
			static_assert(sizeof(UITimeBuffer) % SIMD_ALIGN_SIZE == 0);
		}
	};

	struct alignas(SIMD_ALIGN_SIZE) ColliderBuffer
	{
		jh::math::Vector4			    Color;
	};

	struct alignas(SIMD_ALIGN_SIZE) UIBarBuffer
	{
		jh::math::Vector4			    UV;
		UIBarBuffer()
			: UV(jh::math::Vector4::Zero)
		{
			static_assert(sizeof(UIBarBuffer) % SIMD_ALIGN_SIZE == 0);
		}
	};

	struct alignas(SIMD_ALIGN_SIZE) MonsterUIBuffer
	{
		jh::math::Vector4				MonsterHPRatio;
		MonsterUIBuffer()
			: MonsterHPRatio(jh::math::Vector4::Zero)
		{
			static_assert(sizeof(MonsterUIBuffer) % SIMD_ALIGN_SIZE == 0);
		}
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

	struct alignas(SIMD_ALIGN_SIZE) NumberOfLight
	{
		UINT CountOfLight;
		NumberOfLight()
			: CountOfLight(0)
		{
			static_assert(sizeof(NumberOfLight) == SIMD_ALIGN_SIZE);
		}
	};

	struct alignas(SIMD_ALIGN_SIZE) LightAttribute
	{
		jh::math::Vector4 Diffuse;
		jh::math::Vector4 Specular;
		jh::math::Vector4 Ambient;
		jh::math::Vector4 Position;
		jh::math::Vector4 Direction;

		eLightType	ELightType;
		float		Radius;
		float		Angle;
		int			Padding;
		LightAttribute()
			: Diffuse{}
			, Specular{}
			, Ambient{}
			, Position{}
			, Direction{}
			, ELightType{}
			, Radius{}
			, Angle{}
			, Padding{}
		{	
			assert((sizeof(LightAttribute) % SIMD_ALIGN_SIZE) == 0);
		}
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