#pragma once
#include "jhUISkillObject.h"

namespace jh
{
	class UISkillIconObject : public UISkillObject
	{
	public:
		UISkillIconObject(const eSkillIconType eIconType);
		virtual ~UISkillIconObject() = default;

	private:
		void setRenderer() override;
		void setScript() override;
		void setTransform() override;
		void setAnimator() override;
	private:
		eSkillIconType meSkillIconType;
	};
}

