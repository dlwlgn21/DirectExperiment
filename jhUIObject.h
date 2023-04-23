#pragma once
#include "jhGameObject.h"

namespace jh
{
	class UIObject : public GameObject
	{
	public:
		UIObject();
		virtual ~UIObject() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		void setRenderer();
	};
}