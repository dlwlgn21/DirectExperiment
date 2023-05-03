#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"
#include "jhMonsterManager.h"

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

		eObjectLookDirection GetMonsterLookDirection() const	{ return meLookDir; }
		eMonsterState		 GetMonsterState() const			{ return meState; }
		eMonsterType		 GetMonsterType() const				{ return meMonsterType; }
		void SetHitEffectScript(HitEffectScript* pHitEffectScript) { assert(pHitEffectScript != nullptr);  mpEffectScript = pHitEffectScript; }

	private:
		void setInitialStat(const int hp, const float speed)	{ mMaxHP = hp; mCurrHP = hp; mSpeed = speed; }
		void setAnimKey(const std::wstring& idleKey, const std::wstring& movingkey, const std::wstring& attackKey, const std::wstring& hittedKey);
		void setAnimator();
		void setPosition();
		void setLookDir(const jh::math::Vector3& lookDirVector);
		bool isDistanceCloseToPlayer(const jh::math::Vector3& lookDirVector);
		void setAnimationFlip();
		void setState(const eMonsterState eState)				{ meState = eState; }
		void playAnimation();

	protected:
		Transform*						mpTranform;
		Transform*						mpPlayerTransform;
		Animator*						mpAnimator;
		HitEffectScript*				mpEffectScript;
		int								mMaxHP;
		int								mCurrHP;
		float							mSpeed;
		float							mHittedPushDistance;
		std::wstring					mAnimIdleKey;
		std::wstring					mAnimMoveKey;
		std::wstring					mAnimAttackKey;
		std::wstring					mAnimHittedKey;
		eObjectLookDirection			meLookDir;
		PlayerScript*					mpPlayerScript;
		eMonsterState					meState;
		eMonsterType					meMonsterType;
	};
}

