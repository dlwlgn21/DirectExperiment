#include "jhMonster.h"
#include "jhSpriteRenderer.h"
#include "jhResourcesManager.h"
#include "jhMonsterScript.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhResourceMaker.h"
#include "jhMath.h"
#include "jhCollider2D.h"
#include "jhHitEffectObject.h"
#include "jhHitEffectScript.h"
#include "jhTransform.h"
#include "jhMonsterAttackColiderObject.h"

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
		Collider2D* pMonsterCollider = new Collider2D(eColliderLayerType::MONSTER);
		pMonsterCollider->SetSize(Vector2(0.1f, 0.2f));
		this->AddComponent(pMonsterCollider);
	}
}