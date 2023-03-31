#pragma once
#include "jhRenderer.h"

namespace jh
{
	class SpriteRenderer final : public Renderer
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
	};

}

