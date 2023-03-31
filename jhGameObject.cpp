#include "jhGameObject.h"
#include "jhComponent.h"


namespace jh
{
	GameObject::GameObject()
		: mComponents()
	{
		mComponents.reserve(static_cast<UINT>(eComponentType::COUNT));
		mComponents.resize(static_cast<UINT>(eComponentType::COUNT));
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
	}
	void GameObject::AddComponent(Component* pComponent)
	{
		assert(pComponent != nullptr);
		assert(GetComponentOrNull(pComponent->GetType()) == nullptr);
		mComponents[static_cast<UINT>(pComponent->GetType())] = pComponent;
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