#pragma once
#include "jhEffectScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"
#include "jhWeaponScript.h"


namespace jh
{
	enum eHitObjectType
	{
		MONSTER,
		PLAYER,
		COUNT
	};
	class Transform;
	class OnceAnimator;
	class Script;
	class HitEffectScript : public EffectScript
	{
	public:
		HitEffectScript(Script* pFollwingScript, const std::wstring& animKey);
		virtual ~HitEffectScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void setAnimator() override;

		void HitStart();
		void HitComplete();

	public:
		void PlayAnimation();

	private:
		const std::wstring				mAnimHitEffectKey;
		Script*							mpFollwingScript;
		Transform*						mpFollwingTransform;
		eHitObjectType					meType;
	};

}

