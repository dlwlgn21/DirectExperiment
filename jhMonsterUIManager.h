#pragma once
#include "jhEngine.h"
#include "jhConstantBuffer.h"

namespace jh
{
	class GameObject;
	class MonsterUIManager final
	{
	public:
		static MonsterUIManager& GetInstance()
		{
			static MonsterUIManager instance;
			return instance;
		}

		MonsterUIManager(MonsterUIManager& other) = delete;
		MonsterUIManager& operator=(MonsterUIManager& other) = delete;
		void WriteMonsterUIDataAtBuffer(float monsterHPRatio);

		void SetPipeline();
	private:
		MonsterUIManager()
			: mspMonsterUIConstantBuffer()
			, mCurrRatioValue(0.0f)
		{
			mspMonsterUIConstantBuffer = std::make_unique<ConstantBuffer>(eConstantBufferType::MONSTER_UI);
		}
		~MonsterUIManager()
		{
			mspMonsterUIConstantBuffer.reset();
		}
		std::unique_ptr<ConstantBuffer>					mspMonsterUIConstantBuffer;
	public:
		float											mCurrRatioValue;
		GameObject*										mpCurrMonster;
	};
}