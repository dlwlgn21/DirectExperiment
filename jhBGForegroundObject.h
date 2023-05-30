#pragma once
#include "jhGameObject.h"

namespace jh
{
	class BGForegroundObject final : public GameObject
	{
	public:
		BGForegroundObject();
		virtual ~BGForegroundObject() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		void setRenderer();
	};
}

