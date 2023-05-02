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

/*
				const float WIDTH = 110.0f;
				const float HEIGHT = 42.0f;
				const float MAG = 130.0f;

*/
using namespace jh::math;

static constexpr const float CAGED_SHOKER_WIDTH = 110.0f;
static constexpr const float CAGED_SHOKER_HEIGHT = 42.0f;
static constexpr const float CAGED_SHOKER_MAG = 130.0f;

static constexpr const float COLLIDER_Z_VALUE = 3.0f;
namespace jh
{
	MonstePackage MonsterManager::MakeMonster(const eMonsterType eType, PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		MonstePackage retMonsterPackage;
		ZeroMemory(&retMonsterPackage, sizeof(MonstePackage));
		switch (eType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			HitEffectObject* pHitEffectObject = new HitEffectObject();
			pHitEffectObject->SetEffectAnimation(
				ResourcesManager::Find<Texture>(ResourceMaker::EFFECT_BLOOD_TEXTURE_KEY), 
				128.0f,
				128.0f, 
				L"MonsterHitAnim", 
				12, 
				0.05f
			);

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
			createAnimation(pCagedShokerAnimator, L"MonsterIdle", animInfo);

			animInfo.LeftTop = Vector2(0.0f, CAGED_SHOKER_HEIGHT * 1);
			animInfo.SpriteCount = 12;
			createAnimation(pCagedShokerAnimator, L"MonsterMove", animInfo);

			animInfo.LeftTop = Vector2(0.0f, CAGED_SHOKER_HEIGHT * 2);
			animInfo.SpriteCount = 16;
			animInfo.Duration = 0.15f;
			createAnimation(pCagedShokerAnimator, L"MonsterAttack", animInfo);

			animInfo.LeftTop = Vector2(0.0f, CAGED_SHOKER_HEIGHT * 3);
			animInfo.SpriteCount = 2;
			animInfo.Duration = 0.2f;
			createAnimation(pCagedShokerAnimator, L"MonsterHitted", animInfo);
			pCagedShokerAnimator->PlayAnimation(L"MonsterIdle", true);
		
			MonsterInfo monInfo;
			ZeroMemory(&monInfo, sizeof(MonsterInfo));
			monInfo.pAnimator = pCagedShokerAnimator;
			monInfo.pHitEffectObject = pHitEffectObject;
			monInfo.pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
			monInfo.pMaterial = ResourcesManager::Find<Material>(ResourceMaker::MONSTER_CAGED_SHOKER_MATERIAL_KEY);
			monInfo.pPlayerScript = pPlayerScript;

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
			
			return retMonsterPackage;
		}
		default:
			assert(false);
			break;
		}
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
}