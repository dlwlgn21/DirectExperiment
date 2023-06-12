#include "jhPlayerSkillElectricBeamScript.h"
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
static constexpr const float ELECTRIC_BEAM_Y_POS_DISTANCE_FROM_PLAYER = 0.5f;
static constexpr const UINT ELECTRIC_BEAM_ANIMATION_DAMGAE_VAILED_INDEX = 3;
static constexpr const UINT ELECTRIC_BEAM_DAMAGE = 3;
static constexpr const float ELECTRIC_BEAM_COOL_TIME = 3.0f;
static constexpr const float ELECTRIC_BEAM_PUSH_DISTANCE = 2.0f;


namespace jh
{
	PlayerSkillElectricBeamScript::PlayerSkillElectricBeamScript(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, Animator* pAnimator)
		: PlayerSkillScript(eSkillType, pPlayerScript, pAnimator)
		, mAnimKey(L"ElectricBeamKey")
	{
		initSkillStat();
	}
	void PlayerSkillElectricBeamScript::setAnimationEvent()
	{
		mpAnimator = static_cast<Animator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mAnimKey) = std::bind(&PlayerSkillElectricBeamScript::AnimationSkillStart, this);
		mpAnimator->GetCompleteEvent(mAnimKey) = std::bind(&PlayerSkillElectricBeamScript::AnimationSkillComplete, this);

	}

	void PlayerSkillElectricBeamScript::playAnimation()
	{
		assert(mpAnimator != nullptr);
		mpAnimator->PlayAnimation(mAnimKey, false);
	}

	void PlayerSkillElectricBeamScript::setOnlyYPositoin()
	{
		const float yPos = mpPlayerTransform->GetOnlyYPosition() + ELECTRIC_BEAM_Y_POS_DISTANCE_FROM_PLAYER;
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

	void PlayerSkillElectricBeamScript::setWatingPosition()
	{
		const Vector2 playerPos = mpPlayerTransform->GetOnlyXYPosition();
		const float yPos = playerPos.y + DISTANCE_FROM_PLAYER_Y_DISTANCE;
		switch (mePlayerLookDirection)
		{
		case eObjectLookDirection::LEFT:
		{
			mpTransform->SetOnlyXYPosition(playerPos.x - DISTANCE_FROM_PLAYER_X_DISTANCE, yPos);
			break;
		}
		case eObjectLookDirection::RIGHT:
		{
			mpTransform->SetOnlyXYPosition(playerPos.x + DISTANCE_FROM_PLAYER_X_DISTANCE, yPos);
			break;
		}
		default:
			break;
		}
	}

	void PlayerSkillElectricBeamScript::initSkillStat()
	{
		mSkillStat.Damage = ELECTRIC_BEAM_DAMAGE;
		mSkillStat.CoolTime = ELECTRIC_BEAM_COOL_TIME;
		mSkillStat.VailedAttackIndex = ELECTRIC_BEAM_ANIMATION_DAMGAE_VAILED_INDEX;
		mSkillStat.PushDistance = ELECTRIC_BEAM_PUSH_DISTANCE;
		mTimer = mSkillStat.CoolTime;
	}

	void PlayerSkillElectricBeamScript::AnimationSkillStart()
	{
		// TODO : BUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FUCKDFSAFKSDAFKDSLAFKLSA
		mpAnimator->InitializeCurrAnimation();
	}
	void PlayerSkillElectricBeamScript::AnimationSkillComplete()
	{
		SetState(eSKillState::WAIT);
		//mpAnimator->InitializeCurrAnimation();
	}
}