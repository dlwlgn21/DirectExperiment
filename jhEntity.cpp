#include "jhEntity.h"

namespace jh
{
	Entity::Entity()
		: mID(reinterpret_cast<UINT64>(this))
		, mName()
	{
	}
	Entity::~Entity()
	{
	}
}