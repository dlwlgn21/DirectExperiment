#include "jhPlayerSkillElectricTornadoScript.h"
#include "jhMath.h"
#include "jhAnimator.h"
#include "jhPlayerSkillObject.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"
#include "jhMonsterScript.h"
#include "jhTime.h"
#include "jhCollider2D.h"

using namespace jh::math;

static constexpr const float DISTANCE_FROM_PLAYER_X_DISTANCE = 4.0f;
static constexpr const float DISTANCE_FROM_PLAYER_Y_DISTANCE = 10.0f;
static constexpr const float ELECTRIC_TORNADO_Y_POS_DISTANCE_FROM_PLAYER = 0.5f;
static constexpr const UINT  ELECTRIC_TORNADO_ANIMATION_DAMGAE_VAILED_INDEX = 3;
static constexpr const UINT  ELECTRIC_TORNADO_DAMAGE = 1;
static constexpr const float ELECTRIC_TORNADO_COOL_TIME = 2.0f;
static constexpr const float ELECTRIC_TORNADO_SPEED = 3.0f;
static constexpr const float ELECTRIC_TORNADO_PUSH_DISTANCE = 1.0f;

namespace jh
{
	PlayerSkillElectricTornadoScript::PlayerSkillElectricTornadoScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator)
		: PlayerSkillScript(eSkillType, pPlayerScript, pAnimator)
		, mAnimKey(L"ElectricTornadoKey")
	{
		initSkillStat();
	}
	void PlayerSkillElectricTornadoScript::setAnimationEvent()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimKey) = std::bind(&PlayerSkillElectricTornadoScript::AnimationSkillStart, this);
		mpAnimator->GetCompleteEvent(mAnimKey) = std::bind(&PlayerSkillElectricTornadoScript::AnimationSkillComplete, this);
	}


	void PlayerSkillElectricTornadoScript::Update()
	{
		mePlayerLookDirection = mpPlayerScript->GetPlayerLookDirection();

		switch (meState)
		{
		case eSKillState::WAIT:
		{
			setWatingPosition();
			mTimer -= Time::DeltaTime();
			if (mTimer < 0.0f)
			{
				resetCoolTimer();
				SetState(eSKillState::PLAYING);
			}
			break;
		}
		case eSKillState::PLAYING:
		{
			setAnimationFlip();
			setOnlyYPositoin();
			moveXPosition();
			playAnimation();
			break;
		}
		default:
			assert(false);
			break;
		}
	}


	void PlayerSkillElectricTornadoScript::playAnimation()
	{
		assert(mpAnimator != nullptr);
		mpAnimator->PlayAnimation(mAnimKey, false);
	}

	void PlayerSkillElectricTornadoScript::setOnlyYPositoin()
	{
		const float yPos = mpPlayerTransform->GetOnlyYPosition() + ELECTRIC_TORNADO_Y_POS_DISTANCE_FROM_PLAYER;
		switch (mePlayerLookDirection)
		{
		case eObjectLookDirection::LEFT:
		{
			mpTransform->SetOnlyYPosition(yPos);
			break;
		}
		case eObjectLookDirection::RIGHT:
		{
			mpTransform->SetOnlyYPosition(yPos);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

	void PlayerSkillElectricTornadoScript::moveXPosition()
	{
		const float currXPos = mpTransform->GetOnlyXPosition();
		mpTransform->SetOnlyXPosition(currXPos + (ELECTRIC_TORNADO_SPEED * Time::DeltaTime()));
	}

	void PlayerSkillElectricTornadoScript::setWatingPosition()
	{
		const Vector2 playerPos = mpPlayerTransform->GetOnlyXYPosition();
		const float yPos = playerPos.y + DISTANCE_FROM_PLAYER_Y_DISTANCE;
		switch (mePlayerLookDirection)
		{
		case eObjectLookDirection::LEFT:
		{
			mpTransform->SetOnlyXYPosition(playerPos.x, yPos);
			break;
		}
		case eObjectLookDirection::RIGHT:
		{
			mpTransform->SetOnlyXYPosition(playerPos.x, yPos);
			break;
		}
		default:
			break;
		}
	}

	void PlayerSkillElectricTornadoScript::initSkillStat()
	{
		mSkillStat.Damage =	ELECTRIC_TORNADO_DAMAGE;
		mSkillStat.CoolTime = ELECTRIC_TORNADO_COOL_TIME;
		mSkillStat.VailedAttackIndex = 0;
		mSkillStat.PushDistance = ELECTRIC_TORNADO_PUSH_DISTANCE;
		mTimer = mSkillStat.CoolTime;
	}

	void PlayerSkillElectricTornadoScript::AnimationSkillStart()
	{
		// TODO : BUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FUCKDFSAFKSDAFKDSLAFKLSA
		mpAnimator->InitializeCurrAnimation();
	}
	void PlayerSkillElectricTornadoScript::AnimationSkillComplete()
	{
		SetState(eSKillState::WAIT);
		//mpAnimator->InitializeCurrAnimation();
	}
}