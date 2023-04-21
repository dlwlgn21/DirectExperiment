#pragma once
#include "jhGameObject.h"

namespace jh
{
	enum class eParallaxDepth
	{
		DEPTH_1,
		DEPTH_2,
		DEPTH_3,
		DEPTH_4,
		DEPTH_5,
		DEPTH_6,
		COUNT
	};
	class ParallaxObject final : public GameObject
	{
	public:
		ParallaxObject(const float zValue);
		virtual ~ParallaxObject() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void SetRenderer(const std::wstring& materialKey);
	private:
		void setScript(const float zValue);
	};
}
