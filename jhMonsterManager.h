#pragma once
#include "jhEngine.h"
#include "jhMath.h"


namespace jh
{
	enum class eMonsterType
	{
		LV_1_CAGED_SHOKER,
		COUNT
	};

	class Transform;
	class Texture;
	class Monster;
	class HitEffectObject;
	class PlayerScript;
	class Animator;
	class MonsterAttackColiderObject;
	struct MonstePackage
	{
		Monster*							pMonster;
		HitEffectObject*					pHitEffectObejct;
		MonsterAttackColiderObject*			pMonsterAttackColliderObject;
		MonstePackage()
			: pMonster(nullptr)
			, pHitEffectObejct(nullptr)
			, pMonsterAttackColliderObject(nullptr)
		{

		}
	};
	struct AnimationInfo
	{
		Texture*					pAtalsImage;
		jh::math::Vector2			LeftTop; 
		jh::math::Vector2			SeperatingSize;
		jh::math::Vector2			Offset; 
		UINT						SpriteCount; 
		float						Duration; 
		float						Magnification;
		AnimationInfo()
			: pAtalsImage(nullptr)
			, LeftTop(jh::math::Vector2::Zero)
			, SeperatingSize(jh::math::Vector2::Zero)
			, Offset(jh::math::Vector2::Zero)
			, SpriteCount(0)
			, Duration(0.0f)
			, Magnification(0.0f)
		{
		}
	};

	class MonsterManager final
	{
	public:
		static MonsterManager& GetInstance()
		{
			static MonsterManager instance;
			return instance;
		}

		MonsterManager(const MonsterManager& other) = delete;
		MonsterManager& operator=(const MonsterManager& other) = delete;


		MonstePackage MakeMonster(const eMonsterType eType, PlayerScript* pPlayerScript, const jh::math::Vector3& position, const jh::math::Vector3& scale);


	private:
		 Animator* createAnimatorOrNull();
		 void createAnimation(Animator* pAnimator, const std::wstring& animKey, AnimationInfo& animInfo);
		 void setTransform(Transform* pMonsterTransform, const jh::math::Vector3& position, const jh::math::Vector3& scale);
	
	private:
		MonsterManager() = default;
		~MonsterManager() = default;

	private:

	};
}

