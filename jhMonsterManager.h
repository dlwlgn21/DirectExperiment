#pragma once
#include "jhEngine.h"
#include "jhMath.h"
#include "jhMonster.h"

namespace jh
{
	class Transform;
	class Texture;
	class HitEffectObject;
	class PlayerScript;
	class Animator;
	class MonsterAttackColiderObject;
	class AcientBossMonsterAttackColiderObject;
	class UIBarObject;
	class BossMonster;
	enum class eAnimationIndexSequence
	{
		IDLE,
		MOVING,
		ATTACK,
		HIT,
		DIE,
		COUNT
	};

	struct MonsterPackage
	{
		Monster*					pMonster;
		HitEffectObject*			pHitEffectObejct;
		MonsterAttackColiderObject* pMonsterAttackColliderObject;
		UIBarObject*				pUIBarObject;
		MonsterPackage()
			: pMonster(nullptr)
			, pHitEffectObejct(nullptr)
			, pMonsterAttackColliderObject(nullptr)
			, pUIBarObject(nullptr)
		{

		}
	};

	struct AcientBossMonsterPackage
	{
		Monster* pMonster;
		HitEffectObject* pHitEffectObejct;
		AcientBossMonsterAttackColiderObject* pColliderObject[4];
	};

	struct AnimationInfo
	{
		Texture* pAtalsImage;
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


		MonsterPackage MakeMonster(const eMonsterType eType, PlayerScript* pPlayerScript, const jh::math::Vector3& position);
		AcientBossMonsterPackage MakeAcientBossMonster(PlayerScript* pPlayerScript, const jh::math::Vector3& position);

	private:
		void createMonsterInfo(MonsterInfo& monInfo, Mesh* pMesh, Material* pMaterial, Animator* pAnimator, PlayerScript* pPlayerScript, const eMonsterType eMonType);
		void createIntialAnimationInfo(AnimationInfo& animInfo, Texture* pAtalsImage, const jh::math::Vector2& leftTop, const jh::math::Vector2& seperatingSize, const jh::math::Vector2& offset, const UINT spriteCount, const float duration, const float magnification);
		void createMonster(MonsterInfo& monInfo, MonsterPackage& retMonsterPackage);
		void createAttackCollider(MonsterInfo& monInfo, MonsterPackage& retMonsterPackage, const float yPos);
		void createAnimation(Animator* pAnimator, const std::wstring& animKey, AnimationInfo& animInfo);
		Animator* createAllAnimtaion(Animator* pAnimator, const std::wstring& idleKey, const std::wstring& movingKey, const std::wstring& attackKey, const std::wstring& hitKey, const std::wstring& dieKey, AnimationInfo& animInfo, const jh::math::Vector2 allSpriteLeftTopCoords[], UINT allSpriteCounts[], float allAnimDurationCounts[]);
		Animator* createAllVerticalAnimation(Animator* pAnimator, const std::wstring& idleKey, const std::wstring& movingKey, const std::wstring& attackKey, const std::wstring& hitKey, const std::wstring& dieKey, AnimationInfo& animInfo, const jh::math::Vector2 allSpriteLeftTopCoords[], UINT allSpriteCounts[], float allAnimDurationCounts[]);
		void createVerticalAnimation(Animator* pAnimator, const std::wstring& animKey, AnimationInfo& animInfo);
		void modifyAnimationInfoForNewAnimation(AnimationInfo& animInfo, const jh::math::Vector2& leftTop, const UINT spriteCount, const float duration = 0.1f);
		void setTransform(Transform* pMonsterTransform, const jh::math::Vector3& position, const jh::math::Vector3& scale);
		void resizeAttackColliderSize(const eMonsterType eMonType, MonsterAttackColiderObject* pColliderObject);
		void fillLeftTopsArray(jh::math::Vector2 leftTopArray[], const jh::math::Vector2 movingLeftTop, const jh::math::Vector2 attackLeftTop, const jh::math::Vector2 hitLeftTop, const jh::math::Vector2 dieLeftTop);
		void fillSpriteCountArray(UINT spriteCountArray[], const UINT movingCount, const UINT attackCount, const UINT hitCount, const UINT dieCount);
		void fillAnimationDurationArray(float animDurationArray[], const float movingDuration, const float attackDuration, const float hitDuration, const float dieDuration);

	private:
		MonsterManager() = default;
		~MonsterManager() = default;


	public:
#pragma region ANIM_KEYS
		static const std::wstring HIT_COMBO_1_ELECTRIC_EFFECT_ANIM_KEY;
		static const std::wstring HIT_COMBO_2_ELECTRIC_EFFECT_ANIM_KEY;
		static const std::wstring HIT_COMBO_3_ELECTRIC_EFFECT_ANIM_KEY;

		static const std::wstring CAGED_SHOKER_IDLE_ANIM_KEY;
		static const std::wstring CAGED_SHOKER_MOVING_ANIM_KEY;
		static const std::wstring CAGED_SHOKER_ATTACK_ANIM_KEY;
		static const std::wstring CAGED_SHOKER_HITTED_ANIM_KEY;
		static const std::wstring CAGED_SHOKER_DIE_ANIM_KEY;

		static const std::wstring SWEEPER_IDLE_ANIM_KEY;
		static const std::wstring SWEEPER_MOVING_ANIM_KEY;
		static const std::wstring SWEEPER_ATTACK_ANIM_KEY;
		static const std::wstring SWEEPER_HITTED_ANIM_KEY;
		static const std::wstring SWEEPER_DIE_ANIM_KEY;

		static const std::wstring WARDEN_IDLE_ANIM_KEY;
		static const std::wstring WARDEN_MOVING_ANIM_KEY;
		static const std::wstring WARDEN_ATTACK_ANIM_KEY;
		static const std::wstring WARDEN_HITTED_ANIM_KEY;
		static const std::wstring WARDEN_DIE_ANIM_KEY;

		static const std::wstring ZOMBIE_IDLE_ANIM_KEY;
		static const std::wstring ZOMBIE_MOVING_ANIM_KEY;
		static const std::wstring ZOMBIE_ATTACK_ANIM_KEY;
		static const std::wstring ZOMBIE_HITTED_ANIM_KEY;
		static const std::wstring ZOMBIE_DIE_ANIM_KEY;

		static const std::wstring HEABY_SLICER_IDLE_ANIM_KEY;
		static const std::wstring HEABY_SLICER_MOVING_ANIM_KEY;
		static const std::wstring HEABY_SLICER_ATTACK_ANIM_KEY;
		static const std::wstring HEABY_SLICER_HITTED_ANIM_KEY;
		static const std::wstring HEABY_SLICER_DIE_ANIM_KEY;

		static const std::wstring LIGHT_SLICER_IDLE_ANIM_KEY;
		static const std::wstring LIGHT_SLICER_MOVING_ANIM_KEY;
		static const std::wstring LIGHT_SLICER_ATTACK_ANIM_KEY;
		static const std::wstring LIGHT_SLICER_HITTED_ANIM_KEY;
		static const std::wstring LIGHT_SLICER_DIE_ANIM_KEY;

		static const std::wstring DAGGER_IDLE_ANIM_KEY;
		static const std::wstring DAGGER_MOVING_ANIM_KEY;
		static const std::wstring DAGGER_ATTACK_ANIM_KEY;
		static const std::wstring DAGGER_HITTED_ANIM_KEY;
		static const std::wstring DAGGER_DIE_ANIM_KEY;

		static const std::wstring ARCHER_IDLE_ANIM_KEY;
		static const std::wstring ARCHER_MOVING_ANIM_KEY;
		static const std::wstring ARCHER_ATTACK_ANIM_KEY;
		static const std::wstring ARCHER_HITTED_ANIM_KEY;
		static const std::wstring ARCHER_DIE_ANIM_KEY;

		static const std::wstring BLASTER_IDLE_ANIM_KEY;
		static const std::wstring BLASTER_MOVING_ANIM_KEY;
		static const std::wstring BLASTER_ATTACK_ANIM_KEY;
		static const std::wstring BLASTER_HITTED_ANIM_KEY;
		static const std::wstring BLASTER_DIE_ANIM_KEY;





#pragma endregion
	};
}