#pragma once
#include "jhUISkillScript.h"
#include "jhUISkillTextObject.h"

namespace jh
{
	class Transform;
	class UISkillTextScript : public UISkillScript
	{
	public:
		UISkillTextScript(const eSkillTextType eTextType);
		virtual ~UISkillTextScript() = default;

		void SetSkillIconPosition(const eSkillPosition ePos)	{ meSkillPosition = ePos; }
		const eSkillPosition GetSkillPosition() const			{ return meSkillPosition; }

	private:
		void SetStayingXYPosition() override;

	private:
		eSkillTextType		meSkillTextType;
		eSkillPosition		meSkillPosition;
	};
}
