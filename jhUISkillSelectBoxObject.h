#pragma once
#include "jhGameObject.h"

namespace jh
{
	class UISkillSelectBoxObject : public GameObject
	{
	public:
		UISkillSelectBoxObject();
		virtual ~UISkillSelectBoxObject() = default;

	private:
		void setRenderer();
		void setScript();
		void setTransform();
	};
}