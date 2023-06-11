#pragma once
#include "jhScript.h"
#include "jhUIBarObject.h"

namespace jh
{
	class MonsterScript;
	class Transform;
	class MonsterUIScript : public Script
	{
	public:
		MonsterUIScript(MonsterScript* pMonsterScript);
		virtual ~MonsterUIScript() = default;

		void Initialize() override;
		void Update() override;

		void SetMounsterUIType(const eUIBarType eUIType) { meType = eUIType; }

	private:
		MonsterScript*		mpMonsterScript;
		Transform*			mpTransform;
		Transform*			mpMonsterTransform;
		eUIBarType			meType;
	};
}
