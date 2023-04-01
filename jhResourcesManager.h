#pragma once
#include "jhEngine.h"
#include "jhResource.h"

namespace jh
{
	class ResourcesManager final
	{
	public:
		template<typename T>
		static T* Find(const std::wstring& key)
		{
			auto iter = mResources.find(key);

			if (iter != mResources.end()) { return static_cast<T*>(iter->second.get()); }

			return nullptr;
		}

		template<typename T>
		static void Insert(const std::wstring& key, T* resource)
		{
			assert(resource != nullptr || key == L"");
			if (resource == nullptr || key == L"") { return; }
			auto res = mResources.insert(std::make_pair(key, resource));
			if (res.second == false)
			{
				assert(false);
			}
		}


		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			T* retPResource = Find<T>(key);
			if (retPResource != nullptr) { return retPResource; }

			// IF NOT FOUND Resource
			std::unique_ptr<T> spResource = std::make_unique<T>();
			if (FAILED(spResource->Load(path)))
			{
				assert(false);
				return nullptr;
			}
			spResource->SetKey(key);
			spResource->SetPath(path);
			mResources.insert(std::make_pair(key, std::move(spResource)));

			return static_cast<T*>(Find<T>(key));
		}

	private:
		static std::unordered_map<std::wstring, std::unique_ptr<Resource>> mResources;
	};
}

