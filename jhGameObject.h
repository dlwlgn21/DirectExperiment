#pragma once
#include "jhEngine.h"


namespace jh
{
	class Component;
	class Script;
	class GameObject
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

		void SetLayerType(const eLayerType eType) { meLayerType = eType; }
		eLayerType GetLayerType() const { return meLayerType; }

	private:
		std::vector<Component*>			mComponents;
		std::vector<Script*>			mScripts;
		eLayerType										meLayerType;
	};
}

