#include "jhMonsterUIManager.h"


static constexpr const UINT MAX_MONSTERS_COUNT = 32;

namespace jh
{
	void MonsterUIManager::Initialize()
	{
		mspMonsterUIStructuredBuffer = std::make_unique<MonsterUIStructuredBuffer>();
		mspMonsterUIConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::MONSTER_UI);
		mMonsterUIAttributes.reserve(MAX_MONSTERS_COUNT);
		mspMonsterUIStructuredBuffer->Create(sizeof(MonsterUIStructuredBuffer), MAX_MONSTERS_COUNT, nullptr);
	}
	void MonsterUIManager::WriteMonsterUIDataAtBuffer()
	{
		if (mMonsterUIAttributes.size() == 0)
		{
			return;
		}
		assert(mspMonsterUIStructuredBuffer != nullptr);
		mspMonsterUIStructuredBuffer->WirteDataAtBuffer(mMonsterUIAttributes.data(), static_cast<UINT>(mMonsterUIAttributes.size()));
		MonsterUIBuffer buffer;
		ZeroMemory(&buffer, sizeof(MonsterUIBuffer));
		buffer.CountOfMonsterInScene = static_cast<UINT>(mMonsterUIAttributes.size());
		mspMonsterUIConstantBuffer->WirteDataAtBuffer(&buffer, sizeof(MonsterUIBuffer));
	}
	void MonsterUIManager::SetPipeline()
	{
		if (mMonsterUIAttributes.size() == 0)
		{
			return;
		}
		mspMonsterUIStructuredBuffer->SetPipeline();
		mspMonsterUIConstantBuffer->SetPipeline();
	}

}