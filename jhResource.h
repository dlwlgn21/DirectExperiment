#pragma once
#include "jhEngine.h"
#include "jhGraphics.h"

namespace jh
{
	class Resource
	{
	public:
		Resource(const eReousrceType eType);
		virtual ~Resource();

		eReousrceType GetResourceType() const { return meType; }

		virtual HRESULT Load(const std::wstring& path);

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }

		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }

	protected:
		std::wstring mKey;
		std::wstring mPath;
		const eReousrceType meType;
	};
}

