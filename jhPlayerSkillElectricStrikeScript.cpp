#include <random>
#include "jhPlayerSkillElectricStrikeScript.h"
#include "jhMath.h"
#include "jhAnimator.h"
#include "jhPlayerSkillObject.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"
#include "jhMonsterScript.h"
#include "jhTime.h"
#include "jhCollider2D.h"
using namespace jh::math;

static constexpr const float DISTANCE_FROM_PLAYER_X_DISTANCE = 2.0f;
static constexpr const int   X_DISTNACE_RANDOM_RANGE = 2;
static constexpr const float DISTANCE_FROM_PLAYER_Y_DISTANCE = 10.0f;
static constexpr const float ELECTRIC_STRIKE_Y_POS_DISTANCE_FROM_PLAYER = 1.5f;
static constexpr const UINT ELECTRIC_STRIKE_ANIMATION_DAMGAE_VAILED_INDEX = 3;
static constexpr const UINT ELECTRIC_STRIKE_DAMAGE = 2;
static constexpr const float ELECTRIC_STRIKE_COOL_TIME = 1.0f;
static constexpr const float ELECTRIC_STRIKE_PUSH_DISTANCE = 0.0f;

namespace jh
{
	PlayerSkillElectricStrikeScript::PlayerSkillElectricStrikeScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator)
		: PlayerSkillScript(eSkillType, pPlayerScript, pAnimator)
		, mAnimKey(L"ElectricStrikeKey")
	{
		initSkillStat();
	}
	void PlayerSkillElectricStrikeScript::setAnimationEvent()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimKey) = std::bind(&PlayerSkillElectricStrikeScript::AnimationSkillStart, this);
		mpAnimator->GetCompleteEvent(mAnimKey) = std::bind(&PlayerSkillElectricStrikeScript::AnimationSkillComplete, this);

	}

	void PlayerSkillElectricStrikeScript::playAnimation()
	{
		assert(mpAnimator != nullptr);
		mpAnimator->PlayAnimation(mAnimKey, false);
	}

	void PlayerSkillElectricStrikeScript::setOnlyYPositoin()
	{
		const float yPos = mpPlayerTransform->GetOnlyYPosition() + ELECTRIC_STRIKE_Y_POS_DISTANCE_FROM_PLAYER;
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

	void PlayerSkillElectricStrikeScript::setWatingPosition()
	{
		const Vector2 playerPos = mpPlayerTransform->GetOnlyXYPosition();
		const float yPos = playerPos.y + DISTANCE_FROM_PLAYER_Y_DISTANCE + 10.0f;

		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_int_distribution<> dist(-X_DISTNACE_RANDOM_RANGE, X_DISTNACE_RANDOM_RANGE);
		float xRandomMove = static_cast<float>(dist(gen));

		switch (mePlayerLookDirection)
		{
		case eObjectLookDirection::LEFT:
		{
			mpTransform->SetOnlyXYPosition((playerPos.x - DISTANCE_FROM_PLAYER_X_DISTANCE) + xRandomMove, yPos);
			break;
		}
		case eObjectLookDirection::RIGHT:
		{
			mpTransform->SetOnlyXYPosition((playerPos.x + DISTANCE_FROM_PLAYER_X_DISTANCE) + xRandomMove, yPos);
			break;
		}
		default:
			break;
		}
	}

	void PlayerSkillElectricStrikeScript::initSkillStat()
	{
		mSkillStat.Damage = ELECTRIC_STRIKE_DAMAGE;
		mSkillStat.CoolTime = ELECTRIC_STRIKE_COOL_TIME;
		mSkillStat.VailedAttackIndex = ELECTRIC_STRIKE_ANIMATION_DAMGAE_VAILED_INDEX;
		mSkillStat.PushDistance = ELECTRIC_STRIKE_PUSH_DISTANCE;
		mTimer = mSkillStat.CoolTime;
	}

	void PlayerSkillElectricStrikeScript::AnimationSkillStart()
	{
		// TODO : BUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FUCKDFSAFKSDAFKDSLAFKLSA
		mpAnimator->InitializeCurrAnimation();
	}
	void PlayerSkillElectricStrikeScript::AnimationSkillComplete()
	{
		SetState(eSKillState::WAIT);
		//mpAnimator->InitializeCurrAnimation();
	}
}