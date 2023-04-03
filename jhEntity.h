#pragma once
#include "jhEngine.h"

namespace jh
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { mName = name; }
		__forceinline const std::wstring& GetName() { return mName; }
		__forceinline UINT64 GetID() { return mID; }

	private:
		std::wstring mName;
		UINT64 mID;
	};
}

