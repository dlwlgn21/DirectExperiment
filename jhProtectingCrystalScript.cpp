#include "jhProtectingCrystalScript.h"
#include "jhTime.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"


using namespace jh::math;

static constexpr const float PI = 3.14592f;

static constexpr const float CRYSTAL_SPEED = 1.0f;
static constexpr const int	CRYSTAL_MAX_HP = 5;
static constexpr const float INVINCIVILTY_TIME = 2.0f;
static constexpr const float STATE_CHANGE_Y_POSITON = -1.0f;
static constexpr const float X_DISTANCE_FROM_PLAYER = 2.0f;


namespace jh
{
	ProtectingCrystalScript::ProtectingCrystalScript()
		: Script()
		, mSpeed(CRYSTAL_SPEED)
		, mCurrHp(CRYSTAL_MAX_HP)
		, mpTransform(nullptr)
		, meCrystalState(eCrystalState::ENTERING)
		, mInvincivlityTimer(INVINCIVILTY_TIME)
		, mpPlayerScript(nullptr)
		, mpPlayerTransform(nullptr)
	{
	}

	void ProtectingCrystalScript::Initialize()
	{
		assert(mpPlayerScript != nullptr);
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
		mpPlayerTransform = mpPlayerScript->GetOwner()->GetTransform();
		assert(mpPlayerTransform);
	}
	void ProtectingCrystalScript::Update()
	{
		assert(mpTransform != nullptr && mpPlayerScript != nullptr && mpPlayerTransform != nullptr);
		float movingXPos = mpPlayerTransform->GetOnlyXPosition() - X_DISTANCE_FROM_PLAYER;
		switch (meCrystalState)
		{
		case eCrystalState::ENTERING:
		{
			float currYPos = mpTransform->GetOnlyYPosition();
			if (currYPos < STATE_CHANGE_Y_POSITON)
			{
				SetState(eCrystalState::STAYING);
				return;
			}
			currYPos -= mSpeed * Time::DeltaTime();
			//currXPos -= mSpeed * Time::DeltaTime();
			setFinalPosision(movingXPos, currYPos);
			break;
		}
		case eCrystalState::STAYING:
		{
			static float accumYValue = 0.0f;
			accumYValue += Time::DeltaTime();
			if (std::abs(accumYValue - (2 * PI)) < FLT_EPSILON)
			{
				accumYValue = 0.0f;
			}
			float yPos = std::sin(accumYValue) - 1.0f;
			setFinalPosision(movingXPos, yPos);
			break;
		}
		case eCrystalState::HITTED:
		{
			mInvincivlityTimer -= Time::DeltaTime();
			if (mInvincivlityTimer < 0.0f)
			{
				mInvincivlityTimer = INVINCIVILTY_TIME;
				SetState(eCrystalState::STAYING);
			}
			break;
		}
		case eCrystalState::DEAD:
		{
			int a = 0;
			break;
		}
		default:
			assert(false);
			break;
		}

	}

	void ProtectingCrystalScript::DecreaseHP(UINT damage)
	{
		if (meCrystalState == eCrystalState::HITTED)
		{
			return;
		}
		mCurrHp -= damage;
		SetState(eCrystalState::HITTED);
		if (mCurrHp <= 0)
		{
			int a = 0;
			SetState(eCrystalState::DEAD);
		}
	}


	void ProtectingCrystalScript::setFinalPosision(const float xPos, const float yPos)
	{
		 mpTransform->SetOnlyXYPosition(xPos, yPos);
	}
}