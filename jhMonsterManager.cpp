#include "jhMonsterManager.h"
#include "jhMonster.h"
#include "jhResourcesManager.h"
#include "jhResourceMaker.h"
#include "jhTransform.h"
#include "jhMaterial.h"
#include "jhTexture.h"
#include "jhMesh.h"
#include "jhMonsterScript.h"
#include "jhMonsterAttackColiderObject.h"
#include "jhHitEffectObject.h"
#include "jhHitEffectScript.h"
#include "jhPlayerScript.h"
#include "jhAnimator.h"
#include "jhAnimation.h"
#include "jhCollider2D.h"

using namespace jh::math;

static constexpr const float MONSTER_INITIAL_Z_POS = 4.0f;
static constexpr const float MONSTER_HIT_ANIM_DURATION = 0.1f;
static constexpr const float MONSTER_DIE_ANIM_DURATION = 0.3f;

static constexpr const float CAGED_SHOKER_SCALE_VALUE = 7.0f;
static constexpr const float CAGED_SHOKER_INITIAL_Y_POS = -1.8f;
static constexpr const float MONSTER_ATTACK_COLLIDER_Y_POS = -2.2f;

static constexpr const float DEFAULT_ANIM_DURATION = 0.1f;
static constexpr const float COLLIDER_Z_VALUE = 1.1f;

static constexpr const float ZOMBIE_SCALE_VALUE = 3.5f;

static constexpr const float HEABY_SLICER_SCALE_VALUE = 6.0f;
static constexpr const float LIGHT_SLICER_SCALE_VALUE = 6.0f;


static constexpr const jh::math::Vector3 CAGED_SHOKER_SCALE_VECTOR = Vector3(CAGED_SHOKER_SCALE_VALUE, CAGED_SHOKER_SCALE_VALUE, 1.0f);
static constexpr const jh::math::Vector3 SWEEPER_SCALE_VECTOR = Vector3(CAGED_SHOKER_SCALE_VALUE, CAGED_SHOKER_SCALE_VALUE, 1.0f);
static constexpr const jh::math::Vector3 ZOMBIE_SCALE_VECTOR = Vector3(ZOMBIE_SCALE_VALUE, ZOMBIE_SCALE_VALUE, 1.0f);
static constexpr const jh::math::Vector3 HEABY_SLICER_SCALE_VECTOR(HEABY_SLICER_SCALE_VALUE, HEABY_SLICER_SCALE_VALUE, 1.0f);
static constexpr const jh::math::Vector3 LIGHT_SLICER_SCALE_VECTOR(LIGHT_SLICER_SCALE_VALUE, LIGHT_SLICER_SCALE_VALUE, 1.0f);

namespace jh
{

	const std::wstring MonsterManager::HIT_COMBO_1_ELECTRIC_EFFECT_ANIM_KEY = L"ElectricHit1Key";
	const std::wstring MonsterManager::HIT_COMBO_2_ELECTRIC_EFFECT_ANIM_KEY = L"ElectricHit2Key";
	const std::wstring MonsterManager::HIT_COMBO_3_ELECTRIC_EFFECT_ANIM_KEY = L"ElectricHit3Key";

	const std::wstring MonsterManager::CAGED_SHOKER_IDLE_ANIM_KEY	= L"CagedIdle";
	const std::wstring MonsterManager::CAGED_SHOKER_MOVING_ANIM_KEY = L"CagedMoving";
	const std::wstring MonsterManager::CAGED_SHOKER_ATTACK_ANIM_KEY = L"CagedAttack";
	const std::wstring MonsterManager::CAGED_SHOKER_HITTED_ANIM_KEY = L"CagedHitted";
	const std::wstring MonsterManager::CAGED_SHOKER_DIE_ANIM_KEY	= L"CagedDie";

	const std::wstring MonsterManager::SWEEPER_IDLE_ANIM_KEY	= L"SweeperIdle";
	const std::wstring MonsterManager::SWEEPER_MOVING_ANIM_KEY	= L"SweeperMoving";
	const std::wstring MonsterManager::SWEEPER_ATTACK_ANIM_KEY	= L"SweeperAttack";
	const std::wstring MonsterManager::SWEEPER_HITTED_ANIM_KEY	= L"SweeperHitted";
	const std::wstring MonsterManager::SWEEPER_DIE_ANIM_KEY		= L"SweeperDie";

	const std::wstring MonsterManager::WARDEN_IDLE_ANIM_KEY		= L"WardenIdle";
	const std::wstring MonsterManager::WARDEN_MOVING_ANIM_KEY	= L"WardenMoving";
	const std::wstring MonsterManager::WARDEN_ATTACK_ANIM_KEY	= L"WardenAttack";
	const std::wstring MonsterManager::WARDEN_HITTED_ANIM_KEY	= L"WardenHitted";
	const std::wstring MonsterManager::WARDEN_DIE_ANIM_KEY		= L"WardenDie";

	const std::wstring MonsterManager::ZOMBIE_IDLE_ANIM_KEY		= L"ZombieIdle";
	const std::wstring MonsterManager::ZOMBIE_MOVING_ANIM_KEY	= L"ZombieMoving";
	const std::wstring MonsterManager::ZOMBIE_ATTACK_ANIM_KEY	= L"ZombieAttack";
	const std::wstring MonsterManager::ZOMBIE_HITTED_ANIM_KEY	= L"ZombieHitted";
	const std::wstring MonsterManager::ZOMBIE_DIE_ANIM_KEY		= L"ZombieDie";

	const std::wstring MonsterManager::HEABY_SLICER_IDLE_ANIM_KEY	= L"HeabySlicerIdle";
	const std::wstring MonsterManager::HEABY_SLICER_MOVING_ANIM_KEY = L"HeabySlicerMoving";
	const std::wstring MonsterManager::HEABY_SLICER_ATTACK_ANIM_KEY = L"HeabySlicerAttack";
	const std::wstring MonsterManager::HEABY_SLICER_HITTED_ANIM_KEY = L"HeabySlicerHitted";
	const std::wstring MonsterManager::HEABY_SLICER_DIE_ANIM_KEY	= L"HeabySlicerDie";

	const std::wstring MonsterManager::LIGHT_SLICER_IDLE_ANIM_KEY	= L"LightSlicerIdle";
	const std::wstring MonsterManager::LIGHT_SLICER_MOVING_ANIM_KEY = L"LightSlicerMoving";
	const std::wstring MonsterManager::LIGHT_SLICER_ATTACK_ANIM_KEY = L"LightSlicerAttack";
	const std::wstring MonsterManager::LIGHT_SLICER_HITTED_ANIM_KEY = L"LightSlicerHitted";
	const std::wstring MonsterManager::LIGHT_SLICER_DIE_ANIM_KEY	= L"LightSlicerDie";

	MonsterPackage MonsterManager::MakeMonster(const eMonsterType eType, PlayerScript* pPlayerScript, const Vector3& position)
	{
		assert(pPlayerScript != nullptr);
		MonsterPackage retMonsterPackage;
		ZeroMemory(&retMonsterPackage, sizeof(MonsterPackage));
		Vector2 leftTops[static_cast<UINT>(eAnimationIndexSequence::COUNT)];
		UINT spriteCounts[static_cast<UINT>(eAnimationIndexSequence::COUNT)];
		float animDurations[static_cast<UINT>(eAnimationIndexSequence::COUNT)];
		switch (eType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			static constexpr const float CAGED_SHOKER_WIDTH = 110.0f;
			static constexpr const float CAGED_SHOKER_HEIGHT = 42.0f;
			static constexpr const float CAGED_SHOKER_MAG = 130.0f;
			AnimationInfo animInfo;
			ZeroMemory(&animInfo, sizeof(AnimationInfo));
			createIntialAnimationInfo(
				animInfo, 
				ResourcesManager::Find<Texture>(ResourceMaker::MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY),
				Vector2(Vector2::Zero),
				Vector2(CAGED_SHOKER_WIDTH, CAGED_SHOKER_HEIGHT),
				Vector2(0.007f, 0.0f),
				15,
				DEFAULT_ANIM_DURATION,
				CAGED_SHOKER_MAG
			);
			fillLeftTopsArray(
				leftTops,
				Vector2(0.0f, CAGED_SHOKER_HEIGHT * 1),
				Vector2(0.0f, CAGED_SHOKER_HEIGHT * 2),
				Vector2(0.0f, CAGED_SHOKER_HEIGHT * 3),
				Vector2(0.0f, CAGED_SHOKER_HEIGHT * 4)
			);

			fillSpriteCountArray(
				spriteCounts,
				12,
				16,
				2,
				12
			);
			fillAnimationDurationArray(
				animDurations,
				DEFAULT_ANIM_DURATION,
				DEFAULT_ANIM_DURATION,
				DEFAULT_ANIM_DURATION,
				MONSTER_DIE_ANIM_DURATION - 0.1f
			);

			Animator* pCagedShokerAnimator = createAllAnimtaion(
				new Animator(),
				CAGED_SHOKER_IDLE_ANIM_KEY,
				CAGED_SHOKER_MOVING_ANIM_KEY,
				CAGED_SHOKER_ATTACK_ANIM_KEY,
				CAGED_SHOKER_HITTED_ANIM_KEY,
				CAGED_SHOKER_DIE_ANIM_KEY,
				animInfo,
				leftTops,
				spriteCounts,
				animDurations
			);

			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			createMonsterInfo(
				monInfo, 
				ResourcesManager::Find<Mesh>(ResourceMaker::RECT_NORMAL_MAP_MESH_KEY), 
				ResourcesManager::Find<Material>(ResourceMaker::MONSTER_CAGED_SHOKER_NORMAL_MAP_MATERIAL_KEY), 
				pCagedShokerAnimator,
				pPlayerScript,
				eMonsterType::LV_1_CAGED_SHOKER
			);

			createMonster(monInfo, retMonsterPackage);
			createAttackCollider(monInfo, retMonsterPackage, MONSTER_ATTACK_COLLIDER_Y_POS);
			setTransform(retMonsterPackage.pMonster->GetTransform(), position, CAGED_SHOKER_SCALE_VECTOR);

			break;
		}

		case eMonsterType::LV_1_SWEEPER:
		{
			static constexpr const float SWEEPER_WIDTH = 88.0f;
			static constexpr const float SWEEPER_HEIGHT = 33.0f;
			static constexpr const float SWEEPER_MAG = 100.0f;
			AnimationInfo animInfo;
			ZeroMemory(&animInfo, sizeof(AnimationInfo));
			createIntialAnimationInfo(
				animInfo,
				ResourcesManager::Find<Texture>(ResourceMaker::MONSTER_TEXTURE_SWEEPER_ATLAS_KEY),
				Vector2(Vector2::Zero),
				Vector2(SWEEPER_WIDTH, SWEEPER_HEIGHT),
				Vector2(0.02f, 0.0f),
				6,
				DEFAULT_ANIM_DURATION,
				SWEEPER_MAG
			);

			fillLeftTopsArray(
				leftTops,
				Vector2(0.0f, SWEEPER_HEIGHT * 1),
				Vector2(0.0f, SWEEPER_HEIGHT * 4),
				Vector2(0.0f, SWEEPER_HEIGHT * 7),
				Vector2(0.0f, SWEEPER_HEIGHT * 8)
			);

			fillSpriteCountArray(
				spriteCounts,
				8,
				10,
				2,
				5
			);
			fillAnimationDurationArray(
				animDurations,
				DEFAULT_ANIM_DURATION,
				0.15f,
				DEFAULT_ANIM_DURATION,
				MONSTER_DIE_ANIM_DURATION
			);

			Animator* pSweeperAnimator = createAllAnimtaion(
				new Animator(),
				SWEEPER_IDLE_ANIM_KEY,
				SWEEPER_MOVING_ANIM_KEY,
				SWEEPER_ATTACK_ANIM_KEY,
				SWEEPER_HITTED_ANIM_KEY,
				SWEEPER_DIE_ANIM_KEY,
				animInfo,
				leftTops,
				spriteCounts,
				animDurations
			);

			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			createMonsterInfo(
				monInfo,
				ResourcesManager::Find<Mesh>(ResourceMaker::RECT_NORMAL_MAP_MESH_KEY),
				ResourcesManager::Find<Material>(ResourceMaker::MONSTER_SWEEPER_NORMAL_MAP_MATERIAL_KEY),
				pSweeperAnimator,
				pPlayerScript,
				eMonsterType::LV_1_SWEEPER
			);
			createMonster(monInfo, retMonsterPackage);
			createAttackCollider(monInfo, retMonsterPackage, MONSTER_ATTACK_COLLIDER_Y_POS);
			setTransform(retMonsterPackage.pMonster->GetTransform(), position, SWEEPER_SCALE_VECTOR);
			break;
		}

		case eMonsterType::LV_1_WARDEN:
		{
			static constexpr const float WARDEN_WIDTH = 97.0f;
			static constexpr const float WARDEN_HEIGHT = 32.0f;
			static constexpr const float WARDEN_MAG = 150.0f;
			static constexpr const float WARDEN_DIE_ANIM_DURATION = 0.1f;
			AnimationInfo animInfo;
			ZeroMemory(&animInfo, sizeof(AnimationInfo));
			const Vector2 ANIM_OFFSET = Vector2(0.014f, 0.0f);
			createIntialAnimationInfo(
				animInfo,
				ResourcesManager::Find<Texture>(ResourceMaker::MONSTER_TEXTURE_WARDEN_ATLAS_KEY),
				Vector2(Vector2::Zero),
				Vector2(WARDEN_WIDTH, WARDEN_HEIGHT),
				ANIM_OFFSET,
				12,
				DEFAULT_ANIM_DURATION,
				WARDEN_MAG
			);

			fillLeftTopsArray(
				leftTops,
				Vector2(0.0f, WARDEN_HEIGHT * 1),
				Vector2(0.0f, WARDEN_HEIGHT * 2),
				Vector2(0.0f, WARDEN_HEIGHT * 3),
				Vector2(0.0f, WARDEN_HEIGHT * 3)
			);

			fillSpriteCountArray(
				spriteCounts,
				12,
				16,
				2,
				11
			);
			fillAnimationDurationArray(
				animDurations,
				DEFAULT_ANIM_DURATION,
				DEFAULT_ANIM_DURATION,
				DEFAULT_ANIM_DURATION,
				WARDEN_DIE_ANIM_DURATION
			);

			Animator* pWardenAnimator = createAllAnimtaion(
				new Animator(),
				WARDEN_IDLE_ANIM_KEY,
				WARDEN_MOVING_ANIM_KEY,
				WARDEN_ATTACK_ANIM_KEY,
				WARDEN_HITTED_ANIM_KEY,
				WARDEN_DIE_ANIM_KEY,
				animInfo,
				leftTops,
				spriteCounts,
				animDurations
			);

			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			createMonsterInfo(
				monInfo,
				ResourcesManager::Find<Mesh>(ResourceMaker::RECT_NORMAL_MAP_MESH_KEY),
				ResourcesManager::Find<Material>(ResourceMaker::MONSTER_WARDEN_NORMAL_MAP_MATERIAL_KEY),
				pWardenAnimator,
				pPlayerScript,
				eMonsterType::LV_1_WARDEN
			);
			createMonster(monInfo, retMonsterPackage);
			createAttackCollider(monInfo, retMonsterPackage, MONSTER_ATTACK_COLLIDER_Y_POS);
			setTransform(retMonsterPackage.pMonster->GetTransform(), position, SWEEPER_SCALE_VECTOR);
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			static constexpr const float ZOMBIE_WIDTH = 130.0f;
			static constexpr const float ZOMBIE_HEIGHT = 70.0f;
			static constexpr const float ZOMBIE_MAG = 130.0f;
			const UINT ZOMBIE_SPRITE_MAX_COUNT = 24;
			const float ZOMBIE_IDLE_MOVING_ANIM_DURATION = 0.2f;
			AnimationInfo animInfo;
			ZeroMemory(&animInfo, sizeof(AnimationInfo));
			const Vector2 ANIM_OFFSET = Vector2(0.0013f, 0.0f);
			createIntialAnimationInfo(
				animInfo,
				ResourcesManager::Find<Texture>(ResourceMaker::MONSTER_TEXTURE_ZOMBIE_KEY),
				Vector2::Zero,
				Vector2(ZOMBIE_WIDTH, ZOMBIE_HEIGHT),
				ANIM_OFFSET,
				ZOMBIE_SPRITE_MAX_COUNT,
				ZOMBIE_IDLE_MOVING_ANIM_DURATION,
				ZOMBIE_MAG
			);

			fillLeftTopsArray(
				leftTops,
				Vector2(0.0f, ZOMBIE_HEIGHT * 1),
				Vector2(ZOMBIE_WIDTH * 5, ZOMBIE_HEIGHT * 2),
				Vector2(0.0f, ZOMBIE_HEIGHT * 3),
				Vector2(0.0f, ZOMBIE_HEIGHT * 4)
			);
			fillSpriteCountArray(
				spriteCounts,
				ZOMBIE_SPRITE_MAX_COUNT - 5,
				ZOMBIE_SPRITE_MAX_COUNT - 5,
				3,
				ZOMBIE_SPRITE_MAX_COUNT / 2
			);
			fillAnimationDurationArray(
				animDurations,
				ZOMBIE_IDLE_MOVING_ANIM_DURATION,
				DEFAULT_ANIM_DURATION,
				DEFAULT_ANIM_DURATION,
				DEFAULT_ANIM_DURATION
			);

			Animator* pZombieAnimator = createAllAnimtaion(
				new Animator(),
				ZOMBIE_IDLE_ANIM_KEY,
				ZOMBIE_MOVING_ANIM_KEY,
				ZOMBIE_ATTACK_ANIM_KEY,
				ZOMBIE_HITTED_ANIM_KEY,
				ZOMBIE_DIE_ANIM_KEY,
				animInfo,
				leftTops,
				spriteCounts,
				animDurations
			);

			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			createMonsterInfo(
				monInfo,
				ResourcesManager::Find<Mesh>(ResourceMaker::RECT_NORMAL_MAP_MESH_KEY),
				ResourcesManager::Find<Material>(ResourceMaker::MONSTER_ZOMBIE_NORMAL_MAP_MATERIAL_KEY),
				pZombieAnimator,
				pPlayerScript,
				eMonsterType::LV_1_ZOMBIE
			);
			createMonster(monInfo, retMonsterPackage);
			createAttackCollider(monInfo, retMonsterPackage, MONSTER_ATTACK_COLLIDER_Y_POS);
			setTransform(retMonsterPackage.pMonster->GetTransform(), position, ZOMBIE_SCALE_VECTOR);
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			static constexpr const float HEABY_SLICER_WIDTH = 192.0f;
			static constexpr const float HEABY_SLICER_HEIGHT = 70.0f;
			static constexpr const float HEABY_SLICER_MAG = 100.0f;
			static constexpr const float HEABY_SLICER_DIE_ANIM_DURATION = 0.1f;
			AnimationInfo animInfo;
			ZeroMemory(&animInfo, sizeof(AnimationInfo));
			Vector2 animOffset = Vector2(0.011f, 0.0f);
			createIntialAnimationInfo(
				animInfo,
				ResourcesManager::Find<Texture>(ResourceMaker::MONSTER_TEXTURE_HEABY_SLICER_KEY),
				Vector2(Vector2::Zero),
				Vector2(HEABY_SLICER_WIDTH, HEABY_SLICER_HEIGHT),
				animOffset,
				13,
				DEFAULT_ANIM_DURATION,
				HEABY_SLICER_MAG
			);

			fillLeftTopsArray(
				leftTops, 
				Vector2(0.0f, HEABY_SLICER_HEIGHT * 1),
				Vector2(0.0f, HEABY_SLICER_HEIGHT * 2),
				Vector2(0.0f, HEABY_SLICER_HEIGHT * 3),
				Vector2(0.0f, HEABY_SLICER_HEIGHT * 4)
			);
			fillSpriteCountArray(
				spriteCounts, 
				8, 
				14, 
				2, 
				15
			);
			fillAnimationDurationArray(
				animDurations, 
				DEFAULT_ANIM_DURATION, 
				DEFAULT_ANIM_DURATION, 
				DEFAULT_ANIM_DURATION, 
				DEFAULT_ANIM_DURATION
			);

			Animator* pHeabySlicerAnimator = createAllAnimtaion(
				new Animator(), 
				HEABY_SLICER_IDLE_ANIM_KEY,
				HEABY_SLICER_MOVING_ANIM_KEY,
				HEABY_SLICER_ATTACK_ANIM_KEY,
				HEABY_SLICER_HITTED_ANIM_KEY,
				HEABY_SLICER_DIE_ANIM_KEY,
				animInfo,
				leftTops,
				spriteCounts,
				animDurations
			);

			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			createMonsterInfo(
				monInfo,
				ResourcesManager::Find<Mesh>(ResourceMaker::RECT_NORMAL_MAP_MESH_KEY),
				ResourcesManager::Find<Material>(ResourceMaker::MONSTER_HEABY_SLICER_NORMAL_MAP_MATERIAL_KEY),
				pHeabySlicerAnimator,
				pPlayerScript,
				eMonsterType::LV_1_HEABY_SLICER
			);
			createMonster(monInfo, retMonsterPackage);
			createAttackCollider(monInfo, retMonsterPackage, MONSTER_ATTACK_COLLIDER_Y_POS);
			setTransform(retMonsterPackage.pMonster->GetTransform(), position, HEABY_SLICER_SCALE_VECTOR);
			break;
		}

		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			static constexpr const float LIGHT_SLICER_WIDTH = 192.0f;
			static constexpr const float LIGHT_SLICER_HEIGHT = 32.0f;
			static constexpr const float LIGHT_SLICER_MAG = 100.0f;
			static constexpr const float LIGHT_SLICER_DIE_ANIM_DURATION = 0.1f;
			AnimationInfo animInfo;
			ZeroMemory(&animInfo, sizeof(AnimationInfo));
			const Vector2 ANIM_OFFSET = Vector2(0.016f, 0.1f);
			createIntialAnimationInfo(
				animInfo,
				ResourcesManager::Find<Texture>(ResourceMaker::MONSTER_TEXTURE_LIGHT_SLICER_KEY),
				Vector2(Vector2::Zero),
				Vector2(LIGHT_SLICER_WIDTH, LIGHT_SLICER_HEIGHT),
				ANIM_OFFSET,
				9,
				DEFAULT_ANIM_DURATION,
				LIGHT_SLICER_MAG
			);

			fillLeftTopsArray(
				leftTops,
				Vector2(0.0f, LIGHT_SLICER_HEIGHT * 1),
				Vector2(0.0f, LIGHT_SLICER_HEIGHT * 2),
				Vector2(0.0f, LIGHT_SLICER_HEIGHT * 3),
				Vector2(0.0f, LIGHT_SLICER_HEIGHT * 4)
			);
			fillSpriteCountArray(
				spriteCounts,
				8,
				17,
				2,
				6
			);
			fillAnimationDurationArray(
				animDurations,
				DEFAULT_ANIM_DURATION,
				DEFAULT_ANIM_DURATION,
				DEFAULT_ANIM_DURATION,
				DEFAULT_ANIM_DURATION
			);

			Animator* pLightSlicerAnimator = createAllAnimtaion(
				new Animator(),
				LIGHT_SLICER_IDLE_ANIM_KEY,
				LIGHT_SLICER_MOVING_ANIM_KEY,
				LIGHT_SLICER_ATTACK_ANIM_KEY,
				LIGHT_SLICER_HITTED_ANIM_KEY,
				LIGHT_SLICER_DIE_ANIM_KEY,
				animInfo,
				leftTops,
				spriteCounts,
				animDurations
			);

			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			createMonsterInfo(
				monInfo,
				ResourcesManager::Find<Mesh>(ResourceMaker::RECT_NORMAL_MAP_MESH_KEY),
				ResourcesManager::Find<Material>(ResourceMaker::MONSTER_LIGHT_SLICER_NORMAL_MAP_MATERIAL_KEY),
				pLightSlicerAnimator,
				pPlayerScript,
				eMonsterType::LV_1_LIGHT_SLICER
			);
			createMonster(monInfo, retMonsterPackage);
			createAttackCollider(monInfo, retMonsterPackage, MONSTER_ATTACK_COLLIDER_Y_POS);
			setTransform(retMonsterPackage.pMonster->GetTransform(), position, LIGHT_SLICER_SCALE_VECTOR);
			break;
		}
		default:
			assert(false);
			break;
		}

		retMonsterPackage.pMonster->Initialize();
		retMonsterPackage.pHitEffectObejct->Initialize();
		retMonsterPackage.pMonsterAttackColliderObject->Initialize();

		return retMonsterPackage;
	}

	void MonsterManager::createMonsterInfo(MonsterInfo& monInfo, Mesh* pMesh, Material* pMaterial, Animator* pAnimator, PlayerScript* pPlayerScript, const eMonsterType eMonType)
	{
		assert(pMesh != nullptr && pMaterial != nullptr && pAnimator != nullptr && pPlayerScript != nullptr);
		monInfo.pMesh = pMesh;
		monInfo.pMaterial = pMaterial;
		monInfo.pAnimator = pAnimator;
		monInfo.pPlayerScript = pPlayerScript;
		monInfo.eMonType = eMonType;
	}

	Animator* MonsterManager::createAllAnimtaion(Animator* pAnimator, const std::wstring& idleKey, const std::wstring& movingKey, const std::wstring& attackKey, const std::wstring& hitKey, const std::wstring& dieKey, AnimationInfo& animInfo, const jh::math::Vector2 allSpriteLeftTopCoords[], UINT allSpriteCounts[], float allAnimDurationCounts[])
	{
		assert(pAnimator != nullptr);
		createAnimation(pAnimator, idleKey, animInfo);

		modifyAnimationInfoForNewAnimation(animInfo, allSpriteLeftTopCoords[static_cast<UINT>(eAnimationIndexSequence::MOVING)], allSpriteCounts[static_cast<UINT>(eAnimationIndexSequence::MOVING)], allAnimDurationCounts[static_cast<UINT>(eAnimationIndexSequence::MOVING)]);
		createAnimation(pAnimator, movingKey, animInfo);

		modifyAnimationInfoForNewAnimation(animInfo, allSpriteLeftTopCoords[static_cast<UINT>(eAnimationIndexSequence::ATTACK)], allSpriteCounts[static_cast<UINT>(eAnimationIndexSequence::ATTACK)], allAnimDurationCounts[static_cast<UINT>(eAnimationIndexSequence::ATTACK)]);
		createAnimation(pAnimator, attackKey, animInfo);

		modifyAnimationInfoForNewAnimation(animInfo, allSpriteLeftTopCoords[static_cast<UINT>(eAnimationIndexSequence::HIT)], allSpriteCounts[static_cast<UINT>(eAnimationIndexSequence::HIT)], allAnimDurationCounts[static_cast<UINT>(eAnimationIndexSequence::HIT)]);
		createAnimation(pAnimator, hitKey, animInfo);

		modifyAnimationInfoForNewAnimation(animInfo, allSpriteLeftTopCoords[static_cast<UINT>(eAnimationIndexSequence::DIE)], allSpriteCounts[static_cast<UINT>(eAnimationIndexSequence::DIE)], allAnimDurationCounts[static_cast<UINT>(eAnimationIndexSequence::DIE)]);
		createAnimation(pAnimator, dieKey, animInfo);

		pAnimator->PlayAnimation(idleKey, true);
		return pAnimator;
	}

	void MonsterManager::createIntialAnimationInfo(AnimationInfo& animInfo, Texture* pAtalsImage, const Vector2& leftTop, const Vector2& seperatingSize, const Vector2& offset, const UINT spriteCount, const float duration, const float magnification)
	{
		assert(pAtalsImage != nullptr);
		animInfo.pAtalsImage = pAtalsImage;
		animInfo.LeftTop = leftTop;
		animInfo.SeperatingSize = seperatingSize;
		animInfo.Offset = offset;
		animInfo.SpriteCount = spriteCount;
		animInfo.Duration = duration;
		animInfo.Magnification = magnification;
	}

	void MonsterManager::modifyAnimationInfoForNewAnimation(AnimationInfo& animInfo, const jh::math::Vector2& leftTop, const UINT spriteCount, const float duration)
	{
		animInfo.LeftTop = leftTop;
		animInfo.SpriteCount = spriteCount;
		animInfo.Duration = duration;
	}
	void MonsterManager::createAnimation(Animator* pAnimator, const std::wstring& animKey, AnimationInfo& animInfo)
	{
		pAnimator->Create(
			animKey,
			animInfo.pAtalsImage,
			animInfo.LeftTop,
			animInfo.SeperatingSize,
			animInfo.Offset,
			animInfo.SpriteCount,
			animInfo.Duration,
			animInfo.Magnification
		);
	}
	void MonsterManager::setTransform(Transform* pMonsterTransform, const Vector3& position, const Vector3& scale)
	{
		assert(pMonsterTransform != nullptr);
		pMonsterTransform->SetPosition(position);
		pMonsterTransform->SetScale(scale);
	}

	void MonsterManager::createMonster(MonsterInfo& monInfo, MonsterPackage& retMonsterPackage)
	{
		Monster* pMonster = new Monster(monInfo);
		monInfo.pHitEffectObject = new HitEffectObject(eHitEffectType::ELECTRIC, static_cast<MonsterScript*>(pMonster->GetScriptOrNull()), monInfo.pPlayerScript);
		pMonster->SetHitEffectObject(monInfo.pHitEffectObject);
		static_cast<MonsterScript*>(pMonster->GetScriptOrNull())->SetHitEffectScript(static_cast<HitEffectScript*>(monInfo.pHitEffectObject->GetScriptOrNull()));
		retMonsterPackage.pMonster = pMonster;
		retMonsterPackage.pHitEffectObejct = monInfo.pHitEffectObject;
	}
	void MonsterManager::createAttackCollider(MonsterInfo& monInfo, MonsterPackage& retMonsterPackage, const float yPos)
	{
		Monster* pMonster = retMonsterPackage.pMonster;
		assert(pMonster != nullptr);
		MonsterAttackColiderObject* pMonsterColiderObject = new MonsterAttackColiderObject();
		Transform* pMonsterTransform = pMonster->GetTransform();
		Vector3 monsterPos = pMonsterTransform->GetPosition();
		pMonsterColiderObject->GetTransform()->SetPosition(Vector3(monsterPos.x, yPos, COLLIDER_Z_VALUE));
		pMonsterColiderObject->SetMonsterTransformAndScriptAndAnimator(pMonster->GetTransform(), static_cast<MonsterScript*>(pMonster->GetScriptOrNull()), static_cast<Animator*>(pMonster->GetComponentOrNull(eComponentType::ANIMATOR)));

		if (monInfo.eMonType == eMonsterType::LV_1_ZOMBIE)
			{resizeColliderSize(monInfo.eMonType, pMonsterColiderObject);}

		retMonsterPackage.pMonsterAttackColliderObject = pMonsterColiderObject;
		pMonster->SetMonsterAttackCollider(pMonsterColiderObject);
	}
	void MonsterManager::resizeColliderSize(const eMonsterType eMonType, MonsterAttackColiderObject* pColliderObject)
	{
		assert(pColliderObject != nullptr);
		switch (eMonType)
		{
			// AttackCollider 조정 할지도 모르기때문에 추가해놓음.
		case eMonsterType::LV_1_CAGED_SHOKER:
			break;
		case eMonsterType::LV_1_SWEEPER:
			break;
		case eMonsterType::LV_1_WARDEN:
			break;
		case eMonsterType::LV_1_ZOMBIE:
		{
			static_cast<Collider2D*>(pColliderObject->GetComponentOrNull(eComponentType::COLLIDER))->SetSize(Vector2(0.5f, 0.5f));
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
			break;
		case eMonsterType::LV_1_LIGHT_SLICER:
			break;
		default:
			assert(false);
			break;
		}
	}
	void MonsterManager::fillLeftTopsArray(jh::math::Vector2 leftTopArray[], const jh::math::Vector2 movingLeftTop, const jh::math::Vector2 attackLeftTop, const jh::math::Vector2 hitLeftTop, const jh::math::Vector2 dieLeftTop)
	{
		leftTopArray[static_cast<UINT>(eAnimationIndexSequence::MOVING)] = movingLeftTop;
		leftTopArray[static_cast<UINT>(eAnimationIndexSequence::ATTACK)] = attackLeftTop;
		leftTopArray[static_cast<UINT>(eAnimationIndexSequence::HIT)] = hitLeftTop;
		leftTopArray[static_cast<UINT>(eAnimationIndexSequence::DIE)] = dieLeftTop;
	}
	void MonsterManager::fillSpriteCountArray(UINT spriteCountArray[], const UINT movingCount, const UINT attackCount, const UINT hitCount, const UINT dieCount)
	{
		spriteCountArray[static_cast<UINT>(eAnimationIndexSequence::MOVING)] = movingCount;
		spriteCountArray[static_cast<UINT>(eAnimationIndexSequence::ATTACK)] = attackCount;
		spriteCountArray[static_cast<UINT>(eAnimationIndexSequence::HIT)] = hitCount;
		spriteCountArray[static_cast<UINT>(eAnimationIndexSequence::DIE)] = dieCount;
	}
	void MonsterManager::fillAnimationDurationArray(float animDurationArray[], const float movingDuration, const float attackDuration, const float hitDuration, const float dieDuration)
	{
		animDurationArray[static_cast<UINT>(eAnimationIndexSequence::MOVING)] = movingDuration;
		animDurationArray[static_cast<UINT>(eAnimationIndexSequence::ATTACK)] = attackDuration;
		animDurationArray[static_cast<UINT>(eAnimationIndexSequence::HIT)] = hitDuration;
		animDurationArray[static_cast<UINT>(eAnimationIndexSequence::DIE)] = dieDuration;
	}
}