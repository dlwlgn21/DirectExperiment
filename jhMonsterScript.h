#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"
#include "jhMonsterManager.h"

namespace jh
{
	enum class eMonsterState
	{
		SPAWNING,
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
		MonsterScript(eMonsterType eMonsterType, PlayerScript* pPlayerScript);
		virtual ~MonsterScript() = default;

		void Initialize() override;
		void Update() override;

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

		void AnimationAttackStart();
		void AnimationAttackComplete();

		void AnimationHittedStart();
		void AnimationHittedComplete();

		void AnimationDieStart();
		void AnimationDieComplete();

		void SetRespawnState();

		eObjectLookDirection GetMonsterLookDirection() const	{ return meLookDir; }
		eMonsterState		 GetMonsterState() const			{ return meState; }
		eMonsterType		 GetMonsterType() const				{ return meMonsterType; }
		void SetHitEffectScript(HitEffectScript* pHitEffectScript) { assert(pHitEffectScript != nullptr);  mpEffectScript = pHitEffectScript; }

	private:
		float calculateDistanceFromPlayerToSetLookDirection();
		void moveOrChangeAttackingState();
		void setInitialStat();
		void setAwarenessRange();
		void setAnimKey();
		void setAnimator();
		void setPosition();
		void setLookDir(const float xPos);
		void setAnimationFlip();
		void setState(const eMonsterState eState)				{ meState = eState; }
		void playAnimation();
		void playHitEffectAnimation();
		void decreaseHP(const int amount);
		bool isCloseEnoughFromPlayerToChangeAttackingState(const float xPos);

	protected:
		Transform*						mpTranform;
		Transform*						mpPlayerTransform;
		Animator*						mpAnimator;
		HitEffectScript*				mpEffectScript;
		int								mMaxHP;
		int								mCurrHP;
		float							mSpeed;
		float							mAttackingAwarenessRange;
		float							mHittedPushDistance;
		float							mSpawningTimer;
		std::wstring					mAnimIdleKey;
		std::wstring					mAnimMoveKey;
		std::wstring					mAnimAttackKey;
		std::wstring					mAnimHittedKey;
		std::wstring					mAnimDieKey;
		eObjectLookDirection			meLookDir;
		PlayerScript*					mpPlayerScript;
		eMonsterState					meState;
		eMonsterType					meMonsterType;
	};
}

