#pragma once
#include "jhGameObject.h"

namespace jh
{
	class PlayerDustEffectObject;
	class HitEffectObject;
	class Player final : public GameObject
	{
	public:
		Player();
		virtual ~Player() = default;

	// Added Part At 2023/04/28 15:21
		void SetDustEffectToPlayerScript(PlayerDustEffectObject* pPlayerDustEffectObject);

	// Added Part At 2023/05/10 11:04 
		void SetHitEffectToPlayerScript(HitEffectObject* pHitEffectObject);


		static const std::wstring HIT_1_ANIM_KEY;
		static const std::wstring HIT_2_ANIM_KEY;
		static const std::wstring HIT_3_ANIM_KEY;
		void Inactive();
	private:
		void setAnimator();
		void setRenderer();
		void setScript();
		void setCollider();

	private:
		PlayerDustEffectObject* mpDashEffect;
		HitEffectObject*		mpHitEffect;
	};
}

