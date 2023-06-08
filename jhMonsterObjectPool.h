#pragma once
#include "jhMonsterManager.h"
#include "jhMonster.h"
#include "jhHitEffectObject.h"
#include "jhMonsterAttackColiderObject.h"

static constexpr const UINT MAX_POOL_SIZE = 64;

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



		MonsterPackage Get(const eMonsterType eMonType, PlayerScript* pPlayerScript, const jh::math::Vector3& pos);
		void Return(const eMonsterType eMonType, MonsterPackage monPackage);

	private:
		MonsterObjectPool()
			: mMaxPoolSize(MAX_POOL_SIZE)
		{
			mMonsterVectorQ.reserve(static_cast<UINT>(eMonsterType::COUNT));
			mMonsterVectorQ.resize(static_cast<UINT>(eMonsterType::COUNT));
			for (int i = 0; i < static_cast<UINT>(eMonsterType::COUNT); ++i)
			{
				mMonsterVectorQ[i] = new std::queue<MonsterPackage>;
			}
		}
		~MonsterObjectPool()
		{
			for (int i = 0; i < mMonsterVectorQ.size(); ++i)
			{
				if (mMonsterVectorQ[i] != nullptr)
				{
					delete mMonsterVectorQ[i];
				}
			}
		}
	
	private:
		UINT mMaxPoolSize;
		std::vector< std::queue<MonsterPackage>* > mMonsterVectorQ;
	};
}