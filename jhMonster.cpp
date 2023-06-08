#include "jhMonster.h"
#include "jhSpriteRenderer.h"
#include "jhMath.h"
#include "jhResourcesManager.h"
#include "jhMonsterScript.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhResourceMaker.h"
#include "jhCollider2D.h"
#include "jhHitEffectObject.h"
#include "jhHitEffectScript.h"
#include "jhTransform.h"
#include "jhMonsterAttackColiderObject.h"
#include "jhMonsterObjectPool.h"
#include "jhAcientBossMonsterScript.h"

using namespace jh::math;

namespace jh
{
	Monster::Monster(MonsterInfo& monsterInfo)
		: GameObject(eLayerType::MONSTER)
		, mMonsterInfo(monsterInfo)
	{
		assert(mMonsterInfo.pAnimator != nullptr && mMonsterInfo.pMesh != nullptr && mMonsterInfo.pPlayerScript != nullptr);
		setRenderer();
		setAnimator();
		setScript();
		setHitCollider();
	}

	Monster::Monster()
		: GameObject(eLayerType::MONSTER)
	{
		setHitCollider();
	}
	void Monster::Initialize()
	{
		GameObject::Initialize();
	}
	void Monster::Update()
	{
		GameObject::Update();
	}
	void Monster::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Monster::Render()
	{
		GameObject::Render();
	}

	void Monster::SetHitEffectObject(HitEffectObject* pHitEffectObject)
	{
		assert(pHitEffectObject);
		mMonsterInfo.pHitEffectObject = pHitEffectObject;
	}

	void Monster::SetInactive()
	{
		assert(mMonsterInfo.pHitEffectObject != nullptr && mMonsterInfo.pMonsterAttackColiderObject != nullptr);
		this->SetState(eGameObjectState::INACTIVE);
		mMonsterInfo.pHitEffectObject->SetState(eGameObjectState::INACTIVE);
		mMonsterInfo.pMonsterAttackColiderObject->SetState(eGameObjectState::INACTIVE);
		MonsterPackage monPack;
		ZeroMemory(&monPack, sizeof(MonsterPackage));
		monPack.pMonster = this;
		monPack.pHitEffectObejct = mMonsterInfo.pHitEffectObject;
		monPack.pMonsterAttackColliderObject = mMonsterInfo.pMonsterAttackColiderObject;

		MonsterObjectPool::GetInstance().Return(mMonsterInfo.eMonType, monPack);
	}

	void Monster::SetActive()
	{
		this->SetState(eGameObjectState::ACTIVE);
		mMonsterInfo.pHitEffectObject->SetState(eGameObjectState::ACTIVE);
		mMonsterInfo.pMonsterAttackColiderObject->SetState(eGameObjectState::ACTIVE);
		static_cast<MonsterScript*>(this->GetScriptOrNull())->SetRespawnState();
		static_cast<HitEffectScript*>(mMonsterInfo.pHitEffectObject->GetScriptOrNull())->SetRespawnState();
	}

	void Monster::setAnimator()
	{
		this->AddComponent(mMonsterInfo.pAnimator);
	}
	void Monster::setRenderer()
	{
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(mMonsterInfo.pMesh, mMonsterInfo.pMaterial);
		this->AddComponent(pSpriteRenderer);

	}
	void Monster::setScript()
	{
		assert(mMonsterInfo.pPlayerScript != nullptr);
		MonsterScript* pScript = new MonsterScript(mMonsterInfo.eMonType, mMonsterInfo.pPlayerScript);
		this->AddScript(pScript);
	}
	void Monster::setHitCollider()
	{
		static const float DEFAULT_X_LENGTH = 0.1f;
		static const float DEFAULT_Y_LENGTH = 0.2f;
		Collider2D* pMonsterCollider = new Collider2D(eColliderLayerType::MONSTER);
		switch (mMonsterInfo.eMonType)
		{
		case eMonsterType::LV_1_CAGED_SHOKER:
		{
			pMonsterCollider->SetSize(Vector2(DEFAULT_X_LENGTH, DEFAULT_Y_LENGTH));
			break;
		}
		case eMonsterType::LV_1_SWEEPER:
		{
			pMonsterCollider->SetSize(Vector2(DEFAULT_X_LENGTH, DEFAULT_Y_LENGTH));
			setHitColliderCenterPos(pMonsterCollider);
			break;
		}
		case eMonsterType::LV_1_WARDEN:
		{
			pMonsterCollider->SetSize(Vector2(DEFAULT_X_LENGTH, DEFAULT_Y_LENGTH));
			setHitColliderCenterPos(pMonsterCollider);
			break;
		}
		case eMonsterType::LV_1_ZOMBIE:
		{
			pMonsterCollider->SetSize(Vector2(DEFAULT_X_LENGTH, DEFAULT_Y_LENGTH));
			setHitColliderCenterPos(pMonsterCollider);
			break;
		}
		case eMonsterType::LV_1_HEABY_SLICER:
		{
			pMonsterCollider->SetSize(Vector2(DEFAULT_X_LENGTH, DEFAULT_Y_LENGTH + 0.1f));
			const Vector3 CENTER_POS = GetTransform()->GetPosition();
			pMonsterCollider->SetCenter(Vector2(CENTER_POS.x + 0.1f, CENTER_POS.y - 1.0f));
			break;
		}
		case eMonsterType::LV_1_LIGHT_SLICER:
		{
			pMonsterCollider->SetSize(Vector2(DEFAULT_X_LENGTH, DEFAULT_Y_LENGTH + 0.1f));
			const Vector3 CENTER_POS = GetTransform()->GetPosition();
			pMonsterCollider->SetCenter(Vector2(CENTER_POS.x + 0.1f, CENTER_POS.y - 1.0f));
			break;
		}
		case eMonsterType::LV_1_DAGGER:
		{
			pMonsterCollider->SetSize(Vector2(DEFAULT_X_LENGTH, DEFAULT_Y_LENGTH));
			setHitColliderCenterPos(pMonsterCollider);
			break;
		}
		case eMonsterType::LV_1_ARCHER:
		{
			pMonsterCollider->SetSize(Vector2(0.05f, 0.1f));
			setHitColliderCenterPos(pMonsterCollider);
			break;
		}
		case eMonsterType::LV_1_BLASTER:
		{
			pMonsterCollider->SetSize(Vector2(0.05f, 0.1f));
			setHitColliderCenterPos(pMonsterCollider);
			break;
		}
		case eMonsterType::LV_1_ACIENT_BOSS:
		{
			pMonsterCollider->SetSize(Vector2(0.3f, 1.0f));
			setHitColliderCenterPos(pMonsterCollider);
			break;
		}
		default:
			assert(false);
			break;
		}
		this->AddComponent(pMonsterCollider);
	}
	
	void Monster::setHitColliderCenterPos(Collider2D* pCollider, const float xAdjustPos, const float yAdjustPos)
	{
		const Vector3 CENTER_POS = GetTransform()->GetPosition();
		pCollider->SetCenter(Vector2(CENTER_POS.x + xAdjustPos, CENTER_POS.y - yAdjustPos));
	}
}