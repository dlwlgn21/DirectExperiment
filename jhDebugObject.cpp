#include "jhDebugObject.h"
#include "jhComponent.h"

namespace jh
{
	DebugObject::DebugObject()
		: GameObject()
	{
	}
	void DebugObject::FixedUpdate()
	{
		for (auto* pComponent : mComponents)
		{
			if (pComponent != nullptr)	
				{pComponent->FixedUpdate();}
		}
	}

}