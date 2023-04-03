#pragma once
#include "jhEntity.h"

namespace jh
{
	class Component;
	class Script;
	class Transform;
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddComponent(Component* pComponent);
		void AddScript(Script* pScript);

		Component* GetComponentOrNull(const eComponentType eType);

		Transform* GetTransform() const { return mpTransform; }

	private:
		std::vector<Component*>							mComponents;
		std::vector<Script*>							mScripts;
		Transform*										mpTransform;
	};
}

