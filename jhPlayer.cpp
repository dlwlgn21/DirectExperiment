#include "jhPlayer.h"
#include "jhResourceMaker.h"
#include "jhSpriteRenderer.h"
#include "jhPlayerScript.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhMath.h"
#include "jhCollider2D.h"

using namespace jh::math;


namespace jh
{
	Player::Player()
		: GameObject(eLayerType::PLAYER)
	{
		setRenderer();
		setAnimator();
		setScript();
		setCollider();
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
		const float WIDTH = 90.0f;
		const float HEIGHT = 37.0f;
		const float MAGNINICATION = 120.0f;
		Vector2 animSize(WIDTH, HEIGHT);
		Vector2 offset(0.02f, 0.0f);
		Animator* pPlayerAnimator = new Animator();
		pPlayerAnimator->Create(
			L"PlayerIdle",
			pAtlas,
			Vector2(0.0f, HEIGHT * 1),
			animSize,
			offset,
			9,
			0.15f,
			MAGNINICATION
		);


		pPlayerAnimator->Create(
			L"PlayerMove",
			pAtlas,
			Vector2(0.0f, HEIGHT * 2),
			animSize,
			offset,
			8,
			0.1f,
			MAGNINICATION
		);


		pPlayerAnimator->Create(
			L"PlayerWeaponSwing",
			pAtlas,
			Vector2(0.0f, HEIGHT * 9),
			animSize,
			offset,
			5,
			0.15f,
			MAGNINICATION
		);

		pPlayerAnimator->Create(
			L"PlayerHitted",
			pAtlas,
			Vector2(0.0f, HEIGHT * 25),
			animSize,
			offset,
			2,
			0.1f,
			MAGNINICATION
		);

		pPlayerAnimator->Create(
			L"PlayerDash",
			pAtlas,
			Vector2(0.0f, HEIGHT * 12),
			animSize,
			offset,
			6,
			0.07f,
			MAGNINICATION
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
	void Player::setCollider()
	{
		Collider2D* pHitPlayerCollider = new Collider2D();
		pHitPlayerCollider->SetSize(Vector2(0.1f, 0.25f));
		this->AddComponent(pHitPlayerCollider);
	}
}