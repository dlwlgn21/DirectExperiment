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
		enum class eGameObjectState
		{
			ACTIVE,
			PAUSED,
			INACTIVE,
			COUNT
		};

	public:
		GameObject();
		GameObject(const eLayerType eType);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddComponent(Component* pComponent);
		void AddScript(Script* pScript);

		__forceinline eGameObjectState GetState() const					{ return meState; }

		Component* GetComponentOrNull(const eComponentType eType);
		Transform* GetTransform() const									{ return mpTransform; }
		Script* GetScriptOrNull();

		std::vector<Script*>& GetScripts()								{ return mScripts; }

		eLayerType GetLayer() const { return meLayer; }

	protected:
		std::vector<Component*>							mComponents;
		std::vector<Script*>							mScripts;
		Transform*										mpTransform;
		eGameObjectState								meState;
		eLayerType								meLayer;
	};
}

