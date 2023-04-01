#pragma once
#include "jhEngine.h"

namespace jh
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddComponent(class Component* pComponent);
		Component* GetComponentOrNull(const eComponentType eType);

		void SetLayerType(const eLayerType eType) { meLayerType = eType; }
		eLayerType GetLayerType() const { return meLayerType; }

	private:
		std::vector<class Component*>	mComponents;
		eLayerType						meLayerType;
	};
}

