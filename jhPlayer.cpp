#include "jhPlayer.h"
#include "jhResourceMaker.h"
#include "jhSpriteRenderer.h"
#include "jhPlayerScript.h"
#include "jhAnimator.h"
#include "jhTexture.h"
#include "jhResourcesManager.h"
#include "jhMath.h"
#include "jhCollider2D.h"
#include "jhPlayerDustEffectObject.h"
#include "jhPlayerDustEffectScript.h"
#include "jhTransform.h"
#include "jhHitEffectObject.h"
#include "jhPlayerHitEffectScript.h"
#include "jhNormalMapMaterial.h"

using namespace jh::math;

static constexpr const float PLAYER_ATTACK_DURAITON = 0.07f;

namespace jh
{
	const std::wstring Player::HIT_1_ANIM_KEY = L"Hit1AnimKey";
	const std::wstring Player::HIT_2_ANIM_KEY = L"Hit2AnimKey";
	const std::wstring Player::HIT_3_ANIM_KEY = L"Hit3AnimKey";


	Player::Player()
		: GameObject(eLayerType::PLAYER)
		, mpDashEffect(nullptr)
		, mpHitEffect(nullptr)
	{
		setRenderer();
		setAnimator();
		setScript();
		setCollider();
	}

	void Player::Inactive()
	{
		mpDashEffect->SetState(eGameObjectState::INACTIVE);
		mpHitEffect->SetState(eGameObjectState::INACTIVE);
		this->SetState(eGameObjectState::INACTIVE);
	}

	void Player::SetDustEffectToPlayerScript(PlayerDustEffectObject* pPlayerDustEffectObject)
	{
		assert(pPlayerDustEffectObject != nullptr);
		//pPlayerDustEffectObject->GetTransform()->SetParent(this);
		Vector3 playerPos = this->GetTransform()->GetPosition();
		pPlayerDustEffectObject->GetTransform()->SetPosition(Vector3(playerPos.x, playerPos.y + -0.1f, playerPos.z));
		pPlayerDustEffectObject->GetTransform()->SetScale(Vector3(4.0f, 4.0f, 1.0f));
		PlayerDustEffectScript* pScript = new PlayerDustEffectScript(static_cast<PlayerScript*>(this->GetScriptOrNull()));
		pPlayerDustEffectObject->AddScript(pScript);
		static_cast<PlayerScript*>(this->GetScriptOrNull())->SetPlayerDustEffectScript(pScript);
		mpDashEffect = pPlayerDustEffectObject;
	}
	void Player::SetHitEffectToPlayerScript(HitEffectObject* pHitEffectObject)
	{
		assert(pHitEffectObject != nullptr);
		static_cast<PlayerScript*>(this->GetScriptOrNull())->SetPlayerHitEffectScript(static_cast<PlayerHitEffectScript*>(pHitEffectObject->GetScriptOrNull()));
		mpHitEffect = pHitEffectObject;
	}

	void Player::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::PLAYER_TEXTURE_ATLAS_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 90.0f;
		const float HEIGHT = 37.0f;
		const float MAGNINICATION = 120.0f;
		const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(0.02f, 0.0f);
		Animator* pPlayerAnimator = new Animator();
		pPlayerAnimator->Create(
			L"PlayerIdle",
			pAtlas,
			Vector2(0.0f, HEIGHT * 1),
			ANIM_SIZE,
			OFFSET,
			9,
			0.1f,
			MAGNINICATION
		);


		pPlayerAnimator->Create(
			L"PlayerMove",
			pAtlas,
			Vector2(0.0f, HEIGHT * 4),
			ANIM_SIZE,
			OFFSET,
			8,
			0.1f,
			MAGNINICATION
		);


		pPlayerAnimator->Create(
			L"PlayerNormalAttack1",
			pAtlas,
			Vector2(0.0f, HEIGHT * 7),
			ANIM_SIZE,
			OFFSET,
			7,
			PLAYER_ATTACK_DURAITON,
			MAGNINICATION
		);

		pPlayerAnimator->Create(
			L"PlayerNormalAttack2",
			pAtlas,
			Vector2(0.0f, HEIGHT * 8),
			ANIM_SIZE,
			OFFSET,
			5,
			PLAYER_ATTACK_DURAITON,
			MAGNINICATION
		);
		pPlayerAnimator->Create(
			L"PlayerNormalAttack3",
			pAtlas,
			Vector2(0.0f, HEIGHT * 9),
			ANIM_SIZE,
			OFFSET,
			5,
			PLAYER_ATTACK_DURAITON + 0.03f,
			MAGNINICATION
		);



		pPlayerAnimator->Create(
			L"PlayerHitted",
			pAtlas,
			Vector2(0.0f, HEIGHT * 25),
			ANIM_SIZE,
			OFFSET,
			2,
			0.1f,
			MAGNINICATION
		);

		pPlayerAnimator->Create(
			L"PlayerDash",
			pAtlas,
			Vector2(0.0f, HEIGHT * 12),
			ANIM_SIZE,
			OFFSET,
			6,
			0.075f,
			MAGNINICATION
		);
		pPlayerAnimator->Create(
			L"PlayerPushAttack",
			pAtlas,
			Vector2(0.0f, HEIGHT * 10),
			ANIM_SIZE,
			OFFSET,
			6,
			0.1f,
			MAGNINICATION
		);
		pPlayerAnimator->Create(
			L"PlayerRolling",
			pAtlas,
			Vector2(0.0f, HEIGHT * 5),
			ANIM_SIZE,
			OFFSET,
			8,
			0.075f,
			MAGNINICATION
		);

		pPlayerAnimator->Create(
			L"PlayerDie",
			pAtlas,
			Vector2(0.0f, HEIGHT * 26),
			ANIM_SIZE,
			OFFSET,
			6,
			0.1f,
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
		Collider2D* pHitPlayerCollider = new Collider2D(eColliderLayerType::PLAYER);
		pHitPlayerCollider->SetSize(Vector2(0.1f, 0.25f));
		this->AddComponent(pHitPlayerCollider);
	}

}