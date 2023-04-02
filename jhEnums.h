#pragma once
namespace jh
{
	enum class eComponentType
	{
		TRANSFORM,
		RENDERER,
		SCRIPT,
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
}