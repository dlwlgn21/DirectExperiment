#pragma once
namespace jh
{
	enum class eObjectLookDirection
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
		LIGHT,
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
		EFFECT,
		MONSTER_EFFECT,
		PARTICLE,
		UI,
		COUNT = 16,
	};

	enum class eColliderLayerType
	{
		MONSTER,
		PLAYER,
		PLAYER_WEAPON,
		MONSTER_WEAPON,
		COUNT
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
		COLLIDER_COLOR,
		UI_BAR,
		LIGHT,
		MONSTER_UI_BAR,
		COUNT,
	};

	enum class eMonsterType
	{
		LV_1_CAGED_SHOKER,
		LV_1_SWEEPER,
		LV_1_WARDEN,
		LV_1_ZOMBIE,
		LV_1_HEABY_SLICER,
		LV_1_LIGHT_SLICER,
		LV_1_DAGGER,
		LV_1_ARCHER,
		LV_1_BLASTER,
		LV_1_ACIENT_BOSS,
		COUNT
	};

	enum class eLightType
	{
		DIRECTIONAL,
		POINT,
		SPOT_LIGHT,
		COUNT
	};
}