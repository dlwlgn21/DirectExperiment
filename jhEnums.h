#pragma once
namespace jh
{
	enum class eAnimatedObjectLookDirection
	{
		LEFT,
		RIGHT,
		COUNT
	};

	enum class eComponentType
	{
		TRANSFORM,
		CAMERA,
		COLLIDER,
		RENDERER,
		ANIMATOR,
		SCRIPT,
		COUNT
	};

	enum class eColliderShapeType
	{
		RECT,
		CIRCLE,
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

	enum class eSceneType
	{
		PLAY_SCENE,
		COUNT
	};


	enum class eConstantBufferType
	{
		TRANSFORM,
		MATERIAL,
		GRID,
		ANIMATION,
		UV_TRANSLATION,
		COUNT,
	};
}