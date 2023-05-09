#pragma once
#include "jhMonsterManager.h"


namespace jh
{
	class MonsterObjectPool final
	{
	public:
		static MonsterObjectPool& GetInstance()
		{
			static MonsterObjectPool instance;
			return instance;
		}
		MonsterObjectPool(const MonsterObjectPool& other) = delete;
		MonsterObjectPool& operator=(const MonsterObjectPool& other) = delete;



		MonstePackage Get();




	private:
		MonsterObjectPool() = default;
		~MonsterObjectPool();
	};
}