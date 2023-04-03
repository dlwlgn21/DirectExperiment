#pragma once
#include "jhGameObject.h"

namespace jh
{
	class Component
	{
	public:
		Component(eComponentType eType);
		virtual ~Component();

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		eComponentType GetType() const { return meType; }
		void SetOwner(GameObject* pOwner) { assert(pOwner != nullptr); mpOwner = pOwner; }
		GameObject* GetOwner() const { assert(mpOwner != nullptr); return mpOwner; }

	protected:
		GameObject* mpOwner;
		eComponentType meType;
	};
}

