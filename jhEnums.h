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
		AUDIO_LISTENER,
		AUDIO_SOURCE,
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
		AUDIO_CLIP,
		COUNT
	};

	enum class eLayerType
	{
		NONE = 0,
		CAMERA,
		BACKGROUND,
		GRID,
		MONSTER,
		MONSTER_ATTACK_COLLIDER,
		MONSTER_EFFECT,
		MONSTER_UI,
		PLAYER,
		EFFECT,
		PLAYER_SKILL,
		PARTICLE,
		LEVEL_UP_UI,
		PROTECTING_OBJECT,
		UI,
		COUNT = 16,
	};

	enum class eColliderLayerType
	{
		MONSTER,
		PLAYER,
		PLAYER_WEAPON,
		PLAYER_SKILL,
		MONSTER_WEAPON,
		PROTECTING_OBJECT,
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
		MONSTER_UI,
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

	enum class ePlayerSkillType
	{
		ELETRIC_BEAM,
		ELETRIC_STRIKE,
		TORNADO,
		COUNT
	};
}