#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"

namespace jh
{
	enum class eMonsterState
	{
		SEARCHING,
		TRACING,
		ATTACKING,
	};

	class Animator;
	class Transform;
	class EffectScript;
	class PlayerScript;
	class MonsterScript final : public Script
	{
	public:
		MonsterScript(EffectScript* pEffectScript, PlayerScript* pPlayerScript);
		virtual ~MonsterScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void Start();
		void Complete();
		void End();

		void OnCollisionEnter(Collider2D* pOtherCollider) override;
		void OnCollisionStay(Collider2D* pOtherCollider) override;
		void OnCollisionExit(Collider2D* pOtherCollider) override;

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

	private:
		void setPosition();
		void setAnimationFlip();
		void playAnimation();
	private:
		Transform*						mpTranform;
		Transform*						mpPlayerTransform;
		Animator*						mpAnimator;
		EffectScript*					mpEffectScript;
		float							mSpeed;
		const std::wstring				mAnimIdleKey;
		eObjectLookDirection			meLookDir;
		PlayerScript*					mpPlayerScript;
	};
}

