#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"

namespace jh
{
	enum class eMonsterState
	{
		TRACING,
		ATTACKING,
		HITTED,
		DEAD
	};

	class Animator;
	class Transform;
	class HitEffectScript;
	class PlayerScript;
	class MonsterScript final : public Script
	{
	public:
		MonsterScript(PlayerScript* pPlayerScript);
		virtual ~MonsterScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void Start();
		void Complete();
		void End();

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

		void AnimationAttackStart();
		void AnimationAttackComplete();

		void AnimationHittedStart();
		void AnimationHittedComplete();

		eObjectLookDirection GetMonsterLookDirection() const	{ return meLookDir; }
		eMonsterState		 GetMonsterState() const			{ return meState; }

		void SetHitEffectScript(HitEffectScript* pHitEffectScript) { assert(pHitEffectScript != nullptr);  mpEffectScript = pHitEffectScript; }

	private:
		void setAnimator();
		void setPosition();
		void setLookDir(const jh::math::Vector3& lookDirVector);
		bool isDistanceCloseToPlayer(const jh::math::Vector3& lookDirVector);
		void setAnimationFlip();
		void setState(const eMonsterState eState)				{ meState = eState; }
		void playAnimation();
	private:
		Transform*						mpTranform;
		Transform*						mpPlayerTransform;
		Animator*						mpAnimator;
		HitEffectScript*					mpEffectScript;
		float							mSpeed;
		float							mHittedPushDistance;
		const std::wstring				mAnimIdleKey;
		const std::wstring				mAnimMoveKey;
		const std::wstring				mAnimAttackKey;
		const std::wstring				mAnimHittedKey;
		eObjectLookDirection			meLookDir;
		PlayerScript*					mpPlayerScript;
		eMonsterState					meState;
	};
}

