#pragma once
#include "jhEngine.h"
#include "jhMath.h"
#include "jhMonsterUIStructuredBuffer.h"
#include "jhConstantBuffer.h"

namespace jh
{
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

		__forceinline void PushMonsterUIAttribute(MonsterUIAttribute info) { mMonsterUIAttributes.push_back(info); }
		__forceinline void ClearMonsterUIAttribute()					   { mMonsterUIAttributes.clear(); }
		
		void Initialize();
		void WriteMonsterUIDataAtBuffer();
		void SetPipeline();

	private:
		MonsterUIManager()
			: mMonsterUIAttributes()
			, mspMonsterUIStructuredBuffer()
			, mspMonsterUIConstantBuffer()
		{

		}
		~MonsterUIManager()
		{
			mspMonsterUIStructuredBuffer.reset();
			mspMonsterUIConstantBuffer.reset();
		}
		std::vector<MonsterUIAttribute>					mMonsterUIAttributes;
		std::unique_ptr<MonsterUIStructuredBuffer>		mspMonsterUIStructuredBuffer;
		std::unique_ptr<ConstantBuffer>					mspMonsterUIConstantBuffer;
	};
}