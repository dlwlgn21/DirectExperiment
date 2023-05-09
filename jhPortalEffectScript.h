#pragma once
#include "jhEffectScript.h"

namespace jh
{
	enum class ePortalEffectState
	{
		OPEN,
		STAY,
		CLOSE,
		COUNT
	};
	class Transform;
	class OnceAnimator;
	class PortalEffectScript : public EffectScript
	{
	public:
		PortalEffectScript();
		virtual ~PortalEffectScript() = default;

		void Initialize() override;

		void Update() override;


		void PortalStayAnimStart();
		void PortalStayAnimComplete();
		
		void PortalOpenAnimStart();
		void PortalOpenAnimComplete();

		void PortalCloseAnimStart();
		void PortalCloseAnimComplete();


	private:
		void setAnimator() override;
		void setPortalState(const ePortalEffectState eState) { mePortalState = eState; }
		void playAnimation();
	private:
		const std::wstring			mStayAnimKey;
		const std::wstring			mOpenAnimKey;
		const std::wstring			mCloseAnimKey;
		ePortalEffectState			mePortalState;
	};
}