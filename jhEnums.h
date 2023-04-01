#pragma once
namespace jh
{
	enum class eComponentType
	{
		TRANSFORM,
		RENDERER,
		COUNT
	};

	enum class eReousrceType
	{
		MESH,
		MATERIAL,
		SHADER,
		TEXTURE,
		COUNT
	};

	enum class eLayerType
	{
		NONE = 0,
		CAMERA,
		BACKGROUND,
		GRID,
		MONSTER,
		PLAYER,

		PARTICLE,
		UI,
		COUNT = 16,
	};
}