#include "jhMonsterUIManager.h"

using namespace jh::math;

namespace jh
{
	void MonsterUIManager::WriteMonsterUIDataAtBuffer(const float monsterHPRatio)
	{
		MonsterUIBuffer buffer;
		ZeroMemory(&buffer, sizeof(MonsterUIBuffer));
		buffer.MonsterHPRatio = Vector4(monsterHPRatio, 0.0f, 0.0f, 0.0f);
		mCurrRatioValue = monsterHPRatio;
		mspMonsterUIConstantBuffer->WirteDataAtBuffer(&buffer, sizeof(MonsterUIBuffer));
	}

	void MonsterUIManager::SetPipeline()
	{
		mspMonsterUIConstantBuffer->SetPipeline();
	}
}