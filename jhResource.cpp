#include "jhResource.h"

namespace jh
{
	Resource::Resource(const eReousrceType eType)
		: meType(eType)
	{
	}
	Resource::~Resource()
	{
	}
	HRESULT Resource::Load(const std::wstring& path)
	{
		return S_OK;
	}
}
