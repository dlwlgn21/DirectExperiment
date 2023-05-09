#include "jhMonsterObjectPool.h"

using namespace jh::math;

namespace jh
{
	MonsterPackage MonsterObjectPool::Get(const eMonsterType eMonType, PlayerScript* pPlayerScript, const Vector3& pos)
	{
		if (mMonsterVectorQ[static_cast<UINT>(eMonType)]->empty())
		{
			return MonsterManager::GetInstance().MakeMonster(eMonType, pPlayerScript, pos);
		}
		MonsterPackage retPack = mMonsterVectorQ[static_cast<UINT>(eMonType)]->front();
		mMonsterVectorQ[static_cast<UINT>(eMonType)]->pop();
		return retPack;
	}

	void MonsterObjectPool::Return(const eMonsterType eMonType, MonsterPackage monPackage)
	{
		if (mMonsterVectorQ[static_cast<UINT>(eMonType)]->size() >= mMaxPoolSize)
		{
			delete monPackage.pMonster;
			delete monPackage.pHitEffectObejct;
			delete monPackage.pMonsterAttackColliderObject;
			return;
		}
		mMonsterVectorQ[static_cast<UINT>(eMonType)]->push(monPackage);
	}
	void MonsterObjectPool::Release()
	{
		for (int i = 0; i < mMonsterVectorQ.size(); ++i)
		{
			if (mMonsterVectorQ[i] != nullptr)
			{
				while (!mMonsterVectorQ[i]->empty())
				{
					MonsterPackage monPack = mMonsterVectorQ[i]->front();
					delete monPack.pMonster;
					delete monPack.pHitEffectObejct;
					delete monPack.pMonsterAttackColliderObject;
					mMonsterVectorQ[i]->pop();
				}
				delete mMonsterVectorQ[i];
			}
		}
	}
}

