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
			// TODO : 이거 문제 일으킬 수 있지 지후야. 생각해봐. 이걸 지워버리면 당연히 뻑이 나지요.
			//delete monPackage.pMonster;
			//delete monPackage.pHitEffectObejct;
			//delete monPackage.pMonsterAttackColliderObject;
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

