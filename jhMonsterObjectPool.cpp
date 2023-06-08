#include "jhMonsterObjectPool.h"
#include "jhTransform.h"
#include "jhMonsterScript.h"

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
		//retPack.pMonster->SetActive();
		mMonsterVectorQ[static_cast<UINT>(eMonType)]->pop();
		return retPack;
	}

	void MonsterObjectPool::Return(const eMonsterType eMonType, MonsterPackage monPackage)
	{
		if (mMonsterVectorQ[static_cast<UINT>(eMonType)]->size() >= mMaxPoolSize)
		{
			assert(false);
			return;
		}
		mMonsterVectorQ[static_cast<UINT>(eMonType)]->push(monPackage);
	}
}

