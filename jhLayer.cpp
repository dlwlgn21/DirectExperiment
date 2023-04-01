#include "jhLayer.h"
#include "jhGameObject.h"

static constexpr const int MAX_GAME_OBJECT_COUNT = 128;

namespace jh
{
	Layer::Layer()
	{
		mGameObjects.reserve(MAX_GAME_OBJECT_COUNT);
	}
	Layer::~Layer()
	{
		if (mGameObjects.size() != 0)
		{
			for (auto* pGameObject : mGameObjects)
			{
				if (pGameObject != nullptr)
				{
					delete pGameObject;
				}
			}
			mGameObjects.clear();
		}
	}
	void Layer::Initalize()
	{
		for (auto* pGameObject : mGameObjects)
		{
			if (pGameObject != nullptr)
			{
				pGameObject->Initialize();
			}
		}
	}
	void Layer::Update()
	{
		for (auto* pGameObject : mGameObjects)
		{
			if (pGameObject != nullptr)
			{
				pGameObject->Update();
			}
		}
	}
	void Layer::FixedUpdate()
	{
		for (auto* pGameObject : mGameObjects)
		{
			if (pGameObject != nullptr)
			{
				pGameObject->FixedUpdate();
			}
		}
	}
	void Layer::Render()
	{
		for (auto* pGameObject : mGameObjects)
		{
			if (pGameObject != nullptr)
			{
				pGameObject->Render();
			}
		}
	}
	void Layer::Release()
	{
		for (auto* pGameObject : mGameObjects)
		{
			if (pGameObject != nullptr)
			{
				delete pGameObject;
			}
		}
		mGameObjects.clear();
	}
	void Layer::Destroy()
	{
	}
	void Layer::AddGameObject(GameObject* pGameObject, const eLayerType eType)
	{
		assert(pGameObject != nullptr);
		mGameObjects.push_back(pGameObject);
		pGameObject->SetLayerType(eType);
	}
	std::vector<GameObject*> Layer::GetDontDestroyGameObjects()
	{
		return std::vector<GameObject*>();
	}
}