#include "jhResource.h"

namespace jh
{
	Resource::Resource(const eReousrceType eType)
		: meType(eType)
	{
	}

	HRESULT Resource::Load(const std::wstring& path)
	{
		return S_OK;
	}
}
