#include "jhMonster.h"
#include "jhResourceMaker.h"
#include "jhSpriteRenderer.h"
#include "jhMonsterScript.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhMath.h"

using namespace jh::math;

namespace jh
{
	Monster::Monster()
		: GameObject()
	{
		setRenderer();
		setAnimator();
		setScript();
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
		const float WIDTH = 96.0f;
		const float HEIGHT = 96.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(Vector2::Zero);
		Animator* pMonsterAnimator = new Animator();
		pMonsterAnimator->Create(
			L"MonsterIdle",
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			9,
			0.15f,
			100
		);
		//pPlayerAnimator->Create(
		//	L"PlayerMove",
		//	pAtlas,
		//	Vector2(0.0f, HEIGHT * 4),
		//	animSize,
		//	offset,
		//	9,
		//	0.15f,
		//	100
		//);
		//pPlayerAnimator->Create(
		//	L"PlayerLeftPunch",
		//	pAtlas,
		//	Vector2(0.0f, HEIGHT * 12),
		//	animSize,
		//	offset,
		//	6,
		//	0.1f,
		//	100
		//);
		//pPlayerAnimator->Create(
		//	L"PlayerRightPunch",
		//	pAtlas,
		//	Vector2(0.0f, HEIGHT * 13),
		//	animSize,
		//	offset,
		//	5,
		//	0.1f,
		//	100
		//);
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
	void Monster::setScript()
	{
		MonsterScript* pScript = new MonsterScript();
		this->AddScript(pScript);
	}
}