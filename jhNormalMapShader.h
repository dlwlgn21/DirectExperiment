#pragma once
#include "jhShader.h"

namespace jh
{
	class NormalMapShader final : public Shader
	{
	public:
		NormalMapShader();
		virtual ~NormalMapShader() = default;

		void CreateShaders(const std::wstring& VSFileName, const std::wstring& PSFileName) override;
	private:
		void createIA();
	};
}

