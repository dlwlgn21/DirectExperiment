#include "jhPlayer.h"
#include "jhResourceMaker.h"
#include "jhSpriteRenderer.h"
#include "jhPlayerScript.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhMath.h"

using namespace jh::math;


namespace jh
{
	Player::Player()
		: GameObject()
	{
		setRenderer();
		setAnimator();
		setScript();
	}
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}
	void Player::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::PLAYER_TEXTURE_ATLAS_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 48.0f;
		const float HEIGHT = 32.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(0.015f, 0.0f);
		Animator* pPlayerAnimator = new Animator();
		pPlayerAnimator->Create(
			L"PlayerIdle",
			pAtlas,
			Vector2::Zero,
			animSize,
			offset,
			4,
			0.15f,
			100
		);
		pPlayerAnimator->Create(
			L"PlayerMove",
			pAtlas,
			Vector2(0.0f, HEIGHT * 4),
			animSize,
			offset,
			9,
			0.1f,
			100
		);
		pPlayerAnimator->Create(
			L"PlayerWeaponSwing",
			pAtlas,
			Vector2(0.0f, HEIGHT * 14),
			animSize,
			offset,
			6,
			0.07f,
			100
		);
		this->AddComponent(pPlayerAnimator);
		pPlayerAnimator->PlayAnimation(L"PlayerIdle", true);
	}
	void Player::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::PLAYER_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);

	}
	void Player::setScript()
	{
		PlayerScript* pScript = new PlayerScript();
		this->AddScript(pScript);
	}
}