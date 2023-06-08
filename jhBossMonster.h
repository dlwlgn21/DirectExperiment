#pragma once
#include "jhMonster.h"

namespace jh
{
	class BossMonster final : public Monster
	{
	public:
		BossMonster(MonsterInfo& monsterInfo);
		virtual ~BossMonster() = default;

	private:

	};
}