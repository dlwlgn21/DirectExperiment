#pragma once
#include "jhEngine.h"


namespace jh
{

	union ColliderID
	{
		struct
		{
			UINT32 Left;
			UINT32 Right;
		};
		UINT64 Id;
	};


	class Collider2D;
	class Scene;

	class CollisionManager final
	{
	public:
		static CollisionManager& GetInstance()
		{
			static CollisionManager instance;
			return instance;
		}
		CollisionManager(const CollisionManager& other) = delete;
		CollisionManager& operator=(const CollisionManager& other) = delete;

		void Initialize();
		void Update();
		void FixedUpdate();
		void Render();
		void SetCollisionLayerCheck(const eLayerType eLeftLayer, const eLayerType eRightLayer, const bool bIsEnable = true);

	private:
		void checkLayerCollision(Scene* pScene, const eLayerType eLeftLayer, const eLayerType eRightLayer);
		void checkValidColliderCollision(Collider2D* pLeftCollider, Collider2D* pRightCollider);
		bool isIntersect(Collider2D* pLeftCollider, Collider2D* pRightCollider);

	private:
		CollisionManager() = default;
		~CollisionManager() = default;

	private:
		std::bitset<static_cast<UINT>(eLayerType::COUNT)> mLayerCollisionMatrix[static_cast<UINT>(eLayerType::COUNT)];
		std::unordered_map<UINT64, bool> mCollisionMap;
	};
}

