#include "jhComponent.h"


namespace jh
{
	Component::Component(eComponentType eType)
		: mpOwner(nullptr)
		, meType(eType)
	{
	}

	Component::~Component()
	{
	}

}
