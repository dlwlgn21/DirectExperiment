#include "jhProtectingCrystalScript.h"
#include "jhTime.h"
#include "jhTransform.h"
#include "jhPlayerScript.h"


using namespace jh::math;

static constexpr const float PI = 3.14592f;

static constexpr const float CRYSTAL_SPEED = 1.0f;
static constexpr const int	CRYSTAL_MAX_HP = 20;
static constexpr const float INVINCIVILTY_TIME = 2.0f;
static constexpr const float STATE_CHANGE_Y_POSITON = -1.0f;
static constexpr const float FINAL_X_POSITION = -10.0f;

namespace jh
{
	ProtectingCrystalScript::ProtectingCrystalScript()
		: Script()
		, mSpeed(CRYSTAL_SPEED)
		, mCurrHp(CRYSTAL_MAX_HP)
		, mpTransform(nullptr)
		, meCrystalState(eCrystalState::START_MENU)
		, mInvincivlityTimer(INVINCIVILTY_TIME)
		, mpPlayerScript(nullptr)
	{
	}

	void ProtectingCrystalScript::Initialize()
	{
		assert(mpPlayerScript != nullptr);
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}
	void ProtectingCrystalScript::Update()
	{
		assert(mpTransform != nullptr);
		switch (meCrystalState)
		{
		case eCrystalState::START_MENU:
		{
			static float accumYValue = 0.0f;
			accumYValue += Time::DeltaTime();
			if (std::abs(accumYValue - (2 * PI)) < FLT_EPSILON)
			{
				accumYValue = 0.0f;
			}
			float yPos = std::sin(accumYValue) + 2.3f;
			setFinalPosision(0.0f, yPos);
			break;
		}
		case eCrystalState::ENTERING:
		{
			float currYPos = mpTransform->GetOnlyYPosition();
			if (currYPos < STATE_CHANGE_Y_POSITON)
			{
				SetState(eCrystalState::STAYING);
				return;
			}
			currYPos -= mSpeed * Time::DeltaTime();
			setFinalPosision(0.0f, currYPos);
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
			float currXPos = mpTransform->GetOnlyXPosition();
			float xDistance = currXPos - FINAL_X_POSITION;
			if (xDistance <= 0.0f)
			{
				setFinalPosision(FINAL_X_POSITION, yPos);
			}
			else
			{
				currXPos -= mSpeed * Time::DeltaTime();
				setFinalPosision(currXPos, yPos);
			}
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
			SetState(eCrystalState::DEAD);
		}
	}


	void ProtectingCrystalScript::setFinalPosision(const float xPos, const float yPos)
	{
		 mpTransform->SetOnlyXYPosition(xPos, yPos);
	}
}