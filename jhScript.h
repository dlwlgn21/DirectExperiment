#pragma once
#include "jhComponent.h"

namespace jh
{
	class Collider2D;
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script() = default;
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


		virtual void OnCollisionEnter(Collider2D* pOtherCollider);
		virtual void OnCollisionStay(Collider2D* pOtherCollider);
		virtual void OnCollisionExit(Collider2D* pOtherCollider);

		virtual void OnTriggerEnter(Collider2D* pOtherCollider);
		virtual void OnTriggerStay(Collider2D* pOtherCollider);
		virtual void OnTriggerExit(Collider2D* pOtherCollider);
	};
}

