#pragma once
#include "jhGameObject.h"

namespace jh
{
	class BattleBGImageObject final : public GameObject
	{
	public:
		BattleBGImageObject();
		virtual ~BattleBGImageObject() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		void setRenderer();
		void setScript();
	};
}

