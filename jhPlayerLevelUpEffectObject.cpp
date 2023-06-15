#include "jhPlayerLevelUpEffectObject.h"
#include "jhSpriteRendererIncludeFiles.h"
#include "jhAnimator.h"
#include "jhTransform.h"
#include "jhOnceAnimator.h"
#include "jhAnimation.h"
#include "jhPlayerScript.h"
#include "jhPlayerLevelUpEffectScript.h"
#include "jhLayerZValue.h"
using namespace jh::math;

namespace jh
{
	PlayerLevelUpEffectObject::PlayerLevelUpEffectObject(PlayerScript* pPlayerScript)
		: AnimatedGameObject()
	{
		assert(pPlayerScript != nullptr);
		const float LEVEL_UP_SCALE_VALUE = 8.0f;
		setAnimator();
		setRenderer();
		setScript(pPlayerScript);
		GetTransform()->SetOnlyXYScale(LEVEL_UP_SCALE_VALUE);
		Vector2 pPlayerPos = pPlayerScript->GetOwner()->GetTransform()->GetOnlyXYPosition();
		GetTransform()->SetPosition(Vector3(pPlayerPos.x, pPlayerPos.y, LEVEL_UP_UI_Z_VALUE));
	}

	void PlayerLevelUpEffectObject::setAnimator()
	{
		Texture* pAtlas = ResourcesManager::Find<Texture>(ResourceMaker::EFFECT_PLAYER_LEVEL_UP_TEXTURE_KEY);
		assert(pAtlas != nullptr);
		const float WIDTH = 48.0f;
		const float HEIGHT = 48.0f;
		const float BASIC_DURATION = 0.1f;
		const float MAG = 150.0f;
		const Vector2 ANIM_SIZE(WIDTH, HEIGHT);
		const Vector2 OFFSET(Vector2::Zero);
		OnceAnimator* pAnimator = new OnceAnimator();
		Animation* pCurrAnim = pAnimator->Create(
			L"LevelUpKey",
			pAtlas,
			Vector2::Zero,
			ANIM_SIZE,
			OFFSET,
			30,
			BASIC_DURATION,
			MAG
		);
		pAnimator->SetCurrentAnimation(pCurrAnim);
		this->AddComponent(pAnimator);
	}

	void PlayerLevelUpEffectObject::setRenderer()
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::EFFECT_PLAYER_LEVEL_UP_MATERIAL_KEY);
		assert(pMesh != nullptr);
		assert(pMaterial != nullptr);
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}

	void PlayerLevelUpEffectObject::setScript(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		PlayerLevelUpEffectScript* pScript = new PlayerLevelUpEffectScript(pPlayerScript);
		this->AddScript(pScript);
	}
}