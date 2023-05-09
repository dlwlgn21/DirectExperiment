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

using namespace jh::math;

static constexpr const float MONSTER_INITIAL_Z_POS = 4.0f;
static constexpr const float MONSTER_HIT_ANIM_DURATION = 0.3f;
static constexpr const float MONSTER_DIE_ANIM_DURATION = 0.3f;


static constexpr const float CAGED_SHOKER_WIDTH = 110.0f;
static constexpr const float CAGED_SHOKER_HEIGHT = 42.0f;
static constexpr const float CAGED_SHOKER_MAG = 130.0f;
static constexpr const float CAGED_SHOKER_SCALE_VALUE = 7.0f;
static constexpr const float CAGED_SHOKER_INITIAL_Y_POS = -1.8f;
static constexpr const float CAGED_SHOKER_COLLIDER_Y_POS = -2.2f;

static constexpr const float SWEEPER_WIDTH = 88.0f;
static constexpr const float SWEEPER_HEIGHT = 33.0f;
static constexpr const float SWEEPER_MAG = 100.0f;

static constexpr const float DEFAULT_ANIM_DURATION = 0.1f;
static constexpr const float COLLIDER_Z_VALUE = 3.0f;

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


	const Vector3 MonsterManager::CAGED_SHOKER_SCALE_VECTOR = Vector3(CAGED_SHOKER_SCALE_VALUE, CAGED_SHOKER_SCALE_VALUE, 1.0f);
	const Vector3 MonsterManager::SWEEPER_SCALE_VECTOR = Vector3(CAGED_SHOKER_SCALE_VALUE, CAGED_SHOKER_SCALE_VALUE, 1.0f);


	MonsterPackage MonsterManager::MakeMonster(const eMonsterType eType, PlayerScript* pPlayerScript, const Vector3& position, const Vector3& scale)
	{
		assert(pPlayerScript != nullptr);
		MonsterPackage retMonsterPackage;
		ZeroMemory(&retMonsterPackage, sizeof(MonsterPackage));

		switch (eType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			Animator* pCagedShokerAnimator = new Animator();
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
			createAnimation(pCagedShokerAnimator, CAGED_SHOKER_IDLE_ANIM_KEY, animInfo);

			modifyAnimationInfoForNewAnimation(animInfo, Vector2(0.0f, CAGED_SHOKER_HEIGHT * 1), 12);
			createAnimation(pCagedShokerAnimator, CAGED_SHOKER_MOVING_ANIM_KEY, animInfo);

			modifyAnimationInfoForNewAnimation(animInfo, Vector2(0.0f, CAGED_SHOKER_HEIGHT * 2), 16, 0.1f);
			createAnimation(pCagedShokerAnimator, CAGED_SHOKER_ATTACK_ANIM_KEY, animInfo);

			modifyAnimationInfoForNewAnimation(animInfo, Vector2(0.0f, CAGED_SHOKER_HEIGHT * 3), 2, MONSTER_HIT_ANIM_DURATION);
			createAnimation(pCagedShokerAnimator, CAGED_SHOKER_HITTED_ANIM_KEY, animInfo);

			modifyAnimationInfoForNewAnimation(animInfo, Vector2(0.0f, CAGED_SHOKER_HEIGHT * 4), 12, MONSTER_DIE_ANIM_DURATION - 0.1f);
			createAnimation(pCagedShokerAnimator, CAGED_SHOKER_DIE_ANIM_KEY, animInfo);

			pCagedShokerAnimator->PlayAnimation(CAGED_SHOKER_IDLE_ANIM_KEY, true);

			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			createMonsterInfo(
				monInfo, 
				ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY), 
				ResourcesManager::Find<Material>(ResourceMaker::MONSTER_CAGED_SHOKER_MATERIAL_KEY), 
				pCagedShokerAnimator,
				pPlayerScript,
				eMonsterType::LV_1_CAGED_SHOKER
			);

			createMonster(monInfo, retMonsterPackage);
			createAttackCollider(monInfo, retMonsterPackage, CAGED_SHOKER_COLLIDER_Y_POS);
			break;
		}

		case eMonsterType::LV_1_SWEEPER:
		{
			Animator* pSweeperAnimator = new Animator();
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
			createAnimation(pSweeperAnimator, SWEEPER_IDLE_ANIM_KEY, animInfo);

			modifyAnimationInfoForNewAnimation(animInfo, Vector2(0.0f, SWEEPER_HEIGHT * 1), 8);
			createAnimation(pSweeperAnimator, SWEEPER_MOVING_ANIM_KEY, animInfo);

			modifyAnimationInfoForNewAnimation(animInfo, Vector2(0.0f, SWEEPER_HEIGHT * 4), 10, 0.15f);
			createAnimation(pSweeperAnimator, SWEEPER_ATTACK_ANIM_KEY, animInfo);

			modifyAnimationInfoForNewAnimation(animInfo, Vector2(0.0f, SWEEPER_HEIGHT * 7), 2, MONSTER_HIT_ANIM_DURATION);
			createAnimation(pSweeperAnimator, SWEEPER_HITTED_ANIM_KEY, animInfo);

			modifyAnimationInfoForNewAnimation(animInfo, Vector2(0.0f, SWEEPER_HEIGHT * 8), 5, MONSTER_DIE_ANIM_DURATION);
			createAnimation(pSweeperAnimator, SWEEPER_DIE_ANIM_KEY, animInfo);

			pSweeperAnimator->PlayAnimation(SWEEPER_IDLE_ANIM_KEY, true);

			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			createMonsterInfo(
				monInfo,
				ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY),
				ResourcesManager::Find<Material>(ResourceMaker::MONSTER_SWEEPER_MATERIAL_KEY),
				pSweeperAnimator,
				pPlayerScript,
				eMonsterType::LV_1_SWEEPER
			);
			createMonster(monInfo, retMonsterPackage);
			createAttackCollider(monInfo, retMonsterPackage, CAGED_SHOKER_COLLIDER_Y_POS);
			break;
		}
		default:
			assert(false);
			break;
		}

		setTransform(retMonsterPackage.pMonster->GetTransform(), position, scale);

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
		monInfo.pHitEffectObject = new HitEffectObject(static_cast<MonsterScript*>(pMonster->GetScriptOrNull()), monInfo.pPlayerScript);
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

		retMonsterPackage.pMonsterAttackColliderObject = pMonsterColiderObject;
		pMonster->SetMonsterAttackCollider(pMonsterColiderObject);
	}
}