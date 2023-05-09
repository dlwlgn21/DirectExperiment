#include "jhPortalEffectScript.h"
#include "jhOnceAnimator.h"
#include "jhTransform.h"

using namespace jh::math;

namespace jh
{
	PortalEffectScript::PortalEffectScript()
		: EffectScript()
		, mStayAnimKey(L"GreenPortalStayKey")
		, mOpenAnimKey(L"GreenPortalOpenKey")
		, mCloseAnimKey(L"GreenPortalCloseKey")
		, mePortalState(ePortalEffectState::OPEN)
	{
	}

	void PortalEffectScript::Initialize()
	{
		setAnimator();
		mpTransform = GetOwner()->GetTransform();
		assert(mpAnimator != nullptr && mpTransform != nullptr);
	}

	void PortalEffectScript::Update()
	{
		if (isPlayingAnmation()) { return; }
		switch (meState)
		{
		case eEffectState::WAIT:
		{
			break;
		}
		case eEffectState::PLAYING:
			playAnimation();
			break;
		default:
			break;
		}
	}
	void PortalEffectScript::PortalOpenAnimStart()
	{

	}
	void PortalEffectScript::PortalOpenAnimComplete()
	{
		mpAnimator->SetComplete();
		setPortalState(ePortalEffectState::STAY);
	}

	void PortalEffectScript::PortalStayAnimStart()
	{

	}
	void PortalEffectScript::PortalStayAnimComplete()
	{
		mpAnimator->SetComplete();
		setPortalState(ePortalEffectState::CLOSE);
	}


	void PortalEffectScript::PortalCloseAnimStart()
	{

	}
	void PortalEffectScript::PortalCloseAnimComplete()
	{
		mpAnimator->SetComplete();
		SetState(eEffectState::WAIT);
		setPortalState(ePortalEffectState::OPEN);
	}


	void PortalEffectScript::setAnimator()
	{
		mpAnimator = static_cast<OnceAnimator*>(GetOwner()->GetComponentOrNull(eComponentType::ANIMATOR));
		assert(mpAnimator != nullptr);
		mpAnimator->GetStartEvent(mStayAnimKey) = std::bind(&PortalEffectScript::PortalStayAnimStart, this);
		mpAnimator->GetCompleteEvent(mStayAnimKey) = std::bind(&PortalEffectScript::PortalStayAnimComplete, this);

		mpAnimator->GetStartEvent(mOpenAnimKey) = std::bind(&PortalEffectScript::PortalOpenAnimStart, this);
		mpAnimator->GetCompleteEvent(mOpenAnimKey) = std::bind(&PortalEffectScript::PortalOpenAnimComplete, this);

		mpAnimator->GetStartEvent(mCloseAnimKey) = std::bind(&PortalEffectScript::PortalCloseAnimStart, this);
		mpAnimator->GetCompleteEvent(mCloseAnimKey) = std::bind(&PortalEffectScript::PortalCloseAnimComplete, this);
	}

	void PortalEffectScript::playAnimation()
	{
		mpAnimator->SetActive(true);
		mpAnimator->SetPlaying(true);

		switch (mePortalState)
		{
		case ePortalEffectState::OPEN:
		{
			mpAnimator->PlayAnimationWithReset(mOpenAnimKey, false);
			break;
		}
		case ePortalEffectState::STAY:
		{
			mpAnimator->PlayAnimationWithReset(mStayAnimKey, false);
			break;
		}
		case ePortalEffectState::CLOSE:
		{
			mpAnimator->PlayAnimationWithReset(mCloseAnimKey, false);
			break;
		}
		default:
			assert(false);
			break;
		}
	}
}