#include "jhGameObject.h"
#include "jhComponent.h"
#include "jhScript.h"


namespace jh
{
	GameObject::GameObject()
		: mComponents()
		, meLayerType(eLayerType::NONE)
	{
		mComponents.reserve(static_cast<UINT>(eComponentType::COUNT));
		mComponents.resize(static_cast<UINT>(eComponentType::COUNT));
		mScripts.reserve(4);
	}
	GameObject::~GameObject()
	{
		for (auto* pCom : mComponents)
		{
			if (pCom != nullptr)
			{
				delete pCom;
			}
		}
		mComponents.clear();
		for (auto* pScript : mScripts)
		{
			if (pScript != nullptr)
			{
				delete pScript;
			}
		}
		mScripts.clear();
	}
	void GameObject::Initialize()
	{
		for (auto* pCom : mComponents)
		{
			if (pCom != nullptr)
			{
				pCom->Initialize();
			}
		}
		for (auto* pScript : mScripts)
		{
			if (pScript != nullptr)
			{
				pScript->Initialize();
			}
		}
	}
	void GameObject::Update()
	{
		for (auto* pCom : mComponents)
		{
			if (pCom != nullptr)
			{
				pCom->Update();
			}
		}
		for (auto* pScript : mScripts)
		{
			if (pScript != nullptr)
			{
				pScript->Update();
			}
		}
	}
	void GameObject::FixedUpdate()
	{
		for (auto* pCom : mComponents)
		{
			if (pCom != nullptr)
			{
				pCom->FixedUpdate();
			}
		}

		for (auto* pScript : mScripts)
		{
			if (pScript != nullptr)
			{
				pScript->FixedUpdate();
			}
		}
	}
	void GameObject::Render()
	{
		for (auto* pCom : mComponents)
		{
			if (pCom != nullptr)
			{
				pCom->Render();
			}
		}
		for (auto* pScript : mScripts)
		{
			if (pScript != nullptr)
			{
				pScript->Render();
			}
		}
	}
	void GameObject::AddComponent(Component* pComponent)
	{
		assert(pComponent != nullptr);
		assert(GetComponentOrNull(pComponent->GetType()) == nullptr);
		mComponents[static_cast<UINT>(pComponent->GetType())] = pComponent;
	}
	void GameObject::AddScript(Script* pScript)
	{
		assert(pScript != nullptr);
		mScripts.push_back(pScript);
	}
	Component* GameObject::GetComponentOrNull(const eComponentType eType)
	{
		if (mComponents[static_cast<UINT>(eType)] != nullptr)
		{
			return mComponents[static_cast<UINT>(eType)];
		}
		return nullptr;
	}
}