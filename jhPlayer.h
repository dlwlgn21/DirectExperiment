#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Player final : public GameObject
	{
	public:
		Player();
		virtual ~Player() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;


	private:
		void setAnimator();
		void setRenderer();
		void setScript();
		void setCollider();
	};
}

