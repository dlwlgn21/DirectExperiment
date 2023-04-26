#include "jhMonster.h"
#include "jhResourceMaker.h"
#include "jhSpriteRenderer.h"
#include "jhMonsterScript.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhMath.h"
#include "jhCollider2D.h"
#include "jhHitEffectObject.h"
#include "jhEffectScript.h"
#include "jhTransform.h"

using namespace jh::math;

namespace jh
{
	Monster::Monster(HitEffectObject* pHitEffectObject, PlayerScript* pPlayerScript)
		: GameObject(eLayerType::MONSTER)
		, mpHitEffectObject(pHitEffectObject)
	{
		assert(pPlayerScript != nullptr);
		setRenderer();
		setAnimator();
		setScript(pPlayerScript);
		setCollider();
		mpHitEffectObject->GetTransform()->SetParent(this);
		mpHitEffectObject->GetTransform()->SetPosition(Vector3(0.0f, 0.1f, -3.0f));
		mpHitEffectObject->GetTransform()->SetScale(Vector3(0.5f, 0.5f, 1.0f));
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

	void Monster::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::MONSTER_TEXTURE_ATLAS_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 110.0f;
		const float HEIGHT = 42.0f;
		const float MAG = 130.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(0.007f, 0.0f);
		Animator* pMonsterAnimator = new Animator();
		pMonsterAnimator->Create(
			L"MonsterIdle",
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			15,
			0.1f,
			MAG
		);
		pMonsterAnimator->Create(
			L"MonsterMove",
			pAtlas,
			Vector2(0.0f, HEIGHT * 1),
			animSize,
			offset,
			12,
			0.1f,
			MAG
		);

		pMonsterAnimator->Create(
			L"MonsterAttack",
			pAtlas,
			Vector2(0.0f, HEIGHT * 2),
			animSize,
			offset,
			16,
			0.15f,
			MAG
		);

		pMonsterAnimator->Create(
			L"MonsterHitted",
			pAtlas,
			Vector2(0.0f, HEIGHT * 3),
			animSize,
			offset,
			2,
			0.2f,
			MAG
		);
		this->AddComponent(pMonsterAnimator);
		pMonsterAnimator->PlayAnimation(L"MonsterIdle", true);
	}
	void Monster::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::MONSTER_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);

	}
	void Monster::setScript(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript);
		MonsterScript* pScript = new MonsterScript(static_cast<EffectScript*>(mpHitEffectObject->GetScriptOrNull()), pPlayerScript);
		this->AddScript(pScript);
	}
	void Monster::setCollider()
	{
		Collider2D* pMonsterCollider = new Collider2D(eColliderLayerType::MONSTER);
		pMonsterCollider->SetSize(Vector2(0.1f, 0.25f));
		this->AddComponent(pMonsterCollider);
	}
}