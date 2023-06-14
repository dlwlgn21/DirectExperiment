#pragma once
#include "jhUILevelUpScript.h"
#include "jhUISkillTextObject.h"

namespace jh
{


	class Transform;
	class UISkillTextScript : public UILevelUpScript
	{
	public:
		UISkillTextScript(const eSkillTextType eTextType);
		virtual ~UISkillTextScript() = default;

		void SetSkillIconPosition(const eSkillPosition ePos)	{ meSkillPosition = ePos; }
		const eSkillPosition GetSkillPosition() const			{ return meSkillPosition; }

	private:
		void SetWaitingPosition() override;
		void SetStayingXYPosition() override;
		void SetEnteringYPostion(const float yPos) override;

	private:
		eSkillTextType		meSkillTextType;
		eSkillPosition		meSkillPosition;
	};
}
