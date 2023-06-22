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
	struct MonsterHPstatus
	{
		int MaxHP;
		int CurrHP;
		MonsterHPstatus(const int maxHP, const int currHP)
			: MaxHP(maxHP)
			, CurrHP(currHP)
		{
			assert(MaxHP >= 0);
		}
	};
	class Animator;
	class Transform;
	class HitEffectScript;
	class PlayerScript;
	class MonsterScript : public Script
	{
	public:
		MonsterScript(eMonsterType eMonsterType, PlayerScript* pPlayerScript);
		MonsterScript();
		virtual ~MonsterScript() = default;

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnTriggerEnter(Collider2D* pOtherCollider) override;
		virtual void OnTriggerStay(Collider2D* pOtherCollider) override;
		virtual void OnTriggerExit(Collider2D* pOtherCollider) override;

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
		MonsterHPstatus	     GetCurrentHPStatus() const				{ return MonsterHPstatus(mMaxHP, mCurrHP); }
	
	protected:
		virtual void decreaseHP(const int amount);
		void playHitEffectAnimation();
		void setLookDir(const float xPos);


	private:
		float calculateDistanceFromPlayerToSetLookDirection();
		float getMovementAttackingPos(float movementXAmount, float currXPos);
		void moveOrChangeAttackingState();
		void setInitialStat();
		void setAwarenessRange();
		void setAttackingMovementDistance();
		void setAnimKey();
		void setAnimationEvent();
		void setPosition();
		void setAnimationFlip();
		void setState(const eMonsterState eState)				{ meState = eState; }
		void playAnimation();
		void playAttackingSFX();
		void playEruptionSFX();
		void choiceAttackingSFX(const int random);
		bool isCloseEnoughFromPlayerToChangeAttackingState(const float xPos);
		
	protected:
		Transform*						mpTranform;
		Transform*						mpPlayerTransform;
		Animator*						mpAnimator;
		HitEffectScript*				mpEffectScript;
		PlayerScript*					mpPlayerScript;
		int								mMaxHP;
		int								mCurrHP;
		UINT							mExp;
		float							mSpeed;
		float							mSpawningTimer;
		float							mAttackingAwarenessRange;
		eObjectLookDirection			meLookDir;
		eMonsterType					meMonsterType;

	private:
		float							mAttackingMovementDistance;
		float							mHittedPushDistance;
		std::wstring					mAnimIdleKey;
		std::wstring					mAnimMoveKey;
		std::wstring					mAnimAttackKey;
		std::wstring					mAnimHittedKey;
		std::wstring					mAnimDieKey;
		eMonsterState					meState;
		float							mAttackSFXTimer;

	};
}

