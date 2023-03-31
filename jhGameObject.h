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

	private:
		std::vector<class Component*> mComponents;
	};
}

