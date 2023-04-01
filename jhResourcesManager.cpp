#include "jhResourcesManager.h"

namespace jh
{
	std::unordered_map<std::wstring, std::unique_ptr<Resource>> ResourcesManager::mResources;
}