#include "jhMonsterManager.h"
#include "jhResourcesManager.h"
#include "jhResourceMaker.h"
#include "jhTransform.h"
#include "jhMaterial.h"
#include "jhTexture.h"
#include "jhMesh.h"
#include "jhMonster.h"
#include "jhMonsterScript.h"
#include "jhMonsterAttackColiderObject.h"
#include "jhHitEffectObject.h"
#include "jhHitEffectScript.h"
#include "jhPlayerScript.h"
#include "jhAnimator.h"
#include "jhAnimation.h"

using namespace jh::math;

static constexpr const float MONSTER_INITIAL_Z_POS = 4.0f;

static constexpr const float CAGED_SHOKER_WIDTH = 110.0f;
static constexpr const float CAGED_SHOKER_HEIGHT = 42.0f;
static constexpr const float CAGED_SHOKER_MAG = 130.0f;
static constexpr const float CAGED_SHOKER_SCALE_VALUE = 7.0f;
static constexpr const float CAGED_SHOKER_INITIAL_Y_POS = -1.8f;

static constexpr const float SWEEPER_WIDTH = 88.0f;
static constexpr const float SWEEPER_HEIGHT = 33.0f;
static constexpr const float SWEEPER_MAG = 100.0f;

static constexpr const float COLLIDER_Z_VALUE = 3.0f;

namespace jh
{
	const std::wstring MonsterManager::CAGED_SHOKER_IDLE_ANIM_KEY = L"CagedIdle";
	const std::wstring MonsterManager::CAGED_SHOKER_MOVING_ANIM_KEY = L"CagedMoving";
	const std::wstring MonsterManager::CAGED_SHOKER_ATTACK_ANIM_KEY = L"CagedAttack";
	const std::wstring MonsterManager::CAGED_SHOKER_HITTED_ANIM_KEY = L"CagedHitted";
	const std::wstring MonsterManager::CAGED_SHOKER_DIE_ANIM_KEY;

	const std::wstring MonsterManager::SWEEPER_IDLE_ANIM_KEY = L"SweeperIdle";
	const std::wstring MonsterManager::SWEEPER_MOVING_ANIM_KEY = L"SweeperMoving";
	const std::wstring MonsterManager::SWEEPER_ATTACK_ANIM_KEY = L"SweeperAttack";
	const std::wstring MonsterManager::SWEEPER_HITTED_ANIM_KEY = L"SweeperHitted";
	const std::wstring MonsterManager::SWEEPER_DIE_ANIM_KEY;


	const Vector3 MonsterManager::CAGED_SHOKER_SCALE_VECTOR = Vector3(CAGED_SHOKER_SCALE_VALUE, CAGED_SHOKER_SCALE_VALUE, 1.0f);
	const Vector3 MonsterManager::SWEEPER_SCALE_VECTOR = Vector3(CAGED_SHOKER_SCALE_VALUE, CAGED_SHOKER_SCALE_VALUE, 1.0f);


	MonstePackage MonsterManager::MakeMonster(const eMonsterType eType, PlayerScript* pPlayerScript, const Vector3& position, const Vector3& scale)
	{
		assert(pPlayerScript != nullptr);
		MonstePackage retMonsterPackage;
		ZeroMemory(&retMonsterPackage, sizeof(MonstePackage));
		HitEffectObject* pHitEffectObject = new HitEffectObject();
		pHitEffectObject->SetEffectAnimation(
			ResourcesManager::Find<Texture>(ResourceMaker::EFFECT_BLOOD_TEXTURE_KEY),
			128.0f,
			128.0f,
			L"MonsterHitAnim",
			12,
			0.05f
		);

		switch (eType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::MONSTER_TEXTURE_CAGED_SHOKER_ATLAS_KEY);
			assert(pAtlas != nullptr);
			Vector2 animSize(CAGED_SHOKER_WIDTH, CAGED_SHOKER_HEIGHT);
			Vector2 offset(0.007f, 0.0f);
			Animator* pCagedShokerAnimator = createAnimatorOrNull();
			assert(pCagedShokerAnimator != nullptr);
			AnimationInfo animInfo;
			ZeroMemory(&animInfo, sizeof(AnimationInfo));
			animInfo.pAtalsImage = pAtlas;
			animInfo.LeftTop = Vector2::Zero;
			animInfo.SeperatingSize = animSize;
			animInfo.Offset = offset;
			animInfo.SpriteCount = 15;
			animInfo.Duration = 0.1f;
			animInfo.Magnification = CAGED_SHOKER_MAG;
			createAnimation(pCagedShokerAnimator, CAGED_SHOKER_IDLE_ANIM_KEY, animInfo);

			animInfo.LeftTop = Vector2(0.0f, CAGED_SHOKER_HEIGHT * 1);
			animInfo.SpriteCount = 12;
			createAnimation(pCagedShokerAnimator, CAGED_SHOKER_MOVING_ANIM_KEY, animInfo);

			animInfo.LeftTop = Vector2(0.0f, CAGED_SHOKER_HEIGHT * 2);
			animInfo.SpriteCount = 16;
			animInfo.Duration = 0.15f;
			createAnimation(pCagedShokerAnimator, CAGED_SHOKER_ATTACK_ANIM_KEY, animInfo);

			animInfo.LeftTop = Vector2(0.0f, CAGED_SHOKER_HEIGHT * 3);
			animInfo.SpriteCount = 2;
			animInfo.Duration = 0.2f;
			createAnimation(pCagedShokerAnimator, CAGED_SHOKER_HITTED_ANIM_KEY, animInfo);
			pCagedShokerAnimator->PlayAnimation(CAGED_SHOKER_IDLE_ANIM_KEY, true);

			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			monInfo.pAnimator = pCagedShokerAnimator;
			monInfo.pHitEffectObject = pHitEffectObject;
			monInfo.pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
			monInfo.pMaterial = ResourcesManager::Find<Material>(ResourceMaker::MONSTER_CAGED_SHOKER_MATERIAL_KEY);
			monInfo.pPlayerScript = pPlayerScript;
			monInfo.eMonType = eMonsterType::LV_1_CAGED_SHOKER;

			Monster* pMonster = new Monster(monInfo);
			pHitEffectObject->SetScriptAndAnimKey(pMonster->GetScriptOrNull(), L"MonsterHitAnim");
			static_cast<MonsterScript*>(pMonster->GetScriptOrNull())->SetHitEffectScript(static_cast<HitEffectScript*>(pHitEffectObject->GetScriptOrNull()));
			retMonsterPackage.pMonster = pMonster;
			retMonsterPackage.pHitEffectObejct = pHitEffectObject;

			MonsterAttackColiderObject* pMonsterColiderObject = new MonsterAttackColiderObject();
			Transform* pMonsterTransform = pMonster->GetTransform();
			Vector3 monsterPos = pMonsterTransform->GetPosition();
			pMonsterColiderObject->GetTransform()->SetPosition(Vector3(monsterPos.x, -2.2f, COLLIDER_Z_VALUE));
			pMonsterColiderObject->SetMonsterTransformAndScriptAndAnimator(pMonster->GetTransform(), static_cast<MonsterScript*>(pMonster->GetScriptOrNull()), static_cast<Animator*>(pMonster->GetComponentOrNull(eComponentType::ANIMATOR)));

			retMonsterPackage.pMonsterAttackColliderObject = pMonsterColiderObject;

			break;
		}

		case eMonsterType::LV_1_SWEEPER:
		{
			Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::MONSTER_TEXTURE_SWEEPER_ATLAS_KEY);
			assert(pAtlas != nullptr);
			Vector2 animSize(SWEEPER_WIDTH, SWEEPER_HEIGHT);
			Vector2 offset(0.02f, 0.0f);
			Animator* pSweeperAnimator = createAnimatorOrNull();
			assert(pSweeperAnimator != nullptr);
			AnimationInfo animInfo;
			ZeroMemory(&animInfo, sizeof(AnimationInfo));
			animInfo.pAtalsImage = pAtlas;
			animInfo.LeftTop = Vector2::Zero;
			animInfo.SeperatingSize = animSize;
			animInfo.Offset = offset;
			animInfo.SpriteCount = 6;
			animInfo.Duration = 0.1f;
			animInfo.Magnification = SWEEPER_MAG;
			createAnimation(pSweeperAnimator, SWEEPER_IDLE_ANIM_KEY, animInfo);

			animInfo.LeftTop = Vector2(0.0f, SWEEPER_HEIGHT * 1);
			animInfo.SpriteCount = 8;
			createAnimation(pSweeperAnimator, SWEEPER_MOVING_ANIM_KEY, animInfo);

			animInfo.LeftTop = Vector2(0.0f, SWEEPER_HEIGHT * 4);
			animInfo.SpriteCount = 10;
			animInfo.Duration = 0.1f;
			createAnimation(pSweeperAnimator, SWEEPER_ATTACK_ANIM_KEY, animInfo);

			animInfo.LeftTop = Vector2(0.0f, SWEEPER_HEIGHT * 7);
			animInfo.SpriteCount = 2;
			animInfo.Duration = 0.2f;
			createAnimation(pSweeperAnimator, SWEEPER_HITTED_ANIM_KEY, animInfo);
			pSweeperAnimator->PlayAnimation(SWEEPER_IDLE_ANIM_KEY, true);

			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			monInfo.pAnimator = pSweeperAnimator;
			monInfo.pHitEffectObject = pHitEffectObject;
			monInfo.pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
			monInfo.pMaterial = ResourcesManager::Find<Material>(ResourceMaker::MONSTER_SWEEPER_MATERIAL_KEY);
			monInfo.pPlayerScript = pPlayerScript;
			monInfo.eMonType = eMonsterType::LV_1_SWEEPER;

			Monster* pMonster = new Monster(monInfo);
			pHitEffectObject->SetScriptAndAnimKey(pMonster->GetScriptOrNull(), L"MonsterHitAnim");
			static_cast<MonsterScript*>(pMonster->GetScriptOrNull())->SetHitEffectScript(static_cast<HitEffectScript*>(pHitEffectObject->GetScriptOrNull()));
			retMonsterPackage.pMonster = pMonster;
			retMonsterPackage.pHitEffectObejct = pHitEffectObject;

			MonsterAttackColiderObject* pMonsterColiderObject = new MonsterAttackColiderObject();
			Transform* pMonsterTransform = pMonster->GetTransform();
			Vector3 monsterPos = pMonsterTransform->GetPosition();
			pMonsterColiderObject->GetTransform()->SetPosition(Vector3(monsterPos.x, -2.2f, COLLIDER_Z_VALUE));
			pMonsterColiderObject->SetMonsterTransformAndScriptAndAnimator(pMonster->GetTransform(), static_cast<MonsterScript*>(pMonster->GetScriptOrNull()), static_cast<Animator*>(pMonster->GetComponentOrNull(eComponentType::ANIMATOR)));

			retMonsterPackage.pMonsterAttackColliderObject = pMonsterColiderObject;

			break;
		}
		default:
			assert(false);
			break;
		}

		setTransform(retMonsterPackage.pMonster->GetTransform(), position, scale);

		return retMonsterPackage;
	}
	Animator* MonsterManager::createAnimatorOrNull()
	{
		return new Animator();
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
}