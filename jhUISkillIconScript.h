#pragma once
#include "jhUISkillScript.h"
#include "jhUISkillObject.h"

namespace jh
{
	class Transform;
	class UISkillIconScript : public UISkillScript
	{
	public:
		UISkillIconScript(const eSkillIconType eType);
		virtual ~UISkillIconScript() = default;

		void SetSkillIconPosition(const eSkillPosition ePos)	{ meSkillPosition = ePos; }
		const eSkillPosition GetSkillPosition() const			{ return meSkillPosition; }
	private:
		void SetStayingXYPosition() override;

	private:
		eSkillIconType		meSkillIconType;
		eSkillPosition		meSkillPosition;
	};
}

