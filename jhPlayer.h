#pragma once
#include "jhGameObject.h"

namespace jh
{
	class PlayerDustEffectObject;
	class Player final : public GameObject
	{
	public:
		Player();
		virtual ~Player() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;


	// Added Part At 2023/04/28 15:21
		void SetEffectToPlayerScript(PlayerDustEffectObject* pPlayerDustEffectObject);


	private:
		void setAnimator();
		void setRenderer();
		void setScript();
		void setCollider();
	};
}

