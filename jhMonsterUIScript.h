#pragma once
#include "jhScript.h"
#include "jhUIBarObject.h"

namespace jh
{
	class MonsterScript;
	class Transform;
	class MonsterUIScript final : public Script
	{
	public:
		MonsterUIScript(MonsterScript* pMonsterScript);
		virtual ~MonsterUIScript() = default;

		void Initialize() override;
		void Update() override;

		const MonsterScript* GetMonsterScript() { assert(mpMonsterScript != nullptr); return mpMonsterScript; }
		void SetMounsterUIType(const eUIBarType eUIType) { meType = eUIType; }

	private:
		MonsterScript*		mpMonsterScript;
		Transform*			mpTransform;
		Transform*			mpMonsterTransform;
		eUIBarType			meType;
	};
}
