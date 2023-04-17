#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMath.h"

namespace jh
{
	class Animator;
	class Transform;
	class EffectScript;
	class MonsterScript final : public Script
	{
	public:
		MonsterScript(EffectScript* pEffectScript);
		virtual ~MonsterScript() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void Start();
		void Complete();
		void End();

		void OnCollisionEnter(Collider2D* pOtherCollider) override;
		void OnCollisionStay(Collider2D* pOtherCollider) override;
		void OnCollisionExit(Collider2D* pOtherCollider) override;

		void OnTriggerEnter(Collider2D* pOtherCollider) override;
		void OnTriggerStay(Collider2D* pOtherCollider) override;
		void OnTriggerExit(Collider2D* pOtherCollider) override;

	private:
		Transform*						mpTranform;
		Animator*						mpAnimator;
		EffectScript*					mpEffectScript;
		float							mSpeed;
		const std::wstring				mAnimIdleKey;
		eObjectLookDirection			meLookDir;
	};
}

